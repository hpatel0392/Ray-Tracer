/*
* Author: Harsh Patel
* File: vector.h
* Modified On: 9-24-15	
* Description: This header file contains vector definitions and
*              prototype statements for 3-D vector operations   
*/

#ifndef VECTOR_H
#define VECTOR_H

// Structure definition for a vector
typedef struct 
{
   double x;
   double y;
   double z;
} VP_T;


/* Prototype Statements */
VP_T vec_add(VP_T  v1, VP_T  v2);
VP_T vec_subtract(VP_T v1, VP_T v2);
VP_T vec_scale(VP_T v, double scale);
double vec_dot(VP_T v1, VP_T v2);
double vec_len(VP_T v);
VP_T vec_normalize(VP_T v);
void vec_copy(VP_T *result_v, VP_T v);

#endif
