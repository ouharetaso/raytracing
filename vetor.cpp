#include "vector.h"


vec3 reflect(const vec3& v, const vec3& n){
    return v - 2 * dot(v, n) * n;
}


double deg2rad(double deg){
    return deg * pi / 180.0;
}

vec3 random_in_unit_sphere() {
    double r = random_double(0.0000001, 1);
    double theta = random_double(0, pi);
    double phi = random_double(0, 2 * pi);
    vec3 p = vec3(r * cos(theta) * cos(phi), r * cos(theta) * sin(phi), r * sin(theta));

    return p;
}


bool vec3::near_zero() const {
    const double s = 1e-8;
    return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
}


vec3 random_unit_vector(){
    return normalize(random_in_unit_sphere());
}


double dot(const vec3& u, const vec3& v){
    return u[0] * v[0] +
           u[1] * v[1] +
           u[2] * v[2];
}


vec3 cross(const vec3& u, const vec3& v){
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
