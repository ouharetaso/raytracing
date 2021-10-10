#ifndef _SPHERE_H
#define _SPHERE_H

#include "hittable.h"
#include "vector.h"

class sphere : public hittable{
    point3 center;
    double radius;
public:
    sphere() {}
    sphere(point3 cen, double r) : center(cen), radius(r) {};

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
        vec3 outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal);

        return true;
    }

};


#endif
