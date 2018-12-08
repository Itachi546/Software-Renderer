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
    mat3 rotate;
    vec3 translate = vec3(0, 0, -6);
    vec3 lightPos = vec3(0.0f, 2.0f, 0.0f);

    bool wireframe = false;
    float angle = 0;    
    //Load Obj model
    std::vector<TriangleMesh> meshes = ObjLoader::load_obj("../Models/susan.obj");

    while(window->is_open()){

      double startTime = SDL_GetTicks();
      window->clear(0, 0, 0);
      window->poll_events();

      Shader shader;
      shader.set_uniforms(rotate * (lightPos + translate), -translate);
      
      rotate = mat3::rotate(angle);

      for(unsigned int i = 0; i < meshes.size(); ++i){

	Vertex3d v1, v2, v0;
	//Applying world transform
        v0.position = translate + meshes[i].v0;
        v1.position = translate + meshes[i].v1;
	v2.position = translate + meshes[i].v2;

	v0.color = shader.vertex_lighting(v0, meshes[i].n0);
	v1.color = shader.vertex_lighting(v1, meshes[i].n1);
	v2.color = shader.vertex_lighting(v2, meshes[i].n2);

	v0.position = to_worldcoords(projection * v0.position);
	v1.position = to_worldcoords(projection * v1.position);
	v2.position = to_worldcoords(projection * v2.position);

	window->draw_triangle(v0, v1, v2);

	if(wireframe)  window->draw_triangle(v0.position, v1.position, v2.position);	   


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
