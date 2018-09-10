/* 
* rt.cpp
* Author: Harsh Patel
* Date: 12-1-2015
* The advanced ray tracer, displays objects with several lightings and effects 
* and yes I actually used all of the inclusions
*/ 
 
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include "vector.h"
#include "rt.h"
#include "sphere.h"
#include "light.h"
#include "plane.h"
#include "box.h"
#include "scene.h"

using namespace std;

// prototypes
COLOR_T trace(RAY_T, SCENE_T, int);
COLOR_T add_lighting(RAY_T, SCENE_T, int, Vector, Vector, double);
void write_img(IMG_T, char* out);
void add_AntiA(IMG_T&, int);
void cleanUp(SCENE_T, IMG_T);
void init(SCENE_T*, char*);


int main(int argc, char* argv[]) {
   
   if(argc < 3)
   {
      cout<<"Error no files specified!\n";
      exit(-1);
   }

   // anti - aliasing only thing implemented so it only executes if >=4 arguements are present
   int AAScale = 1;
   if (argc >= 4)
      AAScale = 3;
   
   // loop control
   int x,y;

   // declare scene and initialize
   SCENE_T scene;  
   init(&scene, argv[1]);

   // Variables operated on, values are updated each loop
   RAY_T ray = {Vector(), Vector()};
   
   COLOR_T color;         
     
   // calculates startX ,startY and scale
   int x_res = (int) scene.startX * AAScale;
   int y_res = (int) scene.startY * AAScale;
   double scale;
   
   if(x_res >= y_res)
   {
      scale = scene.startY * AAScale;
      scene.startX = -0.5 * scene.startX/scene.startY;
      scene.startY = 0.5;
   }
   else
   {
      scale = scene.startX * AAScale;
      scene.startY = 0.5 * scene.startY/scene.startX;
      scene.startX = -0.5;
   }
 
   // instantiate the image
   IMG_T image = (IMG_T){x_res, y_res};
   image.img = new unsigned char*[image.y];
  
   // Start ray tracing 
   for(y = 0; y < y_res; y++) {
      
      image.img[y] = new unsigned char[(image.x*3)];
      
      for(x = 0; x < x_res; x++) { 
         
         ray.dir.setX(scene.startX + x/scale);
         ray.dir.setY(scene.startY - y/scale);
         ray.dir.setZ(1.0);
         ray.dir.normalize();

         color = trace(ray, scene, 0);

         // cap color at 1.0
         if(color.r > 1.0)
         { color.r = 1.0;}
         if(color.g > 1.0)
         { color.g = 1.0;}
         if(color.b > 1.0)
         { color.b = 1.0;} 
          
         // convert color to the 0-255 range
         image.img[y][x*3] = (unsigned char) (color.r * 255);
         image.img[y][x*3 +1] = (unsigned char) (color.g * 255);
         image.img[y][x*3 +2] = (unsigned char) (color.b * 255);       
      }
   }

   if(argc >= 4) 
      add_AntiA(image, AAScale);

   write_img(image, argv[2]);
   cleanUp(scene, image);

   return 0;
}

