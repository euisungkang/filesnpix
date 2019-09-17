/*
Easton, Andrew
Professor Monroe
Comp-40
09/16/2019

PROJECT: sentence.c
PURPOSE: Definition for Sentence struct functions. This is a custom created
         file. 
NOTE:    

Last Modified: 09/16/2019
*/

#include "sentence.h"

/*
PURPOSE: Creates a new Sentence in the heap, sets all its values,
         and returns it        */
struct Sentence *Sentence_new(char *line, char *name, unsigned int lineNumber)
{
    Sentence *s = (Sentence *) calloc(1, sizeof(Sentence));
    cleanSentence(line);    //Replace spaces with commas
    s -> cleanedSentence = line;
    s -> filename = name;
    s -> lineNumber = lineNumber;
    return s;
}

/*
PURPOSE: Frees all malloc memory in Sentence     */
void Sentence_free(Sentence *s)
{
    if (s == NULL)
        return;
    free(s -> cleanedSentence);
    free(s);
}

/*
PURPOSE: Replaces all spaces with a comma in a given string   */
void cleanSentence(char *sentence)
{
    char *iterateSentence = sentence;
    bool first = true;  //Keeps track of cases with multiple spaces

    //Iterate and assigns each char into given sentence
    do {
        first = true;

        //If a space is detected
        while (*iterateSentence == ' ') {
            if (first) {

                //Replace with comma, and iterate + assign to sentence
                *iterateSentence = ','; 
                first = false; 
                *sentence++ = *iterateSentence++;                 
            }
            else
                iterateSentence++;
        } 
    } while((*sentence++ = *iterateSentence++));
}