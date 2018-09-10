/*
* sphere.c
* Author: Harsh Patel
* Date: 10-24-2015
* Defines sphere functions
*/

#include <math.h>
#include "sphere.h"
#include "rt.h"

/*
* ray-sphere intersect - rs_inter
* calculates whether the ray intersects the sphere at a particular location
* returns 0 if no interection is found, 1 if intersection is found
* also sets value of t and calulates intersection point (inter)
* and normal vector (norm) if intersection is found
*/
int rs_inter(RAY_T ray, OBJECT_T obj, double *t, VP_T *inter, VP_T *norm) {

   SPHERE_T sph = (SPHERE_T) obj.shape.sphere;

   // compute a, b, and c to solve using the quadratic formula
   double a = 1, b, c;

   b = 2 * (ray.dir.x * (ray.org.x - sph.ctr.x) + 
          ray.dir.y * (ray.org.y - sph.ctr.y) + 
          ray.dir.z * (ray.org.z - sph.ctr.z));

   c = pow(ray.org.x - sph.ctr.x, 2) + 
       pow(ray.org.y - sph.ctr.y, 2) + 
       pow(ray.org.z - sph.ctr.z, 2) - 
       pow(sph.rad, 2);

   // calculate the discriminant
   double disc = b*b - 4.0*a*c;
 
   // if the discriminant is < 0 , stop
   if (disc < 0) 
   { return 0; }
   
   double t0, t1;

   // apply quadtratic formula
   t0 = ((-b) - sqrt(disc)) / (2*a); 
   t1 = ((-b) + sqrt(disc)) / (2*a);
  
   // stop if both solutions are invalid ( <0 )
   if (t0 < 0 && t1 < 0)
   { return 0; }
      
   // select the smaller positive solution
   if (t0 < 0)
   {  *t = t1; }
   else if (t1 < 0)
   { *t = t0; }
   else if (t0 < t1)
   { *t = t0; }
   else 
   { *t = t1; }

   // calculate
   vec_copy(inter, vec_add(ray.org, vec_scale(ray.dir, *t)) );
   vec_copy(norm,  vec_normalize(vec_scale(vec_subtract(*inter, sph.ctr), 1/sph.rad) ));
    
   return 1;
}

