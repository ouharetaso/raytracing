#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "color.h"


int main(void){
    const int width  = 256;
    const int height = 256;

    printf("P3\n%d %d\n255\n", width, height);
    for(int j = height-1; j >= 0; j--){
        fprintf(stderr, "\r                                       ");
        fprintf(stderr, "\rScanline remaining : %d / %d", j, height-1);
        for(int i = 0; i < width; i++){
            color pix_color;

            set_v((double)i / (width - 1), (double)j / (height - 1), 0.25, &pix_color);
            write_color(&pix_color);
        }
    }
    fprintf(stderr, "\nDone. \n");

    return 0;
}
