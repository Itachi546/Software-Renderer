#include "MainWindow.h"
#include "InputManager.h"
#include <SDL2/SDL.h>
#include <cmath>
#include <climits>
#include "../Math/Math.h"



MainWindow::MainWindow(int width, int height, const char* title){

  this->width = width;
  this->height = height;
  running = true;

  SDL_Init(SDL_INIT_VIDEO);
  //Enable default vertical sync
  SDL_GL_SetSwapInterval(1);
  SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
  SDL_SetWindowTitle(window, title);


  z_buffer = new float[width * height];
}


void MainWindow::destroy(){

  delete []z_buffer;
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  
}
void MainWindow::clear_depth(){
  //@Note need to find efficient way to clear the depth buffer
  for (unsigned int i= 0; i < width * height; i++) z_buffer[i] = FLT_MAX;
}

void MainWindow::clear(uint8_t r, uint8_t g, uint8_t b){
  SDL_SetRenderDrawColor(renderer, r, g, b, 255);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 0, 0 ,0, 0);
  clear_depth();
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
  SDL_SetRenderDrawColor(renderer, int(color.x), int(color.y), int(color.z), 255);
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

vec3 MainWindow::barycentric(const vec2& a, const vec2& b, const vec2&c, const vec2& p){

  //Calculate the barycentric value from given vertices
  /*
    u = (Area of v1v2p)/(Area of triangle v0v1v2)
    v = (Area of v2v0p)/(Area of triangle v0v1v2)
    w = (Area of v0v1p)/(Area of triangle v0v1v2)
   */
  float u, v, w;
  vec2 v0 = b - a, v1 = c - a, v2 = p - a;
  float den = v0.x * v1.y - v1.x * v0.y;
  v = (v2.x * v1.y - v1.x * v2.y) / den;
  w = (v0.x * v2.y - v2.x * v0.y) / den;
  u = 1.0f - v - w;  
  return vec3(u, v, w);
}

void MainWindow::draw_triangle(vec2 v0, vec2 v1, vec2 v2){

  int faceDir = vec2::cross(v0, v1) + vec2::cross(v1, v2) + vec2::cross(v2, v0);
  if(faceDir >  0) return;
  draw_line(v0, v1, vec3(255,255,255));
  draw_line(v1, v2, vec3(255,255,255));
  draw_line(v2, v0, vec3(255,255,255));
}


void MainWindow::draw_triangle(Vertex3d v0, Vertex3d v1, Vertex3d v2){

  //Sulley's algorith to determine the front facing or back facing triangle
  // faceDir < 0 then backfacing else front facing but opposite is working

  int faceDir = vec2::cross(v0.position, v1.position) + vec2::cross(v1.position, v2.position) + vec2::cross(v2.position, v0.position);
  if(faceDir >  0) return;
  

  //Calculation of bounding box for given triangle
  //@Note maybe need to change the implementation to raster faster
  int minX = int(std::fmin(std::fmin(v0.position.x, v1.position.x), v2.position.x));
  int maxX = int(std::fmax(std::fmax(v0.position.x, v1.position.x), v2.position.x));
				       		      
  int minY = int(std::fmin(std::fmin(v0.position.y, v1.position.y), v2.position.y));
  int maxY = int(std::fmax(std::fmax(v0.position.y, v1.position.y), v2.position.y));

  //Clipping the vertices against the screen 
  minX = int(std::max(minX, 0));
  maxX = int(std::min(maxX, int(width-1)));

  minY = int(std::max(minY, 0));
  maxY = int(std::min(maxY, int(height-1)));
  
  for(int i = minX; i <= maxX; ++i){
    for(int j = minY; j <= maxY;  ++j){

      //for a point to be inside the triangle it's barycentric value must be all positive and sum must be equal to 1
      vec3 barycentric_value = barycentric(v0.position, v1.position, v2.position, vec2(i, j));

      //Check whether the pixel is inside or outside the triangle
      if(barycentric_value.x < 0 || barycentric_value.y < 0 || barycentric_value.z < 0) continue;

      //Garoud shading of color
      vec3 color = v0.color * barycentric_value.x  + v1.color * barycentric_value.y  +  v2.color * barycentric_value.z;
      float zCoords = barycentric_value.x * v0.position.z + barycentric_value.y * v1.position.z + barycentric_value.z * v2.position.z;

      if(z_buffer[i + j * width] >= zCoords){
	z_buffer[i + j * width] = zCoords;
      	plot_pixel(i, j, color);
      }
    }
  }
}

