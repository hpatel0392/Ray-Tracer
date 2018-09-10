 /* 
* rt.h
* Author: Harsh Patel
* Date: 12-1-2015
* The header file for the ray tracer with definitions for a ray, color and Image
*/ 
 
#ifndef RT_H
#define RT_H

#include "vector.h"

#define DEPTH 5
#define BLACK (COLOR_T){0.0, 0.0, 0.0}

typedef struct{
   Vector org;
   Vector dir;
} RAY_T;

typedef struct{
   double r;
   double g;
   double b;
} COLOR_T;

typedef struct{
   int x;
   int y;
   unsigned char **img;
} IMG_T;
        
#endif
