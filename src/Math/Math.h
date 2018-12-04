#ifndef MATH_H
#define MATH_H

#include "vec2.h"

struct Vertex2d{
  vec2 position;
  vec3 color;

  Vertex2d(){}
  Vertex2d(vec2 position, vec3 color) : position(position), color(color){}
};





#endif
