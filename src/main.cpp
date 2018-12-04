#include <iostream>
#include "Core/MainWindow.h"
#include "Core/InputManager.h"
#include "Math/Math.h"
#include "Core/ObjLoader.h"

const int WIDTH = 800;
const int HEIGHT = 600;
MainWindow* window;

// void KochCurve(int x0, int y0, int x1, int y1, int limit = 5){
//     float dx = x1 - x0;
//     float dy = y1 - y0;
//     float distance = sqrt(dx * dx + dy * dy);
//     float unit = distance /3.0f;

//     float angle = atan2(dy, dx);
//     float pX = x0 + dx/3;
//     float pY= y0 + dy/3;
  
//     float qX = x1 - dx/3;
//     float qY= y1 - dy/3;
  
//     float rX = pX + cos(angle - M_PI/3) * unit;
//     float rY= pY +  sin(angle - M_PI/3) * unit;

//     if(limit > 0){
//         KochCurve(x0, y0, pX, pY, limit - 1);
//         KochCurve(pX, pY, rX, rY, limit - 1);
//         KochCurve(rX, rY, qX, qY, limit - 1);
//         KochCurve(qX, qY, x1, y1, limit - 1);

//     }else{

//         //making center of screen the origin
//       window->draw_line(vec2(400 + x0, 300 + y0), vec2(400 + pX, 300 + pY), vec3(255, 0, 0));
//       window->draw_line(vec2(400 + pX, 300 + pY), vec2(400 + rX, 300 + rY), vec3(255, 0, 0));
//       window->draw_line(vec2(400 + rX, 300 + rY), vec2(400 + qX, 300 + qY), vec3(255, 0, 0));
//       window->draw_line(vec2(400 + qX, 300 + qY), vec2(400 + x1, 300 + y1), vec3(255, 0, 0));
//     }

// }

int main(void) {

  //  vec2 x1, y1;
  //  std::cout << "Enter the point: ";
  //  std::cin >> x1.x >> x1.y >> y1.x >> y1.y;
  window = new MainWindow(WIDTH, HEIGHT, "Hello");
  Model headModel = ObjLoader::load_obj("../Models/head.obj");
  vec3 color = {255, 0, 0};				        
  Vertex2d vertices[] = {
    Vertex2d(vec2(50, 160),vec3(0, 255, 0)),
    Vertex2d(vec2(10, 70), vec3(255, 0, 0)),
    Vertex2d(vec2(70, 80), vec3(0, 0, 255))
  };

  while(window->is_open()){
    window->clear(0, 0, 0);
    window->poll_events();
    
    //    KochCurve(0, -300, 278, 160);
    //    KochCurve(278, 160, -278, 160);
    //    KochCurve(-278, 160, 0, -300);
    
    window->draw_triangle(vertices[0], vertices[1], vertices[2]);
    window->render();
    if(InputManager::IsKeyPressed(InputManager::KEY_ESCAPE))
      break;
  }

  window->destroy();
}
