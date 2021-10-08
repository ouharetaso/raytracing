#include "vector.h"


// set value
vec3* set_v(double x, double y, double z, vec3* v){
    v->x = x;
    v->y = y;
    v->z = z;

    return v;
}



vec3* add_v(vec3* u, vec3* v, vec3* result){
    result->x = u->x + v->x;
    result->y = u->y + v->y;
    result->z = u->z + v->z;

    return result;
}


vec3* sub_v(vec3* u, vec3* v, vec3* result){
    result->x = u->x - v->x;
    result->y = u->y - v->y;
    result->z = u->z - v->z;
    return result;
}


vec3* mul_v(vec3* v, double t, vec3* result){
    result->x = v->x * t;
    result->y = v->y * t;
    result->z = v->z * t;
    return result;
}


vec3* div_v(vec3* v, double t, vec3* result){
    result->x = v->x / t;
    result->y = v->y / t;
    result->z = v->z / t;
    return result;
}




double dot(vec3* u, vec3* v){
    return u->x + v->x
         + u->y + v->y
         + u->z + v->z;
}


vec3* cross(vec3* u, vec3* v, vec3* result){
    result->x = u->y * v->z - u->z * v->y;
    result->y = u->z * v->x - u->x * v->z;
    result->z = u->x * v->y - u->y * v->x;
    return result;
}


double length(vec3* u, vec3* v){
    return sqrt( (u->x - v->x) * (u->x - v->x)
               + (u->y - v->y) * (u->y - v->y)
               + (u->z - v->z) * (u->z - v->z) );
}


vec3* normalize(vec3* v, vec3* result){
    vec3 origin = {0, 0, 0};
    double len = length(&origin, v);
    result->x = v->x / len;
    result->y = v->y / len;
    result->z = v->z / len;
    return result;
}
