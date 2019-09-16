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
void hash_file(FILE *, Table_T, char *);
int find_matches(Table_T);
void display_matches(const void *key, void **value, void *cl);
void free_table(Table_T *);
static void free_list(const void *key, void **value, void *cl);
char *commas_to_space(char *);

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
        hash_file(file, sentenceTable, argv[i]);
        fclose(file);
    }

    find_matches(sentenceTable);

    free_table(&sentenceTable);
    sentenceTable = NULL;

    return 0;
}

void hash_file(FILE *file, Table_T table, char *filename) {

    int lineCount = 1;
    char *tempSentence = "$";
    int fileReadSuccess = 0;
    
    do {
        fileReadSuccess = readaline(file, &tempSentence);

        if ((fileReadSuccess != -1) && (fileReadSuccess != 0)) {

            struct Sentence *s = Sentence_new(tempSentence, filename, lineCount++);

            char *key = s -> cleanedSentence;

            const char *sentenceAtom = Atom_new(key, strlen(key));

            void *doesBucketExist = Table_get(table, sentenceAtom);

            if (doesBucketExist == NULL) {
                Seq_T sentenceSeq = Seq_new(5); 
                Seq_addhi(sentenceSeq, s);
                Table_put(table, sentenceAtom, sentenceSeq);
            }
            else {
                Seq_T returnedSeq = doesBucketExist;
                Seq_addhi(returnedSeq, s);
            }
        }
        
    } while(fileReadSuccess != 0);
}

int find_matches(Table_T sentenceTable) {
    Table_map(sentenceTable, display_matches, NULL);
    return 0;
}



void display_matches(const void *key, void **value, void *cl) {
    int seqLength = (int) Seq_length((Seq_T) *value);
    if (seqLength > 1) {
        Seq_T currentSeq = (Seq_T) *value;

        bool first = true; 
        for (int i = 0; i < seqLength; i++) {
            Sentence *currentSentence = Seq_get(currentSeq, i); 
            
            if (first == true){
                char *curCleanedString = currentSentence -> cleanedSentence; 
                printf("%s", commas_to_space(curCleanedString));
                first = false; 
            }

            char format[20];
            int sizeOfFileName = (int) strlen(currentSentence -> filename);


            strcpy(format, currentSentence -> filename);
 
            int tempLineNum = (currentSentence -> lineNumber); 
            int digitsOfInteger = floor(log10(tempLineNum)) + 1;
            
            int power = digitsOfInteger; 
            for (int j = 20 - digitsOfInteger; j < 20; j++) {
                format[j] = (int) (tempLineNum / pow(10, power - 1) + 48);
                tempLineNum -= (10 * power); 
                power--; 
            }

            for (int j = sizeOfFileName; j < 20 - digitsOfInteger ; j++)
                format[j] = '-'; 

            printf("%s\n", format);
        }
    }
    (void) key;
    (void) cl;
}

char *commas_to_space(char *string) {

    for (size_t i = 0; i < strlen(string); i++)
        if (string[i] == ',') 
            string[i] = ' ';

    return string;
}

void free_table(Table_T *table) {
    Table_map(*table, free_list, NULL);
    Table_free(table);
}

static void free_list(const void *key, void **value, void *cl) {
    (void) cl;
    (void) key;

    Seq_T tempList = (Seq_T) *value;
    for (int i = Seq_length(tempList) - 1; i >= 0; i--)
        Sentence_free((Sentence *) Seq_get(tempList, i)); 
    Seq_free(&tempList);
}


void open_file(FILE **file, char *filename) {
    *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: file could not be opened");
        exit(4);
    }
}




