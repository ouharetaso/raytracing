#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits>

#include "vector.h"
#include "color.h"
#include "ray.h"
#include "hittable_list.h"
#include "sphere.h"
#include "triangle.h"
#include "camera.h"
#include "material.h"


extern char *optarg;
extern int optind, opterr, optopt;

const double infinity = std::numeric_limits<double>::infinity();
const double ground_scale = 100;


hittable_list random_scene() {
    hittable_list world;

    for(int a = -20; a < 11; a++){
        for(int b = -20; b < 11; b++){
            double choose_mat = random_double();
            double r = random_double(0.01, 0.2);
            point3 center(a + 0.9 * random_double(), r, b + 0.9 * random_double());

            if ((center - point3(0, 0.5, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;
                if(choose_mat < 0.8){
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    world.add(make_shared<sphere>(center, r, sphere_material));
                }
                else if(choose_mat < 0.95){
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = 0.5 * (1 - random_double() * random_double());
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, r, sphere_material));
                }
                else {
                    sphere_material = make_shared<dielectric>(random_double(1.001, 2));
                    world.add(make_shared<sphere>(center, r, sphere_material));
                }
            }
        }
    }

    point3 vertex[4] = {
        point3(  1 * ground_scale, 0.0,  1 * ground_scale),
        point3(  1 * ground_scale, 0.0, -1 * ground_scale),
        point3( -1 * ground_scale, 0.0,  1 * ground_scale),
        point3( -1 * ground_scale, 0.0, -1 * ground_scale)
    };
    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_left   = make_shared<dielectric>(1.5);
    auto material_right  = make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);

    //world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground ));
    world.add(make_shared<triangle>(vertex[0], vertex[1], vertex[2], material_ground ));
    world.add(make_shared<triangle>(vertex[1], vertex[2], vertex[3], material_ground ));
    world.add(make_shared<sphere>(point3( 0.0,    0.5, 0.0),   0.5, material_center ));
    world.add(make_shared<sphere>(point3(-1.0,    0.5, 0.0),   0.5, material_left ));
    world.add(make_shared<sphere>(point3(-1.0,    0.5, 0.0), -0.45, material_left));
    world.add(make_shared<sphere>(point3( 1.0,    0.5, 0.0),   0.5, material_right ));

    return world;
}

color ray_color(const ray& r, const hittable& world, int depth){
    hit_record rec;

    if(depth <= 0) return color(0, 0, 0);

    if(world.hit(r, 0.0001, infinity, rec)) {
        ray scattered;
        color attenuation;
        if(rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth - 1);
        return color(0, 0, 0);
    }

    vec3 unit_dir = normalize(r.direction());
    double t = 0.5 * (unit_dir.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}


int main(int argc, char** argv){
    // Image
    double aspect_ratio;
    int width  = 1280;
    int height = 720;
    int max_depth = 20;
    int subpixel_v = 4;
    int subpixel_h = 4;

    int opt;
    while( (opt = getopt(argc, argv, "w:h:x:y:d:")) != -1 ){
        switch(opt){
            case 'w':
                width = atoi(optarg);
                break;
            case 'h':
                height = atoi(optarg);
                break;
            case 'x':
                subpixel_h = atoi(optarg);
                break;
            case 'y':
                subpixel_v = atoi(optarg);
                break;
            case 'd':
                max_depth = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Usage: %s [-w] [-h] [-x] [-y] [-d]\n", argv[0]);
                break;
        }
    }

    aspect_ratio = double(width) / double(height);

    // World
    hittable_list world = random_scene();

    // Camera
    point3 lookfrom(13, 2, 3);
    point3 lookat(0, 0, 0);
    vec3 vup(0, 1, 0);
    double dist_to_focus = 10.0;
    double aperture = 0.1;

    camera cam(lookfrom, lookat, vup, 10, aspect_ratio, aperture, dist_to_focus);


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
