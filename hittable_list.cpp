#include "hittable_list.h"


bool hittable_list::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    hit_record tmp_rec;
    bool hit_anything = false;
    double closest_so_far = t_max;

    for ( const auto& object : objects ){
        if(object->hit(r, t_min, closest_so_far, tmp_rec)){
            hit_anything = true;
            closest_so_far = tmp_rec.t;
            rec = tmp_rec;
        }
    }

    return hit_anything;
}
