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

const vec3 origin = {0.0, 0.0, 0.0};

void set_v(double x, double y, double z, vec3* v);

void add_v(vec3* u, vec3* v, vec3* result);
void sub_v(vec3* u, vec3* v, vec3* result);
void mul_v(vec3* v, double t, vec3* result);

double dot(vec3* u, vec3* v);
void cross(vec3* u, vec3* v, vec3* result);

double length(vec3* u, vec3* v);

#endif
