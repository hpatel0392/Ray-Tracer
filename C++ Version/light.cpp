/* 
* light.cpp
* Author: Harsh Patel
* Date: 11-15-2015
* Class definition for Light
*/

#include <cmath>
#include "light.h"
#include "rt.h"
#include "vector.h"
#include "object.h"
#include "scene.h"

// default constructor
Light::Light() :
   location( Vector() ),
   color( (COLOR_T){1.0, 1.0, 1.0} )
{}

// initial value
Light::Light(Vector loc, COLOR_T clr) :
   location( loc ),
   color( clr )
{}

/*
* illuminate
* calcualtes all lighting and updates color 
* returns the color
*/
COLOR_T Light::illuminate(COLOR_T objClr, RAY_T ray, SCENE_T scene, int obj, Vector inter, Vector norm, double rf) {

   COLOR_T ret = (COLOR_T){0.0, 0.0, 0.0};

   // checks for shadow
   if ( this->shadow(scene, inter, obj) )
      return ret;

   // calculate vecL and vecV
   Vector vecL = this->location - inter;
   double dL = vecL.len(); // for light attenuation
   vecL.normalize();

   // calculate diffuse lighting
   double dp = norm * vecL;
      
   // checks to make sure dp is greater than zero
   if (dp < 0)
      return ret;

   // Calculates and caps light attenuation
   double atten = (1.0 / ((.002 * (dL*dL)) + (.02 * dL) + .2) );
   if (atten > 1.0)
      atten = 1.0;

   double rScale = atten * this->color.r;
   double gScale = atten * this->color.g;
   double bScale = atten * this->color.b;

   ret.r += dp * objClr.r * rScale * (1.0 - rf);
   ret.g += dp * objClr.g * gScale * (1.0 - rf);
   ret.b += dp * objClr.b * bScale * (1.0 - rf);
   
   // calculate specular light
   Vector vecR = (vecL - (norm * (2 * dp)) );
   vecR.normalize();
   Vector vecV = (ray.org - inter);
   vecV.normalize();
 
   dp = vecR * vecV;

   ret.r += pow(dp, 100) * rScale;
   ret.g += pow(dp, 100) * gScale;
   ret.b += pow(dp, 100) * bScale;

   return ret;
}   


/*
* Tests for shadows 
* returns false for no shadows and true for shadows
*/
bool Light::shadow(SCENE_T scene, Vector inter, int current) {

   RAY_T shadow = (RAY_T){inter, this->location -  inter};
   double length = shadow.dir.len();
   shadow.dir.normalize();
   int i;
   double t;
   Vector dummy_inter, dummy_norm;

   for (i = 0; i < scene.numObjs; i++) {
      if(i != current)
      {
         if(scene.objs[i]->intersection(shadow, t, dummy_inter, dummy_norm) ){
            if(t < length)   
               return true;
        }
      }
   }
   return false; 
} 


