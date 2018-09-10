/*
* plane.h
* Author: Harsh Patel
* Date: 10-27-2015
* header file for plane related functions
*/

#ifndef PLANE_H
#define PLANE_H

#include "rt.h"

int rp_inter(RAY_T ray, OBJECT_T obj, double *t, VP_T *inter, VP_T *norm);

#endif
