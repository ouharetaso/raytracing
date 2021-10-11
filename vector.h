#ifndef _VECTOR_H
#define _VECTOR_H

#include <cmath>
#include <random>

const double pi = 3.1415926535897932385;

double deg2rad(double deg);

inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min)*random_double();
}


class vec3{
    double e[3];
public:
    vec3() : e{0, 0, 0} {}
    vec3(double x, double y, double z) : e{x, y, z} {}

    inline static vec3 random() {
        return vec3(random_double(), random_double(), random_double());
    }

    inline static vec3 random(double min, double max) {
        return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
    }

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    double operator[] (int i) const { return e[i]; }
    double& operator[] (int i) { return e[i]; }

    double length();

    bool near_zero() const;

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
        e[1] = v.y();
        e[2] = v.z();

        return *this;
    }
};


using point3 = vec3;
using color  = vec3;

double dot(const vec3& u, const vec3& v);
vec3 cross(const vec3& u, const vec3& v);

vec3 normalize(vec3 v);

vec3 random_in_unit_sphere();
vec3 random_unit_vector();

vec3 reflect(const vec3& v, const vec3& n);

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


inline vec3 operator* (const vec3& u, const vec3& v) {
    return vec3(u[0] * v[0], u[1] * v[1], u[2] * v[2]);
}


inline vec3 operator/ (const vec3& v, const double& t) {
    return vec3(v[0] / t, v[1] / t, v[2] / t);
}

#endif
