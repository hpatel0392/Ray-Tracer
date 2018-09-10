/*
* object.h
* Author: Harsh Patel
* Date: 11-14-2015
* The class definition for an ... Object. hah!
*/

#ifndef OBJECT_H
#define OBJECT_H

#include "rt.h"
#include "vector.h"

class Object {
   private:
      bool checker;
      double reflect;
      COLOR_T color1;
      COLOR_T color2;

   public:
      
      // constructors
      Object(bool, double, COLOR_T, COLOR_T);
    
      COLOR_T getColor(Vector);
      double getReflect();
      virtual bool intersection(RAY_T, double&, Vector&, Vector&){};
};

#endif
