/* 
* rt.h
* Author: Harsh Patel
* Date: 10-24-2015
* The header file for the ray tracer with definitions for a sphere, ray, color 
* and prototypes for associated function 
*/ 
 
#ifndef RT_H
#define RT_H

#include "vector.h"

#define NUM_OBJS 3
#define NUM_LIGHTS 1
#define X_RES 640
#define Y_RES 480

// structure definitions
typedef struct{
   VP_T ctr;
   double rad;
} SPHERE_T;

typedef struct{
   VP_T normal;
   double dist;
} PLANE_T;

typedef struct{
   VP_T org;
   VP_T dir;
} RAY_T;

typedef struct{
   double r;
   double g;
   double b;
} COLOR_T;

typedef struct OBJECT{
   COLOR_T color;
   COLOR_T color2;
   union{
      SPHERE_T sphere;
      PLANE_T plane;
   } shape;
   int (*intersect)(RAY_T ray, struct OBJECT obj, double *t, VP_T *inter, VP_T *norm);
} OBJECT_T;
     
typedef struct{
   OBJECT_T *objs;
   int numObjs;
   VP_T lights[NUM_LIGHTS];
   COLOR_T back;
   int x_res;
   int y_res;
} SCENE_T;
   
#endif
