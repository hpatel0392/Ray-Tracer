/*
* plane.c
* Author: Harsh Patel
* Date: 10-27-2015
* Definitions for plane related functions
*/

#include "plane.h"

/*
* ray-plane intersect
* Checks to see if the ray intersects the plane
* if intersection is found, t is set and inter and norm are computed and set
* returns 0 if no intersection occurs, or 1 if intersection occurs
*/
int rp_inter(RAY_T ray, OBJECT_T obj, double *t, VP_T *inter, VP_T *norm) {

   PLANE_T plane = obj.shape.plane;

   double dot_dir = vec_dot(plane.normal, ray.dir);
   double dot_org = vec_dot(plane.normal, ray.org);
 
   // if dot_dir == 0 , stop
   if( dot_dir == 0 )
   { return 0; }

   *t = -(dot_org + plane.dist)/dot_dir;

   // stop if t < 0
   if ( *t < 0 ) 
   { return 0; }

   vec_copy(inter, vec_add(ray.org, vec_scale(ray.dir, *t)));
   vec_copy(norm, plane.normal);

   return 1;
}
       
