#include <stdlib.h>
#include <stdio.h>
#include "flexarray.h"

struct flexarrayrec{
    int capacity;
    int itemcount;
    int *items;
};

void selection_sort(int *a, int n){
    int i,temp,min,store,f;

    for(i=0; i < n -1; i ++){
        min = i; /* assume first index is min */

        /*search for next min */ 

        for(temp = i + 1; temp < n; temp++){
            if(a[temp] < a[min]){
                min = temp; /* index of min */
            } 
        }
        /* swapping elements */ 
        store = a[i];
        a[i] = a[min];
        a[min]=store;

        if(i == n/2-1){
            for(f=0; f < n; f++){
                fprintf(stderr,"%d\n",a[f]);
            }
        }
    }
   
}

void *emalloc(size_t s){
    void *result =malloc(s);
    if (NULL==result){
        fprintf(stderr,"Memory failed");
        exit(EXIT_FAILURE);
    }
    return result;
}

void *erealloc(void *p, size_t s){
    p =realloc (p,s);
    if(p == NULL){
        fprintf(stderr,"Memory failed");
        exit(EXIT_FAILURE);
    }
    return p;

}

flexarray flexarray_new(){
    flexarray result = emalloc (sizeof *result);
    result -> capacity =2;
    result -> itemcount=0;
    result -> items= emalloc(result ->capacity *sizeof result ->items[0]);
    return result;

}

void flexarray_append(flexarray f, int num){
    if(f-> itemcount == f->capacity){
        f->capacity += f->capacity;
        f->items = erealloc (f->items,f->capacity*sizeof f[0]);
    }
    f->items[f->itemcount++] = num;

}

void flexarray_print(flexarray f){
    int i;
    for(i =0; i < f->itemcount; i++){
        printf("%d\n",f->items[i]);
    }
}

void flexarray_sort(flexarray f){
    selection_sort(f->items,f->itemcount);

}

void flexarray_free(flexarray f){
    free(f->items);
    free(f);

}
