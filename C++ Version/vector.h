/*
* Author: Harsh Patel
* File: vector.h
* Modified On: 11-14-15	
* Description: This header file contains vector Class definition
*              and method headers for vector operations   
* Note: vector operations are private on purpose
* Only use of overloaded operators allowed to operate on vectors
*/

#ifndef VECTOR_H
#define VECTOR_H

class Vector {
   private:
      double x;
      double y;
      double z;

      Vector add(Vector v);
      Vector subtract(Vector v);
      Vector scale(double s);
      double dot(Vector v);
   public:
     
      // constructors
      Vector();
      Vector(double, double, double);
      
      // mutators
      void setX(double);
      void setY(double);
      void setZ(double);

      // cringe if you will
      double get(int);
      
      // overloaded operators
      Vector operator+(Vector v);
      Vector operator-(Vector v);
      double operator*(Vector v);
      Vector operator*(double s);
      
      // other vector operations
      double len(void);
      void normalize(void);
      double compAdd(bool);
      Vector compDiv(Vector);
};

#endif
