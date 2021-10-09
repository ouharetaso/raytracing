#ifndef _RAY_H
#define _RAY_H

#include "vector.h"


class ray{
    point3 orig;
    vec3 dir;
public:
    ray() : orig(0, 0, 0), dir(0, 0, 0) {}
    ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}

    point3 origin() { return orig; }
    vec3 direction() { return dir; }

    point3 at(double& t) { return orig + dir * t; }
};


#endif
