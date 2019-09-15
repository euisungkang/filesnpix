#include <stdio.h>
#include <table.h>
#include <string.h>
#include <stdlib.h>
#include <list.h>
#include "sentence.h"
#include "atom.h"
#include "readaline.h"

//Function Prototypes
void open_file(FILE **, char *);
void hash_file(FILE *, Table_T *, char *);
//int find_matches(Table_T);
//void display_matches(const void *key, void **value, void *cl);
//void print_sentence(void **, void*);
void free_table(Table_T *);
static void free_list(const void *key, void **value, void *cl);

int main (int argc, char *argv[]) {

    //If user didn't enter any input files
    if (argc == 1) {
        fprintf(stderr, "Invalid input file(s)");
        return 1;
    }

    //File pointer to store opened file, and initialize sentence table
    FILE *file;
    Table_T sentenceTable = Table_new(10, NULL, NULL);

    //Open each file and insert all lines into table
    for (int i = 1; i < argc; i++) {
        open_file(&file, argv[i]);
        hash_file(file, &sentenceTable, argv[i]);
    }

    //find_matches(sentenceTable);
/*
    free_table(&sentenceTable);
    sentenceTable = NULL;
*/
    //printf("%d\n", find_matches(sentenceTable));

    return 0;
}

void hash_file(FILE *file, Table_T *table, char *filename) {

    int lineCount = 1;
    char *tempSentence = "$";

    while(readaline(file, &tempSentence) != 0) {

        //printf("Line Count: %u\n", lineCount);
        printf("\nValue of tempSentence: %s", tempSentence);

        struct Sentence *s = Sentence_new(tempSentence, filename, lineCount++);

        char *key = s -> cleanedSentence;
        printf("\nThis is key: %s", key);

        const char *sentenceAtom = Atom_new(key, strlen(key));

        void *doesBucketExist = Table_get(*table, sentenceAtom);

        if (doesBucketExist == NULL) {
            List_T *sentenceList = (List_T *) malloc(sizeof(List_T));
            *sentenceList = List_push(NULL, s);
            Table_put(*table, sentenceAtom, sentenceList);
            printf("%d\n", List_length(*sentenceList));
        }
        else {
            List_T *returnedList = doesBucketExist;
            *returnedList = List_push(*returnedList, s);
            Table_put(*table, sentenceAtom, returnedList);
            printf("%d\n", List_length(*returnedList));
        }
    }
    //sfree(tempSentence);
    printf("\nTable length is: %d\n", Table_length(*table));
}
/*
int find_matches(Table_T sentenceTable) {
    Table_map(sentenceTable, display_matches, NULL);
    return 0;
}

void display_matches(const void *key, void **value, void *cl) {
    if (List_length(*value) > 1) {
        const char *sharedKey = key;
        printf("%s\n", sharedKey);
        List_map(*value, print_sentence, NULL);
    }
    cl = cl;
}

void print_sentence(void **value, void *cl) {
    char *format[20];
    for (int i = 0; i < strlen(*value -> filename) - 2; i++) {
        format[i] = *value -> filename[i];
    }


    int digitsOfInteger = floor(log10(*value -> lineNumber) + 1)
    char *intToString[digitsOfInteger];
    sprintf(intToString, "%d", *value -> lineNumber);

    int count = 0;
    for (int i = 19 - digitsOfInteger; i < 20; i++) {

        format[i] = intToString[count++];
    }
    //printf("%s\n", *value -> filename);
}

*/
void free_table(Table_T *table) {
    Table_map(*table, free_list, NULL);
    Table_free(table);
}

static void free_list(const void *key, void **value, void *cl) {
    cl = cl;
    key = key;
    List_T tempList = *value;
    List_map(tempList, Sentence_free, NULL);
    List_free(&tempList);
}


void open_file(FILE **file, char *filename) {
    *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: file could not be opened");
        exit(4);
    }
}




