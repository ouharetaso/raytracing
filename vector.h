#ifndef _VECTOR_H
#define _VECTOR_H

#include <cmath>

class vec3{
    double e[3];
public:
    vec3() : e{0, 0, 0} {}
    vec3(double x, double y, double z) : e{x, y, z} {}

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    double operator[] (int i) const { return e[i]; }
    double& operator[] (int i) { return e[i]; }

    /*vec3 operator+ (const vec3& u, const vec3& v);
    vec3 operator- (const vec3& u, const vec3& v);
    friend vec3 operator* (const vec3& v, const double& t);
    friend vec3 operator* (const double& t, const vec3& v);
    friend vec3 operator/ (const vec3& v, const double& t);*/

    vec3 operator+= (const vec3& v){
        e[0] += v.x();
        e[1] += v.y();
        e[2] += v.z();

        return *this;
    }
    vec3 operator-= (const vec3& v){
        e[0] -= v.x();
        e[1] -= v.y();
        e[2] -= v.z();

        return *this;
    }
    vec3 operator*= (const double& t){
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;

        return *this;
    }
    vec3 operator/= (const double& t){
        e[0] /= t;
        e[1] /= t;
        e[2] /= t;

        return *this;
    }
    vec3 operator= (const vec3& v){
        e[0] = v.x();
        e[1] = v.x();
        e[1] = v.x();

        return *this;
    }
};


using point3 = vec3;
using color  = vec3;

double dot(vec3& u, vec3& v);
vec3 cross(vec3& u, vec3& v);

double length(vec3& v);
vec3 normalize(vec3 v);

inline vec3 operator+ (const vec3& u, const vec3& v){
    return vec3(u[0] + v[0], u[1] + v[1], u[2] + v[2] );
}


inline vec3 operator- (const vec3& u, const vec3& v){
    return vec3(u[0] - v[0], u[1] - v[1], u[2] - v[2] );
}


inline vec3 operator* (const vec3& v, const double& t) {
    return vec3(v[0] * t, v[1] * t, v[2] * t);
}


inline vec3 operator* (const double& t, const vec3& v) {
    return vec3(v[0] * t, v[1] * t, v[2] * t);
}


inline vec3 operator/ (const vec3& v, const double& t) {
    return vec3(v[0] / t, v[1] / t, v[2] / t);
}

#endif
