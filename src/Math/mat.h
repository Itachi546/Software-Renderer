#ifndef MATRIX_H
#define MATRIX_H

#include "vec3.h"
#include <iostream>
#include <cmath>

/* class mat2{ */
/*  public: */
/*   static mat2 rotate(float angle){ */

/*     mat2 result; */
/*     result.m[0][0] = cos(angle); */
/*     result.m[0][1] = sin(angle); */
/*     result.m[1][0] = -sin(angle); */
/*     result.m[1][1] = cos(angle); */

/*     return result; */
/*   } */
/*     friend vec2 operator*(mat2 mat, vec2 v){ */
/*       vec2 result; */
/*       result.x = mat.m[0][0] * v.x + mat.m[0][1] * v.y; */
/*       result.y = mat.m[1][0] * v.x + mat.m[1][1] * v.y; */

/*       return result; */
/*     } */
  
/*  private: */
/*   float m[2][2]; */
/* }; */


class mat3{


public:
  static mat3 rotate(float angle){
    mat3 m;
    angle = ((angle) * M_PI)/180.0f;

    m.m[0][0] = cos(angle);
    m.m[0][1] = 0;
    m.m[0][2] = -sin(angle);

    m.m[1][0] = 0;
    m.m[1][1] = 1;
    m.m[1][2] = 0;

    m.m[2][0] = sin(angle);
    m.m[2][1] = 0;
    m.m[2][2] = cos(angle);

    return m;
  }

  friend vec3 operator*(mat3 m, vec3 v){
    vec3 result;
    result.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0];
    result.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1];
    result.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2];    

    return result;
  }
private:
  float m[3][3];
  
};

class mat4{
private:
  float m[4][4];
  
public:
  mat4(){
   
  }
  static mat4 perspective(float fov, float aspectRatio, float nearPlane = 0.1f, float farPlane = 100.0f){
    mat4 result;
    
    float d = 1.0f/tan((fov/2.0f) * (M_PI/180.0f));    
    
    result.m[0][0] = (d/aspectRatio);
    result.m[0][1] = 0;
    result.m[0][2] = 0;
    result.m[0][3] = 0;

    result.m[1][0] = 0;
    result.m[1][1] = d;
    result.m[1][2] = 0;
    result.m[1][3] = 0;

    float diff = farPlane - nearPlane;
  
    result.m[2][0] = 0;
    result.m[2][1] = 0;
    result.m[2][2] = -farPlane / diff;
    result.m[2][3] = -1;

    result.m[3][0] = 0;
    result.m[3][1] = 0;
    result.m[3][2] = -(nearPlane * farPlane) / diff;
    result.m[3][3] = 0;

    return result;
  }

  friend vec3 operator*(mat4 matrix, vec3 in){


    vec3 out;
    out.x   = in.x * matrix.m[0][0] + in.y * matrix.m[1][0] + in.z * matrix.m[2][0] + /* in.z = 1 */ matrix.m[3][0]; 
    out.y   = in.x * matrix.m[0][1] + in.y * matrix.m[1][1] + in.z * matrix.m[2][1] + /* in.z = 1 */ matrix.m[3][1]; 
    out.z   = in.x * matrix.m[0][2] + in.y * matrix.m[1][2] + in.z * matrix.m[2][2] + /* in.z = 1 */ matrix.m[3][2]; 
    float w = in.x * matrix.m[0][3] + in.y * matrix.m[1][3] + in.z * matrix.m[2][3] + /* in.z = 1 */ matrix.m[3][3]; 

    // normatrix.malize if w is different than 1 (convert fromatrix.m homatrix.mogeneous to Cartesian coordinates)

    if (w != 1) { 
        out.x /= w; 
        out.y /= w; 
        out.z /= w; 
    }

    return out;
  }
};

#endif


