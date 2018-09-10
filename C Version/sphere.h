/*
* sphere.h
* Author: Harsh Patel
* Date: 10-24-2015
* includes function prototypes related to the sphere object
*/

#ifndef SPHERE_H
#define SPHERE_H

#include "vector.h"
#include "rt.h"

int rs_inter(RAY_T ray, OBJECT_T obj, double *t, VP_T *inter, VP_T *normal);

#endif
