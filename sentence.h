#include <stdio.h>
#include <list.h>
#include <stdbool.h>
#include <stdlib.h>

#ifndef _SENTENCE_H_
#define _SENTENCE_H_

//Function Prototypes
struct Sentence *Sentence_new(char *, char *, unsigned int);
void Sentence_free(void **, void *);
void cleanSentence(char *);

//Struct Sentence Definition
typedef struct Sentence {
    char *cleanedSentence;
    char *filename;
    unsigned int lineNumber;
}Sentence;

struct Sentence *Sentence_new(char *line, char *name, unsigned int lineNumber) {
    Sentence *s = (Sentence *) malloc(sizeof(Sentence));
    cleanSentence(line);

    /*
    char *passByValueLine;
    while (*line)
        *passByValueLine++ = *line++;
    */

    s -> cleanedSentence = line;

    s -> filename = name;

    s -> lineNumber = lineNumber;
    return s;
}

void Sentence_free(void **ptr, void *cl) {
    (void) cl;

    if (*ptr == NULL)
        return;

    printf("%p\n", *ptr);


    Sentence *temp =  (Sentence *) *ptr;
    printf("%s\n", temp -> cleanedSentence);
    free(temp);
}

void cleanSentence(char *sentence) {
    char *iterateSentence = sentence;
    bool first = true;
    do {
        first = true; 
        while (*iterateSentence == ' ') {
            if (first){
                *iterateSentence = ','; 
                first = false; 
                *sentence++ = *iterateSentence++;                 

            }
            else{
            iterateSentence++;
            }
        } 

    } while((*sentence++ = *iterateSentence++));
}

#endif