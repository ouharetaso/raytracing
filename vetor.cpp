#include "vector.h"



double dot(vec3& u, vec3& v){
    return u[0] * v[0] +
           u[1] * v[1] +
           u[2] * v[2];
}


vec3 cross(vec3& u, vec3& v){
    return vec3(u[1] * v[2] - u[2] * v[1],
                u[2] * v[0] - u[0] * v[2],
                u[0] * v[1] - u[1] * v[0]);
}

double length(vec3& v){
    return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}


vec3 normalize(vec3 v){
    return v / length(v);
}
