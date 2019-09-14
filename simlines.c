#include <stdio.h>
#include <table.h>
#include <string.h>
#include "sentence.h"
#include "atom.h"
#include "readaline.h"

//Function Prototypes
void open_file(FILE **file, char *filename);
void hash_file(FILE *file, void **table, char *filename);
int find_matches(void *);
void display_matches();

int main (int argc, char *argv[]) {

    //If user didn't enter any input files
    if (argc == 1) {
        fprintf(stderr, "Invalid input file(s)");
        return 1;
    }

    //File pointer to store opened file, and initialize sentence table
    FILE *file;
    void *sentenceTable = Table_new(10, NULL, NULL);

    //Open each file and insert all lines into table
    for (int i = 1; i < argc; i++) {
        open_file(&file, argv[i]);
        hash_file(file, &sentenceTable, argv[i]);
    }

    printf("%d\n", find_matches(sentenceTable));

    return 0;
}

void hash_file(FILE *file, void **table, char *filename) {

    int lineCount = 1;
    char *tempSentence;

    while(readaline(file, &tempSentence) != 0) {

        //printf("Line Count: %u\n", lineCount);
        //printf("\nValue of tempSentence: %s", tempSentence);

        struct Sentence *s = Sentence_new(tempSentence, filename, lineCount++);

        char *key = s -> cleanedSentence;
        printf("\nThis is key: %s", key);

        const char *sentenceAtom = Atom_new(key, strlen(key));

        struct Sentence *replaced = Table_put(*table, sentenceAtom, s);

        if (strlen(s -> cleanedSentence) == 10) {
            //struct Sentence *buffer = Table_get(*table, sentenceAtom);
            if (replaced != NULL) {
                printf("This is from get: %s", replaced -> cleanedSentence);
                printf("This is from get: %s\n", replaced -> filename);
                printf("This is from get: %u\n", replaced -> lineNumber);
            }
            /*
            buffer = Table_get(*table, sentenceAtom);
            if (buffer != NULL) {
                printf("This is from get: %s", buffer -> cleanedSentence);
                printf("This is from get: %s\n", buffer -> filename);
                printf("This is from get: %u\n", buffer -> lineNumber);
            }
            */
        }

        free(tempSentence);

    }    

    printf("Table length is: %d\n", Table_length(*table));
/*
    const char *tempAtom = Atom_new("co,m,p,40\n", 10);

    */
}


int find_matches(void *sentenceTable) {
    sentenceTable = sentenceTable;
    return 0;
}

void display_matches() {

}

void open_file(FILE **file, char *filename) {
    *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: file could not be opened");
        exit(4);
    }
}




