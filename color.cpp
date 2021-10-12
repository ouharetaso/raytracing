#include "color.h"

#include <cstdio>
#include <fstream>


void write_color(const color& pixel_color, std::ofstream& out){
    out << int(sqrt(pixel_color.x()) * 255.999) << ' '
        << int(sqrt(pixel_color.y()) * 255.999) << ' '
        << int(sqrt(pixel_color.z()) * 255.999) << '\n';

}
