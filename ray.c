#include "ray.h"


void at(ray* r, double t, point3* result){
    result->x = r->_origin.x + r->_direction.x * t;
    result->y = r->_origin.y + r->_direction.y * t;
    result->z = r->_origin.z + r->_direction.z * t;
}


ray* set_ray(point3* _origin, vec3* _direction, ray* result){
    result->_origin = *_origin;
    result->_direction = *_direction;
    return result;
}


void set_orig(double x, double y, double z, ray* r){
    r->_origin.x = x;
    r->_origin.y = y;
    r->_origin.z = z;
}


void set_dir(double x, double y, double z, ray* r){
    r->_direction.x = x;
    r->_direction.y = y;
    r->_direction.z = z;
}
