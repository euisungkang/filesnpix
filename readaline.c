/*
Easton, Andrew
Professor Monroe
Comp-40
09/16/2019

PROJECT: readaline.c
PURPOSE: Part B. Implementation of readaline, will read a single line from
         a file.
NOTE:    

Last Modified: 09/16/2019
*/

#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <readaline.h>
#include <assert.h>

//Function Prototypes
size_t readaline(FILE *, char **);
void expand_max_size(char **);
void raise_exception(int);

//Constant Variables
const unsigned int DEFAULT_SENTENCE_LENGTH = 100;

/*
PURPOSE: Reads a single line from given file, returns size of line */
size_t readaline(FILE *inputfd, char **datapp)
{
    //Case 1: If arguments are NULL
    if ((inputfd == NULL) | (datapp == NULL)) {
        fprintf(stderr, "Checked Runtime Error: arguments are NULL\n");
        raise_exception(0);
        exit(EXIT_FAILURE);
    }

    char *line = (char *) calloc(DEFAULT_SENTENCE_LENGTH, sizeof(char)); 
    int maxLineLength = DEFAULT_SENTENCE_LENGTH;

    //Case 2: If malloc/calloc failed
    if (line == NULL) {
        fprintf(stderr, "Checked Runtime Error: malloc failed\n");
        raise_exception(0);
        exit(EXIT_FAILURE);
    }

    char buffer = (char) fgetc(inputfd);

    //Case 3: If read from file fails
    if (ferror(inputfd)) {
        fprintf(stderr, "Checked Runtime Error: file could not be read\n");
        raise_exception(0);
        exit(EXIT_FAILURE);
    }

    if (buffer == EOF) {
        free(line);
        line = NULL;
        return 0;
    } else if (buffer != '\n') {

        line[0] = buffer;

        //Gets an entire line, stops on \n or EOF
        int indexcount = 1;
        do {
            buffer = fgetc(inputfd);
            line[indexcount++] = buffer;

            //Checks if line max size needs to be expanded
            if ((int) strlen(line) > maxLineLength - 1) {
                expand_max_size(&line);
                maxLineLength *= 2;
            }

        } while (buffer != '\n' && buffer != EOF);

        //Add '\n' if line ended with only \0, and no \n
        if (buffer == EOF)
            line[strlen(line) - 1] = '\n';

        *datapp = line;
        return strlen(*datapp); 

    } else if (buffer == '\n')
        return -1;

    return 0;
}

/*
PURPOSE: Doubles given string max size. Make bigger line, copy old
         string, redirect pointer.  */
void expand_max_size(char **s)
{
    char *biggerLine = (char *) calloc(strlen(*s) * 2, sizeof(char));
    strcpy(biggerLine, *s);
    free(*s);
    *s = biggerLine;
}

/*
PURPOSE: Raises exception, Hanson's Exceptions   */
void raise_exception(int Allocation_handled) {
    jmp_buf Allocate_Failed;
    if (Allocation_handled == 0) {
        longjmp(Allocate_Failed, 1);
        assert(0);
    } 
}