#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"


void *emalloc(size_t s){
    void *result= malloc(s);
    if(NULL == result){
        fprintf(stderr,"error");
        exit(EXIT_FAILURE);
    }
    return result;
}
