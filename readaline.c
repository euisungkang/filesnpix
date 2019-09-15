#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <readaline.h>
#include <assert.h>

//Function Prototypes
size_t readaline(FILE *inputfd, char **datapp);
void raise_exception(int);

//Constant Variables
const unsigned int MAX_SENTENCE_LENGTH = 200;

//Returns number of bytes in a sentence
size_t readaline(FILE *inputfd, char **datapp) {

    int Allocation_handled = 1;

    if ((inputfd == NULL) | (datapp == NULL))
        Allocation_handled = 0; 

    char *line = (char *) malloc(MAX_SENTENCE_LENGTH);

    char buffer = '$';

    do {
        buffer = fgetc(inputfd);
        line = strcat(line, &buffer);
    } while ((buffer != EOF) && (buffer != '\n'));

    if ((buffer != EOF) && (buffer != '\n') && (ferror(inputfd))) {

        if (*datapp == NULL)
            Allocation_handled = 0;
        else
            *datapp = line;     

        printf("Inside readaline: %s\n", *datapp);

        line = NULL;

        return strlen(*datapp);

    } else if (buffer == EOF) {
        *datapp = NULL;
    } else if (ferror(inputfd)) {
        Allocation_handled = 0;
        raise_exception(Allocation_handled);
        printf("readaline: input line too long\n");
        exit(4);
    }

    raise_exception(Allocation_handled);
    
    return 0;
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

