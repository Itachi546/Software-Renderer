 #include <iostream>
#include "Core/MainWindow.h"
#include "Core/InputManager.h"
#include "Math/Math.h"
#include "Core/ObjLoader.h"
#include <SDL2/SDL.h>
const int WIDTH = 800;
const int HEIGHT = 600;
bool wireframe = false;


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


vec3 to_worldcoords(vec3 v) {
  return vec3(int((v.x+1.0f)*WIDTH/2.0f+0.5f), HEIGHT - int((v.y+1.0f)*HEIGHT/2.0f+0.5f), v.z);
}


int main(void) {

    window = new MainWindow(WIDTH, HEIGHT, "Hello");
    std::vector<TriangleMesh> meshes = ObjLoader::load_obj("../Models/susan.obj");
    Vertex3d v1, v2, v3;
    v1.color = vec3(255, 0, 0);
    v2.color = vec3(0, 255, 0);
    v3.color = vec3(0, 0, 255);

    mat4 projection = mat4::perspective(70.0f, float(WIDTH)/HEIGHT);
    mat3 rotate;
    float angle = 0;
    vec3 translate = vec3(0, 0, -6);
    
    double frameTime = 1000.0/60.0;


    while(window->is_open()){

      double startTime = SDL_GetTicks();
      window->clear(0, 0, 0);
      window->poll_events();
    
      //    KochCurve(0, -300, 278, 160);
      //    KochCurve(278, 160, -278, 160);
      //    KochCurve(-278, 160, 0, -300);
      for(unsigned int i = 0; i < meshes.size(); ++i){

	rotate = mat3::rotate(angle);
       	angle+=0.00005;

	//Applying world transform
        v1.position = translate + rotate * meshes[i].v0;
        v2.position = translate + rotate * meshes[i].v1;
	v3.position = translate + rotate * meshes[i].v2;

		
	v1.position = to_worldcoords(projection * v1.position);
	v2.position = to_worldcoords(projection * v2.position);
	v3.position = to_worldcoords(projection * v3.position);


	//Visualizing normal as the color
	v1.color = vec3::abs(meshes[i].n0 * 255);
	v2.color = vec3::abs(meshes[i].n1 * 255);
	v3.color = vec3::abs(meshes[i].n2 * 255);


	if(!wireframe) window->draw_triangle(v1, v2, v3);
	else  window->draw_triangle(v1.position, v2.position, v3.position);
      }

      window->render();

      if(InputManager::IsKeyPressed(InputManager::KEY_ESCAPE))
	break;
      if(InputManager::IsKeyPressed(InputManager::KEY_UP))
	translate.y -=0.1;
      else if (InputManager::IsKeyPressed(InputManager::KEY_DOWN))
	translate.y +=0.1;

      if(InputManager::IsKeyPressed(InputManager::KEY_LEFT))
	translate.z -=0.1;
      else if (InputManager::IsKeyPressed(InputManager::KEY_RIGHT))
	translate.z +=0.1;
      

      double deltaTime = SDL_GetTicks() - startTime;

      if(deltaTime < frameTime){
	SDL_Delay(frameTime - deltaTime);
      }

      if(InputManager::IsKeyPressed(InputManager::KEY_SPACE)){
	//@Note Need to implement the key repeat handing also
	InputManager::KeyUp(InputManager::KEY_SPACE);
	wireframe = !wireframe;
      }
    }


    window->destroy();
    return 0;
}
