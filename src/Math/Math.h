#ifndef MATH_H
#define MATH_H

#include "vec2.h"

struct Vertex3d{
  vec3 position;
  vec3 color;

  Vertex3d(){}
  Vertex3d(vec3 position, vec3 color) : position(position), color(color){}
};





#endif
