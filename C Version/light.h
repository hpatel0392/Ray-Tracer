/*
* light.h
* Author: Harsh Patel
* Date: 10-24-2015
* includes prototypeslighting related functions
*/

#ifndef LIGHT_H
#define LIGHT_H

#include "rt.h"
#include "vector.h"

void illuminate(COLOR_T *color, RAY_T ray, SCENE_T scene, int obj, VP_T inter, VP_T norm);
static int shadow(SCENE_T scene, VP_T inter, int current);

#endif
