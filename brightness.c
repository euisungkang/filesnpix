#include <stdio.h>
#include <pnmrdr.h>

void open_file(FILE **img, char *filename);

/*
#define T Pnmrdr_T
typedef struct T *T;
*/
int main (int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "%s\n", "Invalid argument(s) for file");
        return 0;
    }

    FILE *img;

    printf("%s\n", argv[1]);
    
    open_file(&img, argv[1]);

    if (img) {
        printf("%s\n", "file has been opened");
    }
    else {
        printf("%s\n", "file has not been opened");
    }

    Pnmrdr_new(img);

    fclose(img);
}

void open_file(FILE **img, char *filename) {
    *img = fopen(filename, "r");
}