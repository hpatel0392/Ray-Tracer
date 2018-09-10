/*
* plane.cpp
* Author: Harsh Patel
* Date: 11-15-2015
* Plane's method definitions
*/

#include "plane.h"
#include "rt.h"
#include "vector.h"


// checkered plane constructor
Plane::Plane(Vector norm, double dist, bool check, COLOR_T clr1, COLOR_T clr2, double rf) :
   normal( norm ),
   distance( dist ), 
   Object( check, rf, clr1, clr2 )   
{ this->normal.normalize(); }


/*
* intersection
* Checks to see if the ray intersects the plane
* if intersection is found, t is set and inter and norm are computed and set
* returns false if no intersection occurs, or true if intersection occurs
*/
bool Plane::intersection(RAY_T ray, double &t, Vector &inter, Vector &norm) {

   double dot_dir = normal * ray.dir;
   double dot_org = normal * ray.org;
 
   // if dot_dir == 0 , stop
   if( dot_dir == 0 )
      return false; 

   t = -(dot_org + distance ) / dot_dir;

   // stop if t < 0
   if ( t < 0 ) 
      return false;

   inter = ray.org + ray.dir * (t);
   norm =  normal;

   return true;
}