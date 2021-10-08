#include <stdio.h>
#include <stdlib.h>


int main(void){
    const int width  = 256;
    const int height = 256;

    printf("P3\n%d %d\n255\n", width, height);
    for(int j = height-1; j >= 0; j--){
        fprintf(stderr, "\r                                       ");
        fprintf(stderr, "\rScanline remaining : %d / %d", j, height-1);
        for(int i = 0; i < width; i++){
            double ir = (double)i / (width - 1);
            double ig = (double)j / (height - 1);
            double ib = 0.25;

            printf("%d %d %d\n", (int)(ir * 255.999), (int)(ig * 255.999), (int)(ib * 255.999));
        }
    }
    fprintf(stderr, "\nDone. \n");

    return 0;
}
