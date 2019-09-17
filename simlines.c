/*
Easton, Andrew
Professor Monroe
Comp-40
09/16/2019

PROJECT: simlines.c
PURPOSE: Implementation of simlines, primary file of program. Will insert
         all data into table, and display all matches
NOTE:    

Last Modified: 09/16/2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <table.h>
#include <string.h>
#include <seq.h>
#include <math.h>
#include "sentence.h"
#include "atom.h"
#include "readaline.h"

//Function Prototypes
void open_file(FILE **, char *);
void hash_file(FILE *, Table_T, char *);
void find_matches(Table_T);
void display_matches(const void *key, void **value, void *cl);
void free_table(Table_T *);
static void free_seq(const void *key, void **value, void *cl);
char *commas_to_space(char *);

int main (int argc, char *argv[])
{
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

    //Find and display all matches
    find_matches(sentenceTable);

    //Free all memory in heap
    free_table(&sentenceTable);
    sentenceTable = NULL;

    exit(EXIT_SUCCESS);
}

/*
PURPOSE: Hashes an entire file by line into a given table. Uses atoms as
         indexes in the table. The table is filled with Hansen's sequences */
void hash_file(FILE *file, Table_T table, char *filename)
{
    int lineCount = 1;
    char *sentence = "$";

    int fileReadSuccess = 0;    //Determines if readaline() was successful
    
    //Runs until readaline reaches EOF
    do {
        fileReadSuccess = readaline(file, &sentence);

        //0 = EOF, -1 = line with only '\n'
        if ((fileReadSuccess != 0) && (fileReadSuccess != -1)) {

            //Initialize sentence struct, see sentence.c | sentence.h
            struct Sentence *s = Sentence_new(sentence, filename, lineCount++);

            char *key = s -> cleanedSentence;

            const char *sentenceAtom = Atom_new(key, strlen(key));

            //Table_get returns NULL if a bucket is not initialized
            void *doesBucketExist = Table_get(table, sentenceAtom);

            if (doesBucketExist == NULL) {

                //Create new sequence, add to it, and put the seq in table
                Seq_T sentenceSeq = Seq_new(5); 
                Seq_addhi(sentenceSeq, s);
                Table_put(table, sentenceAtom, sentenceSeq);
            }
            else {

                //Edit the seq with the new value
                Seq_T returnedSeq = doesBucketExist;
                Seq_addhi(returnedSeq, s);
            }
        } else if (fileReadSuccess == -1)
            lineCount++;    //If line only contains '\n', just increase count
    } while(fileReadSuccess != 0);
}

/*
PURPOSE: Iterates and prints all the matches in the table's sequences */
void find_matches(Table_T sentenceTable)
{
    Table_map(sentenceTable, display_matches, NULL);
}

/*
PURPOSE: Displays all the matches for one bucket/key   */
void display_matches(const void *key, void **value, void *cl)
{
    int seqLength = (int) Seq_length((Seq_T) *value);

    //If there are matches, seq length must be > 1
    if (seqLength > 1) {

        Seq_T currentSeq = (Seq_T) *value;

        bool printMatch = true;    //Keeps track of printing the matched word once

        for (int i = 0; i < seqLength; i++) {
            Sentence *currentSentence = (Sentence *) Seq_get(currentSeq, i); 
            
            //Print matched word/key once.
            if (printMatch == true) {
                char *cleanedString = currentSentence -> cleanedSentence; 
                printf("%s", commas_to_space(cleanedString));
                printMatch = false; 
            }

            char *filename = currentSentence -> filename;

            //Print filename
            printf("%s", filename);
 
            //Number of digits in line number
            int digitsOfInteger = floor(log10(currentSentence -> lineNumber)) + 1;

            //Print dashes '-'
            int dprint = (int) (20 - strlen(filename) - digitsOfInteger);
            if (dprint > 0) 
                printf("%.*s", dprint , "                        ");

            //Print line number
            printf("%u\n", currentSentence -> lineNumber);
        }
    }
    (void) key;
    (void) cl;
}

/*
PURPOSE: Changes all commas to spaces in a given string */
char *commas_to_space(char *string)
{
    for (size_t i = 0; i < strlen(string); i++)
        if (string[i] == ',') 
            string[i] = ' ';

    return string;
}

/*
PURPOSE: Frees all malloc memory in a given table   */
void free_table(Table_T *table)
{
    Table_map(*table, free_seq, NULL);
    Table_free(table);
}

/*
PURPOSE: Frees all malloc memory in a given sequence */
static void free_seq(const void *key, void **value, void *cl)
{
    Seq_T tempList = (Seq_T) *value;
    for (int i = Seq_length(tempList) - 1; i >= 0; i--)
        Sentence_free((Sentence *) Seq_get(tempList, i)); 
    Seq_free(&tempList);

    (void) cl;
    (void) key;
}

/*
PURPOSE: Opens a file, checks for error and exits */
void open_file(FILE **file, char *filename)
{
    *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: file could not be opened");
        exit(EXIT_FAILURE);
    }
}