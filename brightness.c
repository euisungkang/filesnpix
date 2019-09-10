#include <stdio.h>
#include <pnmrdr.h>

void open_file(FILE **img, char *filename);

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

    Pnmrdr_new (FILE *fp)

    fclose(img);
}

void open_file(FILE **img, char *filename) {
    *img = fopen(filename, "r");
}