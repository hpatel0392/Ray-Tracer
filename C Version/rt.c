/* 
* rt.c
* Author: Harsh Patel
* Date: 10-24-2015
* The ray tracer, displays a scene of objects with proper lighting and shadows 
*/ 
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vector.h"
#include "rt.h"
#include "sphere.h"
#include "light.h"
#include "plane.h"

void trace(RAY_T ray, SCENE_T scene, COLOR_T *color);
VP_T convert(int x, int y, SCENE_T scene);

/*
* Initialize
* Initializes the all of the components of the scene
* no return
*/
void init(SCENE_T *scene){

     
   scene->numObjs = NUM_OBJS;
   scene->lights[0] = (VP_T){5.0, 10.0, -2.0};
   scene->back = (COLOR_T){0.3, 0.3, 0.5};
   scene->x_res = X_RES;
   scene->y_res = Y_RES;
   
   int i;
   OBJECT_T *objs;
   objs = (OBJECT_T*)malloc(sizeof(OBJECT_T) * scene->numObjs);   

   /*
   * initialize color2.r for all objects to -1.0 (used in illuminate)
   * if color 2 is initialized after this, then no checker pattern is present
   * else checker pattern is present
   */
   for( i = 0; i < scene->numObjs; i++){
      objs[i].color2.r = -1.0;
   }
   
   //initialize objects
   objs[0].color = (COLOR_T){0.8, 0.0, 0.0};
   objs[0].shape.sphere = (SPHERE_T){{0.5, 0.8, 4.0}, 0.5};
   objs[0].intersect = rs_inter;

   objs[1].color = (COLOR_T){0.0, 0.8, 0.0};
   objs[1].shape.sphere = (SPHERE_T){{-0.5, 0.15, 4.2}, 0.6};
   objs[1].intersect = rs_inter;
 
   objs[2].color = (COLOR_T){0.0, 0.0, 0.0};
   objs[2].color2 = (COLOR_T){1.0, 1.0, 1.0};
   objs[2].shape.plane = (PLANE_T){vec_normalize((VP_T){0.0, 1.0, 0.0}), 0.9};
   objs[2].intersect = rp_inter;
      
 
   // initialize scene
   scene->objs = objs;
}


int main() {
   
   // loop control
   int x,y;

   // declare scene and initialize
   SCENE_T scene;  
   init(&scene);

   // Variables operated on, values are updated each loop
   RAY_T ray = {{0.0, 0.0, 0.0}};
   COLOR_T color;

   // Declare and open img.ppm or writing
   FILE *fp = fopen("img.ppm", "w");         
      
   // ppm header
   fprintf(fp, "P6\n%d %d\n255\n", scene.x_res, scene.y_res);
 
   // Start ray tracing 
   for(y = 0; y < scene.y_res; y++) {
      for(x = 0; x < scene.x_res; x++) { 
         
         ray.dir = vec_normalize(convert(x, y, scene));

         trace(ray, scene, &color);

         // cap color at 1.0
         if(color.r > 1.0)
         { color.r = 1.0;}
         if(color.g > 1.0)
         { color.g = 1.0;}
         if(color.b > 1.0)
         { color.b = 1.0;}

         // convert color to the 0-255 range
         unsigned char r = (unsigned char) (color.r * 255);
         unsigned char g = (unsigned char) (color.g * 255);
         unsigned char b = (unsigned char) (color.b * 255);
         fprintf(fp, "%c%c%c", r, g, b);
             
      }
   }

   // closes img.ppm
   fclose(fp);

   return 0;
}

/*
* Converts pixel location to image space location
*/
VP_T convert(int x, int y, SCENE_T scene) {
             
   VP_T dest;
   double x_res = (double) scene.x_res,
          y_res = (double) scene.y_res; 
 
   if(x_res >= y_res)
   {
      dest.x = (-0.5 * x_res/y_res) +  x/y_res;
      dest.y = 0.5 -  y/y_res;
   }
   else
   {
      dest.x = -0.5 +  x/x_res;
      dest.y = (0.5 * y_res/x_res) -  y/x_res;
   }
   dest.z = 1.0;

   return dest;
}

/*
* traces
*/ 
void trace(RAY_T ray, SCENE_T scene, COLOR_T *color) {
   
   double closest_t = 1000;
   int closest_obj = -1, i;
   VP_T cl_inter, cl_normal;

   // reset color each run
   *color = (COLOR_T){0.0, 0.0, 0.0};

   for(i = 0; i < scene.numObjs; i++){
      double t;
      VP_T inter, normal;

      // if intersect is found
      if (scene.objs[i].intersect(ray, scene.objs[i], &t, &inter, &normal))
      {
         if (t < closest_t)
         {
            closest_t = t;
            cl_inter = inter;
            cl_normal = normal;
            closest_obj = i;
         }
      }
   }

   // apply lighting effects if applicable
   if(closest_obj >= 0)
   { illuminate(color, ray, scene, closest_obj, cl_inter, cl_normal); }
   else
   { *color = scene.back; }
}
