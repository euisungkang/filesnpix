#include <stdio.h>
#include <table.h>
#include "sentence.h"

void open_file(FILE **file, char *filename);
void hash_file(FILE *file, void *table);

int main (int argc, char *argv[]) {
    if (argc == 1) {
        fprintf(stderr, "Invalid input file(s)");
        return 1;
    }

    FILE *file;
    void *sentenceTable = Table_new(10, NULL, NULL);

    for (int i = 1; i < argc; i++) {
        open_file(&file, argv[i]);
        hash_file(file, sentenceTable);
    }

    return 0;
}

void open_file(FILE **file, char *filename) {
    *file = fopen(filename, "r");
}

void hash_file(FILE *file, void *table) {
    file = file;
    table = table;
}