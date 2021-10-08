#ifndef _VECTOR_H
#define _VECTOR_H

#include <math.h>

typedef struct{
    double x;
    double y;
    double z;
}vec3;

typedef vec3 point3;
typedef vec3 color;

vec3* set_v(double x, double y, double z, vec3* v);

vec3* add_v(vec3* u, vec3* v, vec3* result);
vec3* sub_v(vec3* u, vec3* v, vec3* result);
vec3* mul_v(vec3* v, double t, vec3* result);
vec3* div_v(vec3* v, double t, vec3* result);

double dot(vec3* u, vec3* v);
vec3* cross(vec3* u, vec3* v, vec3* result);

double length(vec3* u, vec3* v);
vec3* normalize(vec3* v, vec3* result);

#endif
