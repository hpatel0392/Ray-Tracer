/*
* sphere.h
* Author: Harsh Patel
* Date: 11-14-2015
* Declares the class Sphere which is derived from Object
*/

#ifndef SPHERE_H
#define SPHERE_H

#include "object.h"
#include "vector.h"
#include "rt.h"

class Sphere : public Object {
   private:
   Vector center;
   double radius;

   public:
      Sphere(Vector, double, COLOR_T clr1, double);
      bool intersection(RAY_T, double&, Vector&, Vector&);
};

#endif
