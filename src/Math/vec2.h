#ifndef VEC2_H
#define VEC2_H

#include <cmath>
#include "vec3.h"

class vec2{

public:

  vec2(float _x, float _y){
    x = _x;
    y = _y;
  }

  vec2(const vec3& v){
    x = v.x;
    y = v.y;
  }

  vec2(){}

  vec2(const vec2& v){
    x = v.x;
    y = v.y;
  }

  inline  float lengthSquared() const{
    return ( x * x + y * y);
  }

  inline  float length() const {
    return sqrtf( x * x + y * y);
  }
  
  static vec2 abs(vec2 v){
    return vec2(fabs(v.x), fabs(v.y));
  }
  static float length(const vec2& v)  {
    return sqrtf( v.x * v.x + v.y * v.y);
  }
  static vec2 normalize(const vec2 v) {
    float len = vec2::length(v);
    if(fabs(len) <= EPSILON){
      Assert("Divide By Zero");
    }
    vec2 result;
    float invLength = 1 / len;
    result.x = v.x * invLength;
    result.y = v.y * invLength;

    return result;
  }

 friend std::ostream& operator<<(std::ostream& os, vec2 v){
   os << v.x << " " << v.y;
   return os;
  }
  
 static float dot(const vec2& v1, const vec2& v2) {
    return(v1.x * v2.x + v1.y * v2.y);
  }

 static float cross(const vec2& v1, const vec2& v2){
   return(v1.x * v2.y - v2.x * v1.y);
 }

  vec2 operator+(const vec2& v) {
    return vec2(x+v.x, y+v.y);
  }
  vec2 operator-(const vec2& v){
    return vec2(x-v.x, y-v.y);
  }
  vec2 operator*(float scalar){
    return vec2(x * scalar, y * scalar);
  }
  vec2 operator/(float scalar){
    if(fabs(scalar) < EPSILON){
      Assert("Divide By Zero");
    }
    return vec2(x / scalar, y / scalar);
  }

  vec2 operator+=(const vec2& v){
    x += v.x;
    y += v.y;
    return *this;
  }

  vec2 operator-=(const vec2& v){
    x -= v.x;
    y -= v.y;
    return *this;
  }

  vec2 operator-=(float scalar){
    x *= scalar;
    y *= scalar;
    return *this;
  }

  friend vec2 operator+(const vec2& v1, const vec2& v2){
    return vec2(v1.x + v2.x, v1.y + v2.y);
  }

  friend vec2 operator-(const vec2& v1, const vec2& v2) {
    return vec2(v1.x - v2.x, v1.y - v2.y);
  }

  friend vec2 operator*(const vec2& v1, float scalar){
    return vec2(v1.x * scalar, v1.x * scalar);
  }

  
  float x;
  float y;
};


#endif




