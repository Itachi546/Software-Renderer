 #include <iostream>
#include "Core/MainWindow.h"
#include "Core/InputManager.h"
#include "Math/Math.h"
#include "Core/ObjLoader.h"
#include "Shader/Shader.h"
#include <SDL2/SDL.h>

const int WIDTH = 800;
const int HEIGHT = 600;

MainWindow* window;

vec3 to_worldcoords(vec3 v) {
  return vec3(int((v.x+1.0f)*WIDTH/2.0f+0.5f), HEIGHT - int((v.y+1.0f)*HEIGHT/2.0f+0.5f), v.z);
}


int main(void) {

    window = new MainWindow(WIDTH, HEIGHT, "Hello");


    mat4 projection = mat4::perspective(70.0f, float(WIDTH)/HEIGHT);
    mat4 rotate;
    vec3 translate = vec3(0, 0, -6);

    bool wireframe = false;
    float angle = 0;    
    //Load Obj model
    std::vector<TriangleMesh> meshes = ObjLoader::load_obj("../Models/cube.obj");

    for(unsigned int i = 0; i <meshes.size(); ++i){
      std::cout << meshes[i].n0 << std::endl;
      std::cout << meshes[i].n1 << std::endl;
      std::cout << meshes[i].n2 << std::endl;
    }

    
    while(window->is_open()){

      double startTime = SDL_GetTicks();
      window->clear(0, 0, 0);
      window->poll_events();

      Shader shader;
      shader.set_uniforms(vec3(0, 5, 0), vec3(0, 0, -1));
      
      rotate = mat4::rotate(45.0f, vec3(1, 1, 1));

      //      mat3 normalTransform = mat3::transpose(mat3::inverse(rotate));
      for(unsigned int i = 0; i < meshes.size(); ++i){

	Vertex3d v1, v2, v3;
	//Applying world transform
        v1.position = translate + rotate * meshes[i].v0;
        v2.position = translate + rotate * meshes[i].v1;
	v3.position = translate + rotate * meshes[i].v2;


	
	
	v1.color = vec3::abs(meshes[i].n0) * 255.0f;
	v2.color = vec3::abs(meshes[i].n1) * 255.0f;
	v3.color = vec3::abs(meshes[i].n2) * 255.0f;

	v1.position = to_worldcoords(projection * v1.position);
	v2.position = to_worldcoords(projection * v2.position);
	v3.position = to_worldcoords(projection * v3.position);

	window->draw_triangle(v1, v2, v3);
	if(wireframe)  window->draw_triangle(v1.position, v2.position, v3.position);	   
      }


      window->render();


      if(InputManager::IsKeyPressed(InputManager::KEY_ESCAPE)) 	        break;

      if(InputManager::IsKeyPressed(InputManager::KEY_UP))              translate.z +=0.1;
      else if (InputManager::IsKeyPressed(InputManager::KEY_DOWN))      translate.z -=0.1;

      if(InputManager::IsKeyPressed(InputManager::KEY_LEFT))	        translate.x +=0.1;
      else if (InputManager::IsKeyPressed(InputManager::KEY_RIGHT))	translate.x -=0.1;

      if(InputManager::IsKeyPressed(InputManager::KEY_Q))	        translate.y +=0.1;
      else if (InputManager::IsKeyPressed(InputManager::KEY_A))	        translate.y -=0.1;
    
      double deltaTime = SDL_GetTicks() - startTime;
      angle += deltaTime * 0.1f;

      if(InputManager::IsKeyPressed(InputManager::KEY_SPACE)){
	//@Note Need to implement the key repeat handing also
	wireframe = !wireframe;
	InputManager::KeyUp(InputManager::KEY_SPACE);
      }
    }


    window->destroy();
    return 0;
}
