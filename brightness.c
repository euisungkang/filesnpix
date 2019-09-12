/*
Easton, Andrew
Professor Monroe
Comp-40
09/10/2019

PROJECT: brightness.c
PURPOSE: Part A of assignment. This short program reads in an image and 
         outputs the average brightness of every pixel in the image
NOTE:    

Last Modified: 09/09/2019
*/

#include <stdio.h>
#include <pnmrdr.h>

//Function Prototypes
void open_file(FILE **img, char *filename);
double average_brightness(void *);

int main (int argc, char *argv[])
{
    printf("%u\n", argc);
    //Error message, too many arguments
    if (argc > 2) {
        fprintf(stderr, "%s\n", "Invalid argument(s) for file");
        return 0;
    }

    void *grayscale;
    //No arguments, read from stdin
    if (argc == 1) { 
        grayscale = Pnmrdr_new(stdin);
        printf("%f\n", average_brightness(grayscale));
    } else if (argc == 2) {
        FILE *img;
        open_file(&img, argv[1]);
        grayscale = Pnmrdr_new(img);
        if (img)
            printf("%s\n", "file has been opened");
        else 
            printf("%s\n", "file has not been opened");
        printf("%f\n", average_brightness(grayscale)); 
        fclose(img);
    }
}

void open_file(FILE **img, char *filename) {
    *img = fopen(filename, "r");
}

double average_brightness(void *img) {
    Pnmrdr_mapdata data = Pnmrdr_data(img);
    double pixelResult = 0;
    printf("%u\n%u\n", data.height, data.width);
    for (unsigned int i = 0; i < data.height; i++) {
        for (unsigned int j = 0; j < data.width; j++) {
            pixelResult += ((double)Pnmrdr_get(img) / 255);
            printf("%f\n", pixelResult);
        }
    }
    //printf("%u\n", data.height * data.width);
    return pixelResult / (data.height * data.width);
}



