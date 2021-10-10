#include <stdio.h>
#include <stdlib.h>

#include <limits>

#include "vector.h"
#include "color.h"
#include "ray.h"
#include "hittable_list.h"
#include "sphere.h"


const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

color ray_color(ray& r, const hittable& world){
    hit_record rec;
    if(world.hit(r, 0, infinity, rec)) {
        return 0.5 * (rec.normal + color(1, 1, 1));
    }

    vec3 unit_dir = normalize(r.direction());
    double t = 0.5 * (unit_dir.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}


int main(void){
    // Image
    const int width  = 320;
    const int height = width * 9 / 16;
    const double aspect_ratio = (double)width / height;

    // World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5) );
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100) );


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
            color pix_color = ray_color(r, world);
            write_color(pix_color);
        }
    }
    fprintf(stderr, "\nDone. \n");

    return 0;
}
