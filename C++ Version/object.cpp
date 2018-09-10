/*
* object.cpp
* Author: Harsh Patel
* Date: 11-15-2015
* Defines relevant methods for the object class
*/

#include "object.h"
#include <cmath>


//initial value constructor
Object::Object(bool check, double rf, COLOR_T clr1, COLOR_T clr2) :
   checker( check ),
   reflect( rf ),
   color1( clr1 ),
   color2( clr2 )
{}

COLOR_T Object::getColor(Vector inter) {

   if (checker)
   {
      if ( ( (int)(inter.compAdd(true)) ) & 1)
         return color2;
   }
   return color1;   
}

double Object::getReflect() {
   return reflect;
}