/*
* box.cpp
* Author: Harsh Patel
* Date: 12-5-2015
* Box's method definitions
*/

#include "box.h"
#include "rt.h"
#include "vector.h"


// checkered plane constructor
Box::Box(Vector min, Vector max, bool check, COLOR_T clr1, COLOR_T clr2, double rf) :
   lowL( min ),
   upR( max ), 
   Object( check, rf, clr1, clr2 )   
{}


/*
* intersection
* Checks to see if the ray intersects the box
* if intersection is found, t is set and inter and norm are computed and set
* returns false if no intersection occurs, or true if intersection occurs
*/
bool Box::intersection(RAY_T ray, double &t, Vector &inter, Vector &norm) {

   static const Vector normals[6] = { Vector(-1.0, 0, 0), Vector(1.0, 0, 0), Vector(0, -1.0, 0),
                                      Vector(0, 1.0, 0), Vector(0, 0, -1.0), Vector(0, 0, 1.0) };

   double tNear = -1, tFar = 1000;
   int i, nIndex;

   for(i = 0; i < 3; i++) {
      if (ray.dir.get(i) == 0.0)
      {
         if(ray.org.get(i) < this->lowL.get(i) || ray.org.get(i) > this->upR.get(i) )
         {
            return false;
         }
      }
   }

   Vector vecT1 = (this->lowL - ray.org).compDiv(ray.dir);
   Vector vecT2 = (this->upR - ray.org).compDiv(ray.dir);
   int swapFlag;
   double t1, t2, temp;
  
   for(i = 0; i < 3; i++) {
      
      t1 = vecT1.get(i);
      t2 = vecT2.get(i); 
      swapFlag = 0; 
   
      if( t1 > t2 )
      { 
         temp = t2;
         t2 = t1;
         t1 = temp;
         swapFlag = 1;
      }

      if( t1 > tNear)
      {
         tNear = t1;
         nIndex = i * 2 + swapFlag;
      }

      if( t2 < tFar)
         tFar = t2;

      if( tNear > tFar)
         return false;
     
      if( tFar < 0)
         return false;
   }

   // compute inter and norm
   t = tNear;
   inter = ray.org + ray.dir * t;
   norm = normals[nIndex];

   return true;
}