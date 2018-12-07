#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H

#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <vector>
#include <string.h>
#include "../Math/Math.h"

struct ivec3{
  int x;
  int y;
  int z;
};

/*struct Model {
  // Position
  std::vector<vec3> position;
  // Normal
  std::vector<vec3> normal;

  std::vector<unsigned int > indices;
};
*/
struct TriangleMesh{
  vec3 v0, v1, v2;
  vec3 n0, n1, n2;

  TriangleMesh(){
    
  }

  TriangleMesh(vec3 v0, vec3 v1, vec3 v2, vec3 n0, vec3 n1, vec3 n2){
    this->v0 = v0;
    this->v1 = v1;
    this->v2 = v2;

    this->n0 = n0;
    this->n1 = n1;
    this->n2 = n2;
  }
};

class ObjLoader {

 public:

  static std::vector<TriangleMesh> load_obj(const char* filename) {

    std::ifstream inFile(filename);

    if (!inFile) {
      std::cout << "Failed to Open File" << std::endl;
    }
    std::vector<std::string*> coordinates;
    std::vector<vec3> normals;
    std::vector<vec3> position;    
    std::vector<unsigned int> indices;

    std::vector<TriangleMesh> meshes;
    //Model modelData;

    std::string line;

    while (std::getline(inFile, line)) {
      coordinates.push_back(new std::string(line));
    }

    for (unsigned int i = 0; i<coordinates.size(); i++) {
      char temp[3];
      temp[2] = '\0';
      strncpy(temp, coordinates[i]->c_str(), 2);

      if (!strcmp(temp, "v ")) {
	vec3 pos;
	//@Note Need to find alternate way
	sscanf(coordinates[i]->c_str(), "v %f %f %f", &pos.x, &pos.y, &pos.z);
	//	modelData.position.push_back(pos);
	position.push_back(pos);
	//	modelData.normal.push_back(vec3(0, 0, 0));
      }

      else if (!strcmp(temp, "vn")) {
	vec3 normal;
	sscanf(coordinates[i]->c_str(), "vn %f %f %f", &normal.x, &normal.y, &normal.z);
	normals.push_back(normal);
      }

      else if (!strcmp(temp, "f ")) {

	ivec3 s1, s2, s3;
	sscanf(coordinates[i]->c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", &s1.x, &s1.y, &s1.z, &s2.x, &s2.y, &s2.z, &s3.x, &s3.y, &s3.z);
	TriangleMesh mesh;
	mesh.v0 = position[s1.x - 1];
	mesh.v1 = position[s2.x - 1];
	mesh.v2 = position[s3.x - 1];

	mesh.n0 = normals[s1.x - 1];
	mesh.n1 = normals[s2.x - 1];
	mesh.n2 = normals[s3.x - 1];

	meshes.push_back(mesh);
	//	modelData.normal[s1.x - 1] = normals[s1.z - 1];
	//	modelData.normal[s2.x - 1] = normals[s2.z - 1];
	//	modelData.normal[s3.x - 1] = normals[s3.z - 1];
	
	//	indices.push_back(s1.x - 1);
	//	indices.push_back(s2.x - 1);
	//	indices.push_back(s3.x - 1);
      }
    }

    for (unsigned int i = 0; i<coordinates.size(); i++) {
      delete coordinates[i];
    }
    /*    for(unsigned int i = 0; i < modelData.normal.size(); ++i){
      std::cout << modelData.normal[i] << std::endl;
    }
    //    modelData.indices = indices;
    */
    return meshes;
  }
};


#endif
