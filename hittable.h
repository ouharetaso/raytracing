#ifndef _HITTABLE_H
#define _HITTABLE_H


#include "vector.h"
#include "ray.h"
#include "material.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;


class material;

struct hit_record;


class hittable {
public:
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};


#endif
