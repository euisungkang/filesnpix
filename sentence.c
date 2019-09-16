#include "sentence.h"

struct Sentence *Sentence_new(char *line, char *name, unsigned int lineNumber) {
    Sentence *s = (Sentence *) calloc(1, sizeof(Sentence));
    cleanSentence(line);

    s -> cleanedSentence = line;

    s -> filename = name;

    s -> lineNumber = lineNumber;
    return s;
}

void Sentence_free(Sentence *s) {
    if (s == NULL)
        return;
    free(s -> cleanedSentence);
    free(s);
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