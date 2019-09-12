#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>
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

    char sentence[MAX_SENTENCE_LENGTH];

    if (fgets(sentence, MAX_SENTENCE_LENGTH, inputfd) != NULL) {

        int sizeOfSentence = sizeof(sentence);
        fseek(inputfd, sizeOfSentence + 1, SEEK_CUR);

        *datapp = (char *) malloc(sizeOfSentence);

        if (*datapp == NULL)
            Allocation_handled = 0;
        else
            **datapp = *sentence;

        return sizeOfSentence;

    } else if (feof(inputfd)) {
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
    if (Allocation_handled) {
        longjmp(Allocate_Failed, 1);
        assert(0);
    } 
}

