#include <stdio.h>
#include <stdlib.h>

#include "vector.h"
#include "color.h"
#include "ray.h"


bool hit_sphere(const point3& c, double radius, const ray& r){
    vec3 oc = r.origin() - c;
    double a = dot(r.direction(), r.direction());
    double b = dot(r.direction(), oc);
    double c = dot(oc, oc) - radius * radius;
    return (b * b - a * c > 0);
}


color ray_color(ray& r){
    if(hit_sphere(point3(0, 0, -1), 0.5, r)) return color(1, 0, 0);

    vec3 unit_dir = normalize(r.direction());
    double t = 0.5 * ( unit_dir.y() + 1.0 );
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
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
    vec3 lower_left = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

    printf("P3\n%d %d\n255\n", width, height);
    for(int j = height-1; j >= 0; j--){
        fprintf(stderr, "\r                                       ");
        fprintf(stderr, "\rScanline remaining : %d / %d", j, height-1);
        for(int i = 0; i < width; i++){
            double u = (double)i / (width - 1);
            double v = (double)j / (height - 1);
            ray r(origin, lower_left + u * horizontal + v * vertical - origin);
            color pix_color = ray_color(r);
            write_color(pix_color);
        }
    }
    fprintf(stderr, "\nDone. \n");

    return 0;
}
