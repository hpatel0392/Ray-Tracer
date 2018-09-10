/*
* plane.h
* Author: Harsh Patel
* Date: 11-15-2015
* Class declaration for a plane, derived from object
*/

#ifndef PLANE_H
#define PLANE_H

#include "object.h"
#include "vector.h"
#include "rt.h"

class Plane : public Object {
   private:
   Vector normal;
   double distance;

   public:
      Plane(Vector, double, bool, COLOR_T, COLOR_T, double);
      bool intersection(RAY_T, double&, Vector&, Vector&);
};

#endif 
