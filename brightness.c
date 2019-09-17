/*
Easton, Andrew
Professor Monroe
Comp-40
09/10/2019

PROJECT: brightness.c
PURPOSE: Part A of assignment. This short program reads in an image and 
         outputs the average brightness of every pixel in the image
NOTE:    

Last Modified: 09/10/2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <pnmrdr.h>
#include <setjmp.h>
#include "except.h"

//Function Prototypes
void open_file(FILE **img, char *filename);
double average_brightness(void *);

int main (int argc, char *argv[])
{
    //Error message, too many arguments
    if (argc > 2) {
        fprintf(stderr, "Invalid input files: ./brightness [image file]\n");
        exit(EXIT_FAILURE);
    }

    void *grayscale;        //void * to store pnmrdr

    //If image file is not given, read from stdin instead
    if (argc == 1) { 

        //Initialize pnmrdr with stdin stream, display brightness
        grayscale = Pnmrdr_new(stdin);
        printf("%.3f\n", average_brightness(grayscale));

    } else if (argc == 2) {

        FILE *img;
        open_file(&img, argv[1]);       //Open file

        //Initialize pnmrdr with file stream, display brightness
        grayscale = Pnmrdr_new(img);

        printf("%.3f\n", average_brightness(grayscale));

        fclose(img);        //Close to avoid mem leak
    }

    exit(EXIT_SUCCESS);
}

/*
PURPOSE: Will open given file and return a pointer to it. Will display error
         message and exit program if file can't be opened       */
void open_file(FILE **img, char *filename)
{
    *img = fopen(filename, "r");
    if (!(*img)) {
        fprintf(stderr, "Error: file could not be opened\n");
        exit(EXIT_FAILURE);
    }
}

/*
PURPOSE: Returns the average brightness of a given pgm file. Iterates
         every pixel's brightness    */
double average_brightness(void *img)
{
    Pnmrdr_mapdata data = Pnmrdr_data(img);

    //Error if file type is not grayscale .pgm
    if (data.type != Pnmrdr_gray) {
        fprintf(stderr, "Error: File is not grayscale .pgm format\n");
        exit(EXIT_FAILURE);
    }

    //Error if image has no readable pixels
    if (data.height * data.width <= 0) {
        fprintf(stderr, "Error: Image is empty, 0 readable pixels\n");
        exit(EXIT_FAILURE);
    }

    double pixelResult = 0;

    //Iterate through each pixel and add brightness (0 ~ 1)
    for (unsigned int i = 0; i < data.height; i++) 
        for (unsigned int j = 0; j < data.width; j++) 
            pixelResult += ((double)Pnmrdr_get(img) / 255);
    
    return pixelResult / (data.height * data.width);
}