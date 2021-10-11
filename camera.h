#ifndef _CAMERA_H
#define _CAMERA_H

#include "vector.h"

vec3 random_in_unit_disk() {
    double r = random_double(0.0000001, 1);
    double theta = random_double(0, 2 * pi);
    vec3 p = vec3(r * cos(theta), r * sin(theta), 0);

    return p;
}

class camera{
public:
    camera(point3 lookfrom,
           point3 lookat,
           vec3   vup,
           double vfov,
           double aspect_ratio,
           double aperture,
           double focus_dist
       ){
        double theta = deg2rad(vfov);
        double h = tan(theta / 2);
        double viewport_height = 2.0 * h;
        double viewport_width = aspect_ratio * viewport_height;

        vec3 w = normalize(lookfrom - lookat);
        vec3 u = normalize(cross(vup, w));
        vec3 v = cross(w, u);

        origin = lookfrom;
        horizontal = focus_dist * viewport_width * u;
        vertical = focus_dist * viewport_height * v;
        lower_left = origin - horizontal / 2 - vertical / 2 - focus_dist * w;

        lens_radius = aperture / 2;
    }

    ray get_ray(double s, double t) const {
        vec3 rd = lens_radius * random_in_unit_disk();
        vec3 offset = u * rd.x() + v * rd.y();

        return ray(origin + offset,
                   lower_left + s * horizontal + t * vertical - origin - offset);
    }

private:
    point3 origin;
    point3 lower_left;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w;
    double lens_radius;
};


#endif
