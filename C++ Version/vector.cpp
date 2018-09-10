/*
* Author: Harsh Patel
* File: vector.cpp 
* Modified On: 11-14-15 
* Description: Defines methods for the Vector class 
* Note: vector operations are private on purpose
* Only use of overloaded operators allowed to operate on vectors
*/

#include <cmath>
#include "vector.h"

/* 
* default constructor
* initializes to zero vector
*/
Vector::Vector() :
   x(0.0),
   y(0.0),
   z(0.0)
{}

//Initial value constructor
Vector::Vector(double x1, double y1, double z1) :
   x(x1),
   y(y1),
   z(z1)
{}



// Private methods - these are only called by overloaded operators

Vector Vector::add(Vector v) {  
   v.x += this->x;
   v.y += this->y;
   v.z += this->z;

   return v; 
}

Vector Vector::subtract(Vector v) {   

   // scale v by -1 and then add to "this"
   v = v.scale(-1.0);

   return this->add(v); 
}

Vector Vector::scale(double s) {
   return Vector(x * s, y * s, z * s); 
}

double Vector::dot(Vector v) {
   return (this->x * v.x ) + (this->y * v.y) + (this->z * v.z);
}


// mutators

void Vector::setX(double x1) {
    this->x = x1;
}

void Vector::setY(double y1) {
   this->y = y1;
}

void Vector::setZ(double z1) {
   this->z = z1;
}

// accessor 
double Vector::get(int i) {
   switch(i){
      case 0:
         return x;
      case 1:
         return y;
      case 2:
         return z;
   }
}
 
     
// overloaded operators

Vector Vector::operator+(Vector v) {
   return this->add(v);
}

Vector Vector::operator-(Vector v) {
   return this->subtract(v);
}

// Dot product - Vector * Vector
double Vector::operator*(Vector v) {
   return this->dot(v);
}

// scale - Vector * double
Vector Vector::operator*(double s) {
   return this->scale(s);
}


// other vector operations

double Vector::len() {
   return sqrt( x*x + y*y + z*z);
}

void Vector::normalize() {
   *this = this->scale(1.0 / this->len());
}

/*
* Component addition
* parameter false - normal component addition
* parameter true - floored component addition (used in Object.cpp)
*/
double Vector::compAdd(bool fl) {
   if (fl)
      return ( floor(x) + floor(y) + floor(z) );
   return x + y + z;
}

/*
* Component scale
* individualy scale each component of a vector 
*/
Vector Vector::compDiv(Vector sc) {
   
   Vector ret;
   ret.x = this->x / sc.x;
   ret.y = this->y / sc.y;
   ret.z = this->z / sc.z;
 
   return ret;  
}