/*
* trace, returns color at the point in space
*/ 
COLOR_T trace(RAY_T ray, SCENE_T scene, int depth) {
   
   if (depth > DEPTH)
      return BLACK;
   
   int closest_obj = -1;
   double closest_t = 1000;
   int i;
   Vector cl_inter, cl_normal;

   for(i = 0; i < scene.numObjs; i++){
      double t;
      Vector inter, normal;

      // if intersect is found
      if (scene.objs[i]->intersection(ray, t, inter, normal))
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
   {
      double rf = scene.objs[closest_obj]->getReflect();
      COLOR_T rClr, localClr;
      if(rf > 0)
      {
         RAY_T R_ray = {cl_inter, ray.dir - (cl_normal * (ray.dir * cl_normal) * 2)};
         R_ray.dir.normalize();
         R_ray.org = R_ray.org + (R_ray.dir * 0.0001); 
         rClr = trace(R_ray, scene, depth+1);
      }
       
      localClr = add_lighting(ray, scene, closest_obj, cl_inter, cl_normal, rf);
      
      return (COLOR_T){ (rClr.r * rf) + (localClr.r*(1-rf)),
                        (rClr.g * rf) + (localClr.g*(1-rf)),
                        (rClr.b * rf) + (localClr.b) *(1-rf)}; // removed (1-rf) from here b/c image looked very off
   }
   else
   { return scene.back; }
} 


/*
* add lighting
* Lights the scene with multiple lights
* returns the final color
*/
COLOR_T add_lighting(RAY_T ray, SCENE_T scene, int obj, Vector inter, Vector normal, double rf) {

   int i;
   
   COLOR_T objClr = scene.objs[obj]->getColor(inter);
   COLOR_T lightClr, ret;  
  
   // calculate ambient lighting
   ret.r = objClr.r * 0.1;
   ret.g = objClr.g * 0.1;
   ret.b = objClr.b * 0.1;

   for(i = 0; i < scene.numLights; i++) {
      lightClr = scene.lights[i]->illuminate(objClr, ray, scene, obj, inter, normal, rf);

      ret.r += lightClr.r;  
      ret.g += lightClr.g;
      ret.b += lightClr.b;
   }
   
   return ret;
}    


/*
* write image
* writes the image to img.ppm
*/
void write_img(IMG_T image, char* out) {

   int y;

   // Declare and open output file for writing
   ofstream fp(out);  

   if(!fp.is_open())
   {
      std::cout<< "Error! cannot open specified output file!\n";
      exit(-1);
   }
      
   // ppm header
   fp << "P6\n" << image.x << " " << image.y << " " <<  "255\n";

   // write to file
   for(y = 0; y < image.y; y++){
      fp.write((char*) image.img[y], image.x*3);
   }
   
   // closes img.ppm
   fp.close();
}

/*
* Add Anti-Aliasing
* takes the supersample and reduces it to correct dimensions
* probably incredibly inefficient but it does the job.
* no return
*/
void add_AntiA(IMG_T &image, int AAScale) {
   int x, y, x2, y2;
   double r, g, b;

   image.x /= AAScale;
   image.y /= AAScale;

   unsigned char **temp = new unsigned char*[image.y];

   for(y = 0; y < image.y; y++) {
      
      temp[y] = new unsigned char[(image.x*3)];
      
      for(x = 0; x < image.x * 3; x+=3) {
         
         r = g = b = 0.0;

         for(y2 = y*3; y2 < (y*3)+2; y2++) {
            for(x2 = x*3; x2 < (x*3) + 7 ; x2+=3) {

                  r += image.img[y2][x2] / 255.0;
                  g += image.img[y2][x2+1] / 255.0;
                  b += image.img[y2][x2+2] / 255.0;
            }
         }
         
         // tampered with this b/c final image was duller
         r *= 1.5 / 9.0;
         g *= 1.5 / 9.0;
         b *= 1.5 / 9.0;

         // cap color at 1.0
         if(r > 1.0)
         { r = 1.0;}
         if(g > 1.0)
         { g = 1.0;}
         if(b > 1.0)
         { b = 1.0;} 

         temp[y][x] = (unsigned char)( r * 255); 
         temp[y][x+1] = (unsigned char)( g * 255);
         temp[y][x+2] = (unsigned char)( b * 255);
      }
   }

   delete image.img;

   image.img = new unsigned char*[image.y];
   for(y = 0; y < image.y; y++) {
      image.img[y] = new unsigned char[(image.x*3)];
      for(x = 0; x < image.x * 3; x+=3) {
         image.img[y][x] = temp[y][x]; 
         image.img[y][x+1] = temp[y][x+1];
         image.img[y][x+2] = temp[y][x+2]; 
      }
   }
   
   delete temp;

}


/*
* CleanUp
* frees all dynamically allocated memory
*/
void cleanUp(SCENE_T scene, IMG_T image) {
   scene.objs.clear();
   scene.lights.clear();
   delete image.img;
}


/*
* Initialize
* Initializes the all of the components of the scene
* no return
*/
void init(SCENE_T *scene, char* in){
     
   ifstream fp(in);

   if(!fp.good())
   {
      cout<< "Error! specified input file does not exist!\n";
      exit(-1);
   }

   const string options[] = {string("width"), string("height"), string("background"), 
                             string("sphere"),string("plane"), string("box") };
   
   const int vals[] = {options[0].compare(options[0]), options[1].compare(options[0]), 
                       options[2].compare(options[0]), options[3].compare(options[0]),
                       options[4].compare(options[0]), options[5].compare(options[0]),
                       options[6].compare(options[0]) };
   
   int numObjs = 0, numLights = 0, check;
   string header, current;
   Vector v1, v2;
   double dist = 0.0, rf = 0.0, d[3] = {0.0, 0.0, 0.0};
   COLOR_T clr1, clr2;
   bool flag = false, ineedsleep = true;

   // shield your eyes
   while( getline(fp, header) ){
      
      flag = false;
      check = header.compare(options[0]);
  
      if( check == vals[0] ) // width
      {
         getline(fp, current);
         scene->startX = atoi(current.c_str());
         getline(fp, header);
         continue;
      }
      else if( check == vals[1] ) // height
      {
         getline(fp, current);
         scene->startY = atoi(current.c_str());
         getline(fp, header);
         continue;
      }
      else if( check == vals[2] && ineedsleep) // background
      {
         getline(fp, current);
         sscanf(current.c_str(), "%lf %lf %lf", &clr1.r, &clr1.g, &clr1.b);
         scene->back = clr1;
         getline(fp, header);
         ineedsleep = false;
         continue;
      }
      else if( check == vals[3] || check == vals[4] || check == vals[5] ) // object
      {
         numObjs++;         

         getline(fp, current);
         sscanf(current.c_str(), "%lf %lf %lf", &d[0], &d[1], &d[2]);
         v1 = Vector(d[0], d[1], d[2]);
        

         getline(fp, current);
         if(current.size() < 10) // approx
         { dist = atof(current.c_str()); }
         else
         {
            sscanf(current.c_str(), "%lf %lf %lf", &d[0], &d[1], &d[2]);
            v2 = Vector(d[0], d[1], d[2]);
         }


         getline(fp, current);
         sscanf(current.c_str(), "%lf %lf %lf", &clr1.r, &clr1.g, &clr1.b);


         getline(fp, current);
         if(current.size() < 10)
         { rf = atof(current.c_str());}
         else
         { 
            sscanf(current.c_str(), "%lf %lf %lf", &clr2.r, &clr2.g, &clr2.b); 
            flag = true;
         }


         getline(fp, current);
         if(!current.length())
         {
            if(check == vals[3])
            { 
               scene->objs.push_back( new Sphere( v1, dist, clr1, rf) ); 
               continue;
            }
            else if(check == vals[4])
            {
               scene->objs.push_back( new Plane( v1, dist, flag, clr1, clr1, rf) ); 
               continue;
            }
            else if(check == vals[5])
            {
               scene->objs.push_back( new Box(v1, v2, flag, clr1, clr1, rf) );
               continue;
            }
         }
         else
         {
            rf = atof(current.c_str()); 
            if(check == vals[4])
            {
               scene->objs.push_back( new Plane( v1, dist, flag, clr1, clr2, rf) ); 
               getline(fp, header);
               continue;    
            }
            else if(check == vals[5])
            {
               scene->objs.push_back( new Box(v1, v2, flag, clr1, clr2, rf) );
               getline(fp, header);
               continue;
            }
         }      
      }  
      else
      {
         numLights++;
         getline(fp, current);
         sscanf(current.c_str(), "%lf %lf %lf", &d[0], &d[1], &d[2]);
         v1 = Vector(d[0], d[1], d[2]);
         getline(fp, current);
         sscanf(current.c_str(), "%lf %lf %lf", &clr1.r, &clr1.g, &clr1.b);
         scene->lights.push_back( new Light(v1, clr1) );
         getline(fp, header);
         continue;
     }
   }

   scene->numObjs = numObjs;
   scene->numLights = numLights;
     
   fp.close();
}