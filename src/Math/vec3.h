#ifndef VEC3_H
#define VEC3_H


#define _USE_MATH_DEFINES

#include <cmath>
#include <iostream>
#include <cassert>

#define EPSILON 0.000001
#define Assert(msg) \
  std::cout << __FILE__ <<" " << __LINE__ << " " << msg <<  std::endl;\
  assert(0);


class vec3{

 public:
  vec3(float _x, float _y, float _z){
    x = _x;
    y = _y;
    z = _z;
  }

  vec3(){}

  vec3(const vec3& v){
    x = v.x;
    y = v.y;
    z = v.z;
  }


  inline  float lengthSquared() const{
    return ( x * x + y * y);
  }

  inline  float length() const {
    return sqrtf( x * x + y * y + z * z);
  }

  static float length(const vec3& v)  {
    return sqrtf( v.x * v.x + v.y * v.y + v.z * v.z);
  }

  static vec3 normalize(const vec3 v) {
    float len = vec3::length(v);
    if(fabs(len) <= EPSILON){
      Assert("Divide By Zero");
    }
    vec3 result;
    float invLength = 1 / len;
    result.x = v.x * invLength;
    result.y = v.y * invLength;
    result.z = v.z * invLength;

    return result;
  }

  friend std::ostream& operator<<(std::ostream& os, vec3 v){
    os << v.x << " " << v.y << " " << v.z;
    return os;
  }
  
  static float dot(const vec3& v1, const vec3& v2) {
    return(v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
  }
 

  static vec3 cross(const vec3& v1, const vec3& v2){
    vec3 result;
    result.x = v1.y * v2.z - v2.y * v1.z;
    result.y = v1.z * v2.x - v1.x * v2.z;
    result.z = v1.x * v2.y - v2.x * v1.y;

    return result;
  }
 
  vec3 operator+(const vec3& v) {
    return vec3(x+v.x, y+v.y, z + v.z);
  }

  vec3 operator-(const vec3& v){
    return vec3(x-v.x, y-v.y, z - v.z);
  }

  vec3 operator*(float scalar){
    return vec3(x * scalar, y * scalar, z * scalar);
  }
  
  vec3 operator/(float scalar){
    if(fabs(scalar) < EPSILON){
      Assert("Divide By Zero");
    }
    return vec3(x / scalar, y / scalar, z/scalar);
  }

  vec3 operator+=(const vec3& v){
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }

  vec3 operator-=(const vec3& v){
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
  }

  vec3 operator-=(float scalar){
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
  }

  friend vec3 operator+(const vec3& v1, const vec3& v2){
    return vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
  }

  friend vec3 operator-(const vec3& v1, const vec3& v2) {
    return vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
  }

  friend vec3 operator*(const vec3& v1, float scalar){
    return vec3(v1.x * scalar, v1.x * scalar, v1.z * scalar);
  }

  
  float x;
  float y;
  float z;
};

#endif
