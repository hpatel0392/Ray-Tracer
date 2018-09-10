/*
* scene.h
* Author : Harsh Patel
* Date: 11-19-2015
* Holds the Scene type structure
*/

#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "object.h"
#include "light.h"
#include "rt.h"

class Light;
typedef struct{
   std::vector<Object*> objs;
   int numObjs;
   std::vector<Light*> lights;
   int numLights;
   COLOR_T back;
   double startX;
   double startY;
} SCENE_T;

#endif
