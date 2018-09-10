/*
* sphere.cpp
* Author: Harsh Patel
* Date: 11-15-2015
* Defines sphere's methods
*/

#include <cmath>
#include "sphere.h"
#include "rt.h"

//initial value constructor
Sphere::Sphere(Vector ctr, double rad, COLOR_T clr, double rf) :
   center( ctr ),
   radius( rad ),
   Object(false, rf, clr, clr)
{}

/*
* intersection
* calculates whether the ray intersects the sphere at a particular location
* returns false if no interection is found, true if intersection is found
* also sets value of t and calulates intersection point (inter)
* and normal vector (norm) if intersection is found
*/
bool Sphere::intersection(RAY_T ray, double &t, Vector &inter, Vector &norm) {

   // compute a, b, and c to solve using the quadratic formula
   double a = 1, b, c;

   Vector v = ray.org - center;

   b = 2.0 * (ray.dir * v);

   c = (v * v) - pow(radius, 2);

   // calculate the discriminant
   double disc = b*b - 4.0*a*c;
 
   // if the discriminant is < 0 , stop
   if (disc < 0) 
      return false; 
   
   double t0, t1;

   // apply quadtratic formula
   t0 = ((-b) - sqrt(disc)) / (2*a); 
   t1 = ((-b) + sqrt(disc)) / (2*a);
  
   // stop if both solutions are invalid ( <0 )
   if (t0 < 0 && t1 < 0)
      return false;
      
   // select the smaller positive solution
   if (t0 < 0)
   { t = t1; }
   else if (t1 < 0)
   { t = t0; }
   else if (t0 < t1)
   { t = t0; }
   else 
   { t = t1; }

   // calculate
   inter = ray.org + (ray.dir * (t));
   norm = (inter - center) * ( 1.0/ radius) ;
   norm.normalize();
    
   return true;
}