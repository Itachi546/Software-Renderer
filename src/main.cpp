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

  while(window->is_open()){
    window->clear(0, 0, 0);
    window->poll_events();
    
    //    KochCurve(0, -300, 278, 160);
    //    KochCurve(278, 160, -278, 160);
    //    KochCurve(-278, 160, 0, -300);
    vec3 white = {255, 255, 255};
    for(unsigned int i = 0; i < headModel.indices.size(); i+=3){
      Vertex2d v1, v2, v3;
      int i1 = headModel.indices[i];
      int i2 = headModel.indices[i + 1];
      int i3 = headModel.indices[i + 2];
      
      v1.position = vec2(headModel.position[i1]);
      v2.position = vec2(headModel.position[i2]);
      v3.position = vec2(headModel.position[i3]);

      v1.position.x = (v1.position.x + 1) * WIDTH/2;
      v1.position.y = HEIGHT - (v1.position.y + 1) * HEIGHT/2;

      v2.position.x = (v2.position.x + 1) * WIDTH/2.0f;
      v2.position.y = HEIGHT - (v2.position.y + 1) * HEIGHT/2;

      v3.position.x = (v3.position.x + 1) * WIDTH/2;
      v3.position.y = HEIGHT - (v3.position.y + 1) * HEIGHT/2;

      
      //v1.color = headModel.normal[i1]* 255;
      //      v1.color = headModel.normal[i2]* 255;
      //      v1.color = headModel.normal[i3]* 255;

      //      window->draw_triangle(v1, v2, v3);
      window->draw_line(v1.position, v2.position, white);
      window->draw_line(v2.position, v3.position, white);
      window->draw_line(v3.position, v1.position, white);
}

    
    window->render();
    if(InputManager::IsKeyPressed(InputManager::KEY_ESCAPE))
      break;
  }

  window->destroy();
}
