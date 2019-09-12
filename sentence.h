#include <stdio.h>
#include <stdlib.h>

#ifndef _SENTENCE_H_
#define _SENTENCE_H_

struct Sentence *Sentence_new(char *, char *, unsigned int);
void Sentence_free(struct Sentence *);
void cleanSentence(char *);

//Struct Sentence Definition
typedef struct Sentence {
	char *cleanedSentence;
	char *filename;
	unsigned int lineNumber;
}Sentence;

struct Sentence *Sentence_new(char *line, char *name, unsigned int lineNumber) {
	Sentence *s = (Sentence *) malloc(sizeof(Sentence));
	(*s).cleanedSentence = line;
	(*s).filename = name;
	(*s).lineNumber = lineNumber;
	return s;
}

void Sentence_free(Sentence *s) {
	free (s);
}

void cleanSentence(char *sentence) {
	char *iterateSentence = sentence;
	do {
		while (*iterateSentence == ' ') 
			++iterateSentence;
	} while((*sentence++ = *iterateSentence++));
}

#endif