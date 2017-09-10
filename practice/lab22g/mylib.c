#include <stdlib.h>
#include <stdio.h>
#include "mylib.h"

void *emalloc(size_t s){
    void *result = malloc(s);
    if (NULL == result){
        fprintf(stderr,"failed");
        exit(EXIT_FAILURE);
    }
    return result;
}
