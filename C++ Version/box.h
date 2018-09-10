/*
* box.h
* Author: Harsh Patel
* Date: 12-5-2015
* Class declaration for a Box, derived from object
*/

#ifndef BOX_H
#define BOX_H

#include "object.h"
#include "vector.h"
#include "rt.h"

class Box : public Object {
   private:
   Vector lowL;
   Vector upR;

   public:
      Box(Vector, Vector, bool, COLOR_T, COLOR_T, double);
      bool intersection(RAY_T, double&, Vector&, Vector&);
};

#endif 
