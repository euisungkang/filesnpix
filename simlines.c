#include <stdio.h>
#include <table.h>
#include <string.h>
#include <stdlib.h>
#include <list.h>
#include <seq.h>
#include <math.h>
#include "sentence.h"
#include "atom.h"
#include "readaline.h"

//Function Prototypes
void open_file(FILE **, char *);
void hash_file(FILE *, Table_T *, char *);
int find_matches(Table_T);
void display_matches(const void *key, void **value, void *cl);
void print_sentence(void **, void*);
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

    free_table(&sentenceTable);
    sentenceTable = NULL;

    //printf("%d\n", find_matches(sentenceTable));

    return 0;
}

void hash_file(FILE *file, Table_T *table, char *filename) {

    int lineCount = 1;
    char *tempSentence = "";
    int fileReadSuccess = 0;
    
    do {
        fileReadSuccess = readaline(file, &tempSentence);

        if ((fileReadSuccess != -1) && (fileReadSuccess != 0)) {

            char copyOfSentence[strlen(tempSentence)];
            for (size_t i = 0; i < strlen(tempSentence); i++)
                copyOfSentence[i] = tempSentence[i];

            //printf("Line Count: %u\n", lineCount);
            //printf("\nValue of tempSentence: %s", tempSentence);

            struct Sentence *s = Sentence_new(copyOfSentence, filename, lineCount++);

            char *key = s -> cleanedSentence;
            //printf("\nThis is key: %s", key);

            const char *sentenceAtom = Atom_new(key, strlen(key));

            void *doesBucketExist = Table_get(*table, sentenceAtom);

            if (doesBucketExist == NULL) {
                //replace with sequence
               // Seq_T *sentenceList = (Seq_T *) malloc(sizeof(List_T));
                Seq_T sentenceList = Seq_new(5); 
                Seq_addhi(sentenceList, s);
                Table_put(*table, sentenceAtom, sentenceList);
                //printf("%d\n", List_length(*sentenceList));
            }
            else {
                Seq_T returnedList = doesBucketExist;
                Seq_addhi(returnedList, s);
                Table_put(*table, sentenceAtom, returnedList);
                //printf("%d\n", List_length(*returnedList));
            }
        }
        free(tempSentence);
    } while(fileReadSuccess != 0);

   
    printf("\nTable length is: %d\n", Table_length(*table));
}

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
    value = value;
    cl = cl; 
    int temp1;  
    for (int i = 0; i < (int)strlen(((Sentence *) value)->filename) - 2; i++) {
        *(format[i]) = (((Sentence *) value) -> filename)[i];
        temp1 = i; 
    }

    int tempLineNum = ((Sentence *) value) -> lineNumber; 	
    int digitsOfInteger = floor(log10(tempLineNum + 1));
    /*
    char *intToString[digitsOfInteger];
    sprintf(intToString, "%s", (((Sentence *) value) -> lineNumber));
    */
    
   
   // int count = 0;
    int power = digitsOfInteger; 
    for (int i = 19 - digitsOfInteger; i < 20; i++) {
	
        *(format[i]) = (char)trunc(tempLineNum / (10 * power));
        power--; 
    }

    for (int i = temp1; i < 20 - digitsOfInteger ; i++){
            *(format[i]) = '-'; 
    }
    //printf("%s\n", *value -> filename
}


void free_table(Table_T *table) {
    Table_map(*table, free_list, NULL);
    printf("%d\n",Table_length(*table));
    Table_free(table);
    //printf("%d\n",Table_length(*table));
}

static void free_list(const void *key, void **value, void *cl) {
    (void) cl;
    (void) key;
    Seq_T tempList = (Seq_T) *value;
    for (int i = Seq_length(tempList); i >= 0; i--){
        Sentence_free(Seq_get(tempList, i), NULL); 
    }
    //List_map(tempList, Sentence_free, NULL);
    //printf("%d\n",List_length(tempList));
    Seq_free(&tempList);
    //free(tempList);
    //printf("%d\n",List_length(tempList));
}


void open_file(FILE **file, char *filename) {
    *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: file could not be opened");
        exit(4);
    }
}




