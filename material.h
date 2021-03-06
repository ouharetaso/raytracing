#ifndef _MATRIAL_H
#define _MATRIAL_H

#include "hittable.h"
#include "ray.h"
#include "vector.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat);


class material;

struct hit_record{
    point3 p;
    vec3 normal;
    shared_ptr<material> mat_ptr;
    double t;
    bool front_face;
    double u;
    double v;

    inline void set_face_normal(const ray& r, const vec3& outward_normal){
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -1*outward_normal;
    }
};


class material {
public:
    virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const = 0;
};


class texture : public material{
    std::vector<std::vector<color>> tex;
    int u_max;
    int v_max;
public:
    texture(std::vector<std::vector<color>> t) : tex(t) {
        u_max = t.at(0).size() - 1;
        v_max = t.size() - 1;
    };

    virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override{
        vec3 reflected = reflect(normalize(r_in.direction()), rec.normal);
        scattered = ray(rec.p, reflected + random_in_unit_sphere());
        attenuation = tex.at(int(v_max * rec.v)).at(u_max * rec.u);
        return true;
    };
};


class dielectric : public material {
    double ir;
public:
    dielectric(double index_of_refraction) : ir(index_of_refraction) {}

    virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override{
        attenuation = color(1.0, 1.0, 1.0);
        double refraction_ratio = rec.front_face ? (1.0 / ir) : ir;

        vec3 unit_dir = normalize(r_in.direction());
        double cos_theta = fmin(dot(-unit_dir, rec.normal), 1.0);
        double sin_theta = sqrt(1.0 - cos_theta*cos_theta);

        bool cannot_refract = refraction_ratio * sin_theta > 1.0;
        vec3 dir;

        if(cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double()) dir = reflect(unit_dir, rec.normal);
        else dir = refract(unit_dir, rec.normal, refraction_ratio);

        scattered = ray(rec.p, dir);
        return true;
    }

private:
    static double reflectance(double cosine, double ref_idx) {
        double r0 = (1 - ref_idx) / (1 + ref_idx);
        r0 = r0 * r0;
        return r0 + (1 - r0) * pow((1 - cosine), 5);
    }

};


class lambertian : public material {
    color albedo;
public:
    lambertian(const color& a) : albedo(a) {}
    virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override{
        vec3 scatter_direction = rec.normal + random_unit_vector();

        if(scatter_direction.near_zero()) scatter_direction = rec.normal;

        scattered = ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }
};


class metal : public material {
    color albedo;
    double fuzz;
public:
    metal(const color& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

    virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
        vec3 reflected = reflect(normalize(r_in.direction()), rec.normal);
        scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere());
        attenuation = albedo;
        return ( dot(scattered.direction(), rec.normal) > 0 );
    }
};


#endif
