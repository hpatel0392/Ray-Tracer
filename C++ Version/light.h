/*
* light.h
* Author: Harsh Patel
* Date: 11-14-2015
* Declares the Light Class
*/

#ifndef LIGHT_H
#define LIGHT_H

#include "rt.h"
#include "vector.h"
#include "object.h"
#include "scene.h"

class Light {
   private:   
      Vector location; 
      COLOR_T color;

      bool shadow(SCENE_T, Vector, int);
   public:
      Light();
      Light(Vector, COLOR_T);
      COLOR_T illuminate(COLOR_T, RAY_T, SCENE_T, int, Vector, Vector, double);
};

#endif 
