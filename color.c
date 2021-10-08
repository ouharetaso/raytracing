#include "color.h"

#include <stdio.h>


void write_color(color* pixel_color){
    printf("%d %d %d\n", (int)(pixel_color->x * 255.999),
                         (int)(pixel_color->y * 255.999),
                         (int)(pixel_color->z * 255.999) );
}
