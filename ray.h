#ifndef _RAY_H
#define _RAY_H

#include "vector.h"

typedef struct{
    point3 _origin;
    vec3 _direction;
}ray;

void at(ray* r, double t, point3* result);
ray* set_ray(point3* _origin, vec3* _direction, ray* result);
void set_orig(double x, double y, double z, ray* r);
void set_dir(double x, double y, double z, ray* r);

#endif
