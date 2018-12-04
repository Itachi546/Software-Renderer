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

struct Model {
  // Position
  std::vector<vec3> position;
  // Normal
  std::vector<vec3> normal;

  std::vector<unsigned int > indices;
};
class ObjLoader {

 public:

  static Model load_obj(const char* filename) {

    std::ifstream inFile(filename);

    if (!inFile) {
      std::cout << "Failed to Open File" << std::endl;
    }
    std::vector<std::string*> coordinates;
    std::vector<vec3> normals;
    std::vector<unsigned int> indices;

    Model modelData;

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
	sscanf(coordinates[i]->c_str(), "v %f %f %f", &pos.x, &pos.y, &pos.z);
	modelData.position.push_back(pos);
	modelData.normal.push_back(vec3(0, 0, 0));
      }

      else if (!strcmp(temp, "vn")) {
	vec3 normal;
	sscanf(coordinates[i]->c_str(), "vn %f %f %f", &normal.x, &normal.y, &normal.z);
	normals.push_back(normal);
      }

      else if (!strcmp(temp, "f ")) {

	ivec3 s1, s2, s3;
	sscanf(coordinates[i]->c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", &s1.x, &s1.y, &s1.z, &s2.x, &s2.y, &s2.z, &s3.x, &s3.y, &s3.z);

	modelData.normal[s1.x - 1] = normals[s1.z - 1];
	modelData.normal[s2.x - 1] = normals[s2.z - 1];
	modelData.normal[s3.x - 1] = normals[s3.z - 1];

	indices.push_back(s1.x - 1);
	indices.push_back(s2.x - 1);
	indices.push_back(s3.x - 1);
      }
    }

    for (unsigned int i = 0; i<coordinates.size(); i++) {
      delete coordinates[i];
    }
    modelData.indices = indices;
    return modelData;
  }
};


#endif
