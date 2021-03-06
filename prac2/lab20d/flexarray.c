#include <stdio.h>
#include <stdlib.h>
#include "flexarray.h"


struct flexarrayrec{
    int capacity;
    int itemcount;
    int *items;
};

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



void insertion_sort(int *a, int n){
    int key,j,i,f;

    for(i=1; i < n; i++){
        key=a[i]; /*value we want to check */
        j=i-1; /* j is behind */
        /*searching loop */
        while(j >=0 && a[j] >key){
            a[j+1] =a[j];
            j=j-1;
            a[j+1]=key;
        }
        if(i == n/2-1){
            for(f=0; f < n ; f++){
                fprintf(stderr, "%d\n",a[f]);
            }
        }
    }
}






flexarray flexarray_new() {
    flexarray result = emalloc(sizeof *result);
    result -> capacity =2;
    result -> itemcount =0;
    result -> items = emalloc(result -> capacity * sizeof result -> items[0]);
    return result;
}

void flexarray_append(flexarray f, int num){
    if(f-> itemcount == f-> capacity){
        f-> capacity += f->capacity;
        f->items = erealloc(f->items,f->capacity * sizeof f->items[0]);

    }
    f->items[f->itemcount++] = num;
    
    
}

void flexarray_print(flexarray f){
    int i;
    for(i=0; i < f->itemcount; i ++){
        printf("%d\n",f->items[i]);
    }
}

void flexarray_sort(flexarray f){
    insertion_sort(f->items,f->itemcount);

}

void flexarray_free(flexarray f){
    free(f->items);
    free(f);
}

