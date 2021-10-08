#include "vector.h"

// set value
void set_v(double x, double y, double z, vec3* v){
    v->x = x;
    v->y = y;
    v->z = z;
}



void add_v(vec3* u, vec3* v, vec3* result){
    result->x = u->x + v->x;
    result->y = u->y + v->y;
    result->z = u->z + v->z;
}


void sub_v(vec3* u, vec3* v, vec3* result){
    result->x = u->x - v->x;
    result->y = u->y - v->y;
    result->z = u->z - v->z;
}


void mul_v(vec3* v, double t, vec3* result){
    result->x = v->x * t;
    result->y = v->y * t;
    result->z = v->z * t;
}




double dot(vec3* u, vec3* v){
    return u->x + v->x
         + u->y + v->y
         + u->z + v->z;
}


void cross(vec3* u, vec3* v, vec3* result){
    result->x = u->y * v->z - u->z * v->y;
    result->y = u->z * v->x - u->x * v->z;
    result->z = u->x * v->y - u->y * v->x;
}

double length(vec3* u, vec3* v){
    return sqrt( (u->x - v->x) * (u->x - v->x)
               + (u->y - v->y) * (u->y - v->y)
               + (u->z - v->z) * (u->z - v->z) );
}
