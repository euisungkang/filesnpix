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

    char *line = (char *) calloc(MAX_SENTENCE_LENGTH, sizeof(char)); 

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
        } while (buffer != '\n');

        if (ferror(inputfd)) {
            Allocation_handled = 0;
            raise_exception(Allocation_handled);
            printf("readaline: input line too long\n");
            raise_exception(Allocation_handled);
            exit(4);
        }    

        *datapp = line;

        line = NULL;

        return strlen(*datapp); 
    } else {
        return -1;
    }
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

