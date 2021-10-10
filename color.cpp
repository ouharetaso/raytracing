#include "color.h"

#include <cstdio>


void write_color(const color& pixel_color){
    std::printf("%d %d %d\n", int(sqrt(pixel_color.x()) * 255.999),
                              int(sqrt(pixel_color.y()) * 255.999),
                              int(sqrt(pixel_color.z()) * 255.999) );
}
