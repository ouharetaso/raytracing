#include <stdio.h>
#include <stdlib.h>

#include <limits>

#include "vector.h"
#include "color.h"
#include "ray.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"


const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

color ray_color(const ray& r, const hittable& world, int depth){
    hit_record rec;

    if(depth <= 0) return color(0, 0, 0);

    if(world.hit(r, 0.00000001, infinity, rec)) {
        point3 target = rec.p + rec.normal + random_unit_vector();
        return 0.5 * ray_color(ray(rec.p, target - rec.p), world, depth - 1);
    }

    vec3 unit_dir = normalize(r.direction());
    double t = 0.5 * (unit_dir.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}


int main(void){
    // Image
    const int width  = 400;
    const int height = width * 9 / 16;
    const int max_depth = 50;
    const int subpixel_v = 10;
    const int subpixel_h = 10;

    // World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5) );
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100) );

    // Camera
    camera cam;

    printf("P3\n%d %d\n255\n", width, height);
    for(int j = height-1; j >= 0; j--){
        fprintf(stderr, "\r                                       ");
        fprintf(stderr, "\rScanline remaining : %d / %d", j, height-1);
        for(int i = 0; i < width; i++){
            color pix_color;
            for(int k = 0; k < subpixel_h; k++){
                for(int l = 0; l < subpixel_v; l++){
                    double u = (i + double(2 * k - subpixel_h) / subpixel_h) / (width - 1);
                    double v = (j + double(2 * l - subpixel_v) / subpixel_v) / (height - 1);
                    ray r = cam.get_ray(u, v);
                    pix_color += ray_color(r, world, max_depth);
                }
            }
            write_color((pix_color / double(subpixel_h * subpixel_v)));
        }
    }
    fprintf(stderr, "\nDone. \n");

    return 0;
}
