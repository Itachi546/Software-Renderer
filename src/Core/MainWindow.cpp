#include "MainWindow.h"
#include "InputManager.h"
#include <SDL2/SDL.h>
#include <cmath>
#include "../Math/Math.h"



MainWindow::MainWindow(int width, int height, const char* title){

  this->width = width;
  this->height = height;
  running = true;

  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);

  SDL_SetWindowTitle(window, title);

}


void MainWindow::destroy(){
  
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}


void MainWindow::clear(uint8_t r, uint8_t g, uint8_t b){
  SDL_SetRenderDrawColor(renderer, r, g, b, 255);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 0, 0 ,0, 0);
}



void MainWindow::render(){

  SDL_RenderPresent(renderer);

}

bool MainWindow::is_open(){
  return running;
}

void MainWindow::set_title(const char* title){
    SDL_SetWindowTitle(window, title);
}


void MainWindow::poll_events(){
  SDL_Event event;

  while(SDL_PollEvent(&event)){

    switch(event.type){
    case SDL_KEYDOWN:
      {
	InputManager::KeyDown(event.key.keysym.scancode);
      }break;
    case SDL_KEYUP:
      {
	InputManager::KeyUp(event.key.keysym.scancode);
      }break;
    case SDL_QUIT:
      {
	running = false;
      }
    }
  }
}


void MainWindow::plot_pixel(int x, int y, vec3 color){

  SDL_SetRenderDrawColor(renderer, color.x, color.y, color.z, 255);
  SDL_RenderDrawPoint(renderer, x, y);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

}


void MainWindow::draw_line(vec2 v1, vec2 v2, vec3 color){
  
  int dx = abs(v2.x - v1.x);
  int dy = abs(v2.y - v1.y);

  int x = v1.x;
  int y = v1.y;

  int dy2 = 2 * dy;
  int dx2 = 2 * dx;


  if(fabs(dx) > fabs(dy)){
    int p0 = dy2 - dx;
    dx = 1;
    dy = 1;

    if(v1.x > v2.x){
      x = v2.x;
      y = v2.y;
      v2 = v1;
    }
    
    if(v2.y < y) dy = -1;

    while(x <= v2.x){
      plot_pixel(x, y, color);
      x += dx;
      if(p0 < 0) p0 += dy2;
      else{
	y += dy;
	p0 += dy2 - dx2;
      }
    }
  }else{

    dx = 1;
    dy = 1;
    int p0 = dx2 - dy;

    if(v1.y > v2.y){
      x = v2.x;
      y = v2.y;
      v2 = v1;
    }

    if(v2.x < x) dx = -1;

    while(y <= v2.y){
      plot_pixel(x, y, color);
      y += dy;
      if(p0 < 0) p0 += dx2;
      else{
	x+=dx;
	p0 += dx2 - dy2;
      }
    }
    
  }
}

void MainWindow::draw_circle(vec2 center, int radius, vec3 color){

  int x = radius;
  int y = 0;

  if(radius == 0){
    plot_pixel(int(center.x), int(center.y), color);
    return;
  }

  int p0 = 0;
  
  while(x >= y){

    plot_pixel(x + center.x, y + center.y, color);
    plot_pixel(y + center.y, x + center.x, color);

    plot_pixel(-y + center.x, x + center.y, color);
    plot_pixel(-x + center.x, y + center.y, color);

    plot_pixel(-x + center.x, -y + center.y, color);
    plot_pixel(-y + center.x, -x + center.y, color);

    plot_pixel(y + center.x, -x + center.y, color);
    plot_pixel(x + center.x, -y + center.y, color);

    if(p0 <= 0){
      y += 1;
      p0 += 2 * y + 1;
    }else{
      x -= 1;
      p0 -= 2 * x + 1;
    }

  }
}

vec3 MainWindow::barycentric(const vec2& v0, const vec2& v1, const vec2&v2, const vec2& p){

  //Calculate the barycentric value from given vertices
  /*
    u = (Area of v1v2p)/(Area of triangle v0v1v2)
    v = (Area of v2v0p)/(Area of triangle v0v1v2)
    w = (Area of v0v1p)/(Area of triangle v0v1v2)
   */
  vec3 u = vec3::cross(vec3(v2.x - v0.x, v1.x - v0.x, v0.x - p.x), vec3(v2.y - v0.y, v1.y - v0.y, v0.y - p.y));

  if(std::abs(u.z) < 1) return vec3(-1, -1, -1);

  return vec3(1.0f - (u.x + u.y)/ u.z, u.y/u.z, u.x/u.z);
}


void MainWindow::draw_triangle(Vertex2d v0, Vertex2d v1, Vertex2d v2){


  //Sulley's algorith to determine the front facing or back facing triangle
  //if faceDir < 0 then backfacing else front facing
  int faceDir = vec2::cross(v0.position, v1.position) + vec2::cross(v1.position, v2.position) + vec2::cross(v2.position, v0.position);
  if(faceDir < 0) return;


  //Calculation of bounding box for given triangle
  //@Note maybe need to change the implementation to raster faster
  int minX = int(std::fmin(std::fmin(v0.position.x, v1.position.x), v2.position.x));
  int maxX = int(std::fmax(std::fmax(v0.position.x, v1.position.x), v2.position.x));
				       		      
  int minY = int(std::fmin(std::fmin(v0.position.y, v1.position.y), v2.position.y));
  int maxY = int(std::fmax(std::fmax(v0.position.y, v1.position.y), v2.position.y));



  //Clipping the vertices against the screen 
  minX = int(std::max(minX, 0));
  maxX = int(std::min(maxX, int(width)));

  minY = int(std::max(minY, 0));
  maxY = int(std::min(maxY, int(height)));


  for(int i = minX; i <= maxX; ++i){
    for(int j = minY; j <= maxY; ++j){

      //for a point to be inside the triangle it's barycentric value must be all positive and sum must be equal to 1
      vec3 barycentric_value = barycentric(v0.position, v1.position, v2.position, vec2(i, j));

      //Check whether the pixel is inside or outside the triangle
      if(barycentric_value.x < 0 || barycentric_value.y < 0 || barycentric_value.z < 0) continue;

      //Garoud shading of color
      vec3 color = v0.color * barycentric_value.x  + v1.color * barycentric_value.y  +  v2.color * barycentric_value.z;

      plot_pixel(i, j, color);

    }
  }
}