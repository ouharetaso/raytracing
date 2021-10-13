#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <limits>
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <vector>
#include <mutex>
#include <algorithm>

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
const double ground_scale = 2;


void load_texture(std::vector<std::vector<color>>& tex, char* filename){
    std::ifstream file(filename);
    std::string line;
    int width, height, r, g, b;

    std::getline(file, line);
    file >> width >> height;
    std::getline(file, line);
    std::getline(file, line);
    for(int j = 0; j < height; j++){
        tex.push_back(std::vector<color>(width));
        for(int i = 0; i < width; i++){
            file >> r >> g >> b;
            tex[j][width - i - 1] = color(double(r) / 255.0 , double(g) / 255.0 , double(b) / 255.0);
        }
    }
}


hittable_list random_scene() {
    hittable_list world;

    /*for(int a = -11; a < 11; a++){
        if(a%2 ==0 ) continue;
        for(int b = -11; b < 11; b++){
            if(b%2 ==0 ) continue;
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
    }*/

    /*std::vector<std::vector<color>> tex(100, std::vector<color>(100));
    for(size_t i = 0; i < tex.size(); i++){
        for(size_t j = 0; j < tex.at(0).size(); j++){
            tex[i][j] = color(random_double(), random_double(), random_double());
        }
    }*/
    std::vector<std::vector<color>> tkg1, tkg2, earth;
    load_texture(tkg1, "earth.ppm");
    load_texture(earth, "earth.ppm");

    for(int j = 0; j < tkg1.at(0).size(); j++){
        tkg2.push_back(std::vector<color>(tkg1.size()));
        for(int i = 0; i < tkg1.size(); i++){
            tkg2[j][i] = tkg1[tkg1.size() - i - 1][tkg1.at(0).size() - j - 1];
        }
    }

    double ground_aspect_ratio = double(tkg1.at(0).size()) / tkg1.size();

    point3 vertex[4] = {
        point3(  1 * ground_scale, 0.0,  1 * ground_scale * ground_aspect_ratio),
        point3(  1 * ground_scale, 0.0, -1 * ground_scale * ground_aspect_ratio),
        point3( -1 * ground_scale, 0.0,  1 * ground_scale * ground_aspect_ratio),
        point3( -1 * ground_scale, 0.0, -1 * ground_scale * ground_aspect_ratio)
    };

    //auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_ground1 = make_shared<texture>(tkg1);
    auto material_ground2 = make_shared<texture>(tkg2);
    //auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_center = make_shared<texture>(earth);
    auto material_left   = make_shared<dielectric>(1.5);
    auto material_right  = make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);

    //world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground ));
    world.add(make_shared<triangle>(vertex[0], vertex[1], vertex[2], material_ground1 ));
    world.add(make_shared<triangle>(vertex[3], vertex[1], vertex[2], material_ground2 ));
    world.add(make_shared<sphere>(point3( 0.0,    1, 0.0),   1, material_center ));
    //world.add(make_shared<sphere>(point3(-1.0,    0.5, 0.0),   0.5, material_left ));
    //world.add(make_shared<sphere>(point3(-1.0,    0.5, 0.0), -0.45, material_left));
    //world.add(make_shared<sphere>(point3( 1.0,    0.5, 0.0),   0.5, material_right ));

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
    //return (1.0 - t) * color(0.01, 0.01, 0.01) + t * color(0.05, 0.07, 0.1);
}


void get_ray_color(color& pix_color, const ray& r, const hittable& world, int depth){
    pix_color = ray_color(r, world, depth);
}


int main(int argc, char** argv){
    // Image
    double aspect_ratio;
    int width  = 400;
    int height = 255;
    int max_depth = 20;
    int subpixel_v = 7;
    int subpixel_h = 7;
    bool is_multithread = false;

    int opt;
    while( (opt = getopt(argc, argv, "w:h:x:y:d:m")) != -1 ){
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
            case 'm':
                is_multithread = true;
            default:
                fprintf(stderr, "Usage: %s [-w] [-h] [-x] [-y] [-d]\n", argv[0]);
                break;
        }
    }

    aspect_ratio = double(width) / double(height);

    // World
    hittable_list world = random_scene();

    // Camera
    //point3 lookfrom(13, 2, 3);
    point3 lookfrom(-5, 3, 0);
    point3 lookat(0, 0.5, 0);
    vec3 vup(0, 1, 0);
    double dist_to_focus = 10.0;
    double aperture = 0.1;

    camera cam(lookfrom, lookat, vup, 50, aspect_ratio, aperture, dist_to_focus);

    // File
    char file_name[256];
    std::ofstream out_file;

    sprintf(file_name, "image_%dx%d_%dx%d_%d.ppm", width, height, subpixel_h, subpixel_v, max_depth);
    out_file.open(file_name, std::ios::trunc);

    out_file << "P3\n" << width << ' ' << height << "\n255\n";
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
            write_color((pix_color / double(subpixel_h * subpixel_v)), out_file);
        }
    }
    fprintf(stderr, "\nDone. \n");

    return 0;
}
