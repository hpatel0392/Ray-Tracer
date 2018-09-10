/* 
* light.c
* Author: Harsh Patel
* Date: 10-27-2015
* Defines light related functions
*/

#include <stdio.h>
#include <math.h>
#include "light.h"

/*
* illuminate
* calcualtes all lighting and updates color 
* no return
*/
void illuminate(COLOR_T *color, RAY_T ray, SCENE_T scene, int obj, VP_T inter, VP_T norm) {

   COLOR_T objClr = scene.objs[obj].color;

   // checks for checkerboard (if color2.r was changed) and sets to correct color
   if ( scene.objs[obj].color2.r != -1.0 )
   {   
      if ( ( (int)(floor(inter.x) + floor(inter.y) + floor(inter.z)) ) & 1)
      { objClr = scene.objs[obj].color2; }
   }

   VP_T light = scene.lights[0];
  
   // calculate vecL and vecV
   VP_T vecL = (vec_subtract(light, inter));
   double dL = vec_len(vecL); // for light attenuation
   vecL = vec_normalize(vecL);
   VP_T vecV = vec_normalize(vec_subtract(ray.org, inter));


   // calculate ambient lighting
   color->r += objClr.r * 0.1;
   color->g += objClr.g * 0.1;
   color->b += objClr.b * 0.1;

   // checls for shadow
   if (!shadow(scene, inter, obj) )
   {
      // calculate diffuse lighting
      double dp = vec_dot(norm, vecL);
      
      // Calculates light attenuation
      double atten = (1.0 / ((.002 * (dL*dL)) + (.02 * dL) + .2) );

      // checks to make sure dp is between 0 and 1
      if (dp > 0)
      {
         color->r += dp * objClr.r * atten;
         color->g += dp * objClr.g * atten;
         color->b += dp * objClr.b * atten;
   
         // calculate specular light
         VP_T vecR = vec_normalize(vec_subtract(vecL, vec_scale(norm, 2 * dp)));
 
         dp = vec_dot(vecR, vecV);

         color->r += pow(dp, 100) * atten;
         color->g += pow(dp, 100) * atten;
         color->b += pow(dp, 100) * atten;
      }

   }

}   


/*
* Tests for shadows 
* returns 0 for no shadows and 1 for shadows
*/
static int shadow(SCENE_T scene, VP_T inter, int current) {

   RAY_T shadow = {inter, vec_normalize(vec_subtract(scene.lights[0], inter))};
   int i;
   double t;
   VP_T dummy_inter, dummy_norm;

   for (i = 0; i < scene.numObjs; i++) {
      if(i != current)
      {
         if(scene.objs[i].intersect(shadow, scene.objs[i], &t, &dummy_inter, &dummy_norm) ){
            if(t < vec_len(shadow.dir))   
               return 1;
        }
      }
   }
   return 0; 
}
