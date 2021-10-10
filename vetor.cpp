#include "vector.h"


inline vec3 random_in_unit_sphere() {
    while(true){
        vec3 p = vec3::random(-1, 1);
        if(p.length() >= 1) continue;
        return p;
    }
}


vec3 random_unit_vector(){
    return normalize(random_in_unit_sphere());
}


double dot(const vec3& u, const vec3& v){
    return u[0] * v[0] +
           u[1] * v[1] +
           u[2] * v[2];
}


vec3 cross(vec3& u, vec3& v){
    return vec3(u[1] * v[2] - u[2] * v[1],
                u[2] * v[0] - u[0] * v[2],
                u[0] * v[1] - u[1] * v[0]);
}

double vec3::length(){
    return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
}


vec3 normalize(vec3 v){
    return v / v.length();
}
