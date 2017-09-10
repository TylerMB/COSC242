#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"

void *emalloc(size_t s){
    void *result = malloc(s);
    if(result == NULL){
        fprintf(stderr,"Memory allocation failed \n");
        exit(EXIT_FAILURE);
    }
    return result; 

}

void *erealloc(void *p, size_t s){

    p = realloc (p, s);
    if(p == NULL){
        fprintf(stderr,"Memory relocation failed \n");
        exit(EXIT_FAILURE);
    }

    return p; 
}
