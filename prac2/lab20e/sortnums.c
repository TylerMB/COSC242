#include <stdlib.h>
#include <stdio.h>
#include "flexarray.h"

int main(void){
    int item;
    flexarray flex = flexarray_new();

    while(1==scanf("%d",&item)){
        flexarray_append(flex,item);
    }
    flexarray_sort(flex);
    flexarray_print(flex);
    flexarray_free(flex);

  
    return EXIT_SUCCESS; 
}
