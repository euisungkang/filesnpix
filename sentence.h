/*
Easton, Andrew
Professor Monroe
Comp-40
09/16/2019

PROJECT: sentence.h
PURPOSE: Header file for Sentence struct + functions. This is a custom created
         file. 
NOTE:    

Last Modified: 09/16/2019
*/

#include <stdio.h>
#include <list.h>
#include <stdbool.h>
#include <stdlib.h>

#ifndef _SENTENCE_H_
#define _SENTENCE_H_

//Function Prototypes
extern struct Sentence *Sentence_new(char *, char *, unsigned int);
extern void Sentence_free(struct Sentence *);
extern void cleanSentence(char *);

//Struct Sentence Definition
typedef struct Sentence {
    char *cleanedSentence;
    char *filename;
    unsigned int lineNumber;
} Sentence;

#endif