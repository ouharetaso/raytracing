#ifndef _TRIANGLE_H
#define _TRIANGLE_H


#include "vector.h"
#include "hittable.h"
#include "material.h"


class triangle : public hittable{
    vec3 v0 ,v1, v2;
    vec3 e1, e2;
    vec3 normal;
    shared_ptr<material> mat_ptr;

public:
    triangle() {}
    triangle(vec3 a, vec3 b, vec3 c, shared_ptr<material> m) : v0(a), v1(b), v2(c), mat_ptr(m) {
        e1 = b - a;
        e2 = c - a;
        normal = normalize(cross(e1, e2));
    };

    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override {
        double t, u, v;
        vec3 e0;
        e0 = r.origin() - v0;
        vec3 a = cross(r.direction(), e2);
        vec3 b = cross(e0, e1);

        t = dot(b, e2) / dot(a, e1);
        u = dot(a, e0) / dot(a, e1);
        v = dot(b, r.direction()) / dot(a, e1);

        if( !(t >= 0) || !(u >= 0) || !(v >= 0) || !(u + v <=1) ) return false;
        if( t < t_min || t_max < t) return false;

        rec.t = t;
        rec.p = r.at(t);
        rec.set_face_normal(r, normal);
        rec.mat_ptr = mat_ptr;

        return true;
    }
};


#endif
