#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <readaline.h>
#include <assert.h>

//Function Prototypes
size_t readaline(FILE *inputfd, char **datapp);
void check_error(FILE *, )
void raise_exception(int);
int expand_max_size(char **);

//Constant Variables
const unsigned int DEFAULT_SENTENCE_LENGTH = 100;

//Returns number of bytes in a sentence
size_t readaline(FILE *inputfd, char **datapp) {

    int Allocation_handled = 1;

    if ((inputfd == NULL) | (datapp == NULL))
        Allocation_handled = 0; 

    char *line = (char *) calloc(DEFAULT_SENTENCE_LENGTH, sizeof(char)); 
    int maxLineLength = DEFAULT_SENTENCE_LENGTH;

    if (line == NULL)
        Allocation_handled = 0;

    char buffer = (char) fgetc(inputfd);

    if (buffer == EOF) {
        free(line);
        line = NULL;
        return 0;
    } else if (buffer != '\n') {

        line[0] = buffer;

        int indexcount = 1;
        do {
            buffer = fgetc(inputfd);
            line[indexcount++] = buffer;
            if ((int) strlen(line) > maxLineLength - 1)
                maxLineLength = expand_max_size(&line);
        } while (buffer != '\n' && buffer != EOF);

        if (ferror(inputfd)) {
            Allocation_handled = 0;
            raise_exception(Allocation_handled);
            printf("readaline: input line too long\n");
            raise_exception(Allocation_handled);
            exit(4);
        }    

        if (buffer == EOF)
            line[strlen(line) - 1] = '\n';

        *datapp = line;

        return strlen(*datapp); 
    } else if (buffer == '\n') {
        return -1;
    }
    return -2;
}


int expand_max_size(char **s) {
    char *biggerLine = (char *) calloc(strlen(*s) * 2, sizeof(char));

    strcpy(biggerLine, *s);
    free(*s);
    *s = biggerLine;

    return strlen(biggerLine);
}


void raise_exception(int Allocation_handled) {
    jmp_buf Allocate_Failed;
    if (Allocation_handled == 0) {
        printf("Before raising\n");
        longjmp(Allocate_Failed, 1);
        printf("After raising\n");
        assert(0);
    } 
}

