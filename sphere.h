#ifndef _SPHERE_H
#define _SPHERE_H

#include <cmath>

#include "hittable.h"
#include "vector.h"

class sphere : public hittable{
    point3 center;
    double radius;
    shared_ptr<material> mat_ptr;
public:
    sphere() {}
    sphere(point3 cen, double r, shared_ptr<material> m) : center(cen), radius(r), mat_ptr(m){};

    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override {
        vec3 oc = r.origin() - center;
        double a = dot(r.direction(), r.direction());
        double b = dot(r.direction(), oc);
        double c = dot(oc, oc) - radius * radius;
        double d = b * b - a * c;

        if(d < 0)return false;
        double sqrtd = sqrt(d);

        double root = (-b - sqrtd) / a;
        if(root < t_min || t_max < root){
            root = (-b + sqrtd) / a;
            if(root < t_min || t_max < root) return false;
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        vec3 outward_normal = normalize(rec.p - center);
        rec.set_face_normal(r, outward_normal);
        rec.mat_ptr = mat_ptr;
        rec.u = std::abs(acos( outward_normal.z() / sqrt(outward_normal.x()*outward_normal.x()+outward_normal.z()*outward_normal.z() ) ) ) / pi;
        rec.v = acos(outward_normal.y()) / pi;

        return true;
    }

};


#endif
