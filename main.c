#include <stdio.h>
#include <stdlib.h>

#include "vector.h"
#include "color.h"
#include "ray.h"


// DON'T USE same function more than 2 times at the same time
#define ADD(u, v) (add_v((u), (v), &_res_a))
#define SUB(u, v) (sub_v((u), (v), &_res_s))
#define MUL(u, v) (mul_v((u), (v), &_res_m))
#define DIV(u, v) (div_v((u), (v), &_res_d))
#define VEC3(x, y, z) (set_v((x), (y), (z), &_res_v))

vec3 _res_a, _res_s, _res_m, _res_d, _res_v;

void ray_color(ray* r, color* pix_color){
    vec3 unit_dir;
    color a, b;

    normalize(&(r->_direction), &unit_dir);
    double t = 0.5 * ( unit_dir.y + 1.0 );

    set_v(1.0, 1.0, 1.0, &a); set_v(0.5, 0.7, 1.0, &b);
    mul_v(&a, (1-t), &a);
    mul_v(&b, t, &b);
    add_v(&a, &b, pix_color);
}


int main(void){
    // Image
    const int width  = 400;
    const int height = width * 9 / 16;
    const double aspect_ratio = (double)width / height;

    // Camera
    double viewport_height = 2.0;
    double viewport_width  = viewport_height * aspect_ratio;
    double focal_length = 1.0;

    vec3 origin = {0, 0, 0};
    vec3 horizontal = {viewport_width, 0, 0};
    vec3 vertical   = {0, viewport_height, 0};
    vec3 lower_left = origin;
    sub_v(&lower_left, DIV(&horizontal, 2), &lower_left);
    sub_v(&lower_left, DIV(&vertical, 2), &lower_left);
    sub_v(&lower_left, VEC3(0, 0, focal_length), &lower_left);

    printf("P3\n%d %d\n255\n", width, height);
    for(int j = height-1; j >= 0; j--){
        fprintf(stderr, "\r                                       ");
        fprintf(stderr, "\rScanline remaining : %d / %d", j, height-1);
        for(int i = 0; i < width; i++){
            double u = (double)i / (width - 1);
            double v = (double)j / (height - 1);
            ray r;
            vec3 dir;
            color pix_color;

            add_v(&lower_left, MUL(&horizontal, u), &dir);
            add_v(&dir, MUL(&vertical, v), &dir);
            sub_v(&dir, &origin, &dir);
            set_ray(&origin, &dir, &r);
            ray_color(&r, &pix_color);
            write_color(&pix_color);
        }
    }
    fprintf(stderr, "\nDone. \n");

    return 0;
}
