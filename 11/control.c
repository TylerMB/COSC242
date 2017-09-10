#include <stdio.h>
#include <stdlib.h>
#include "flexiarray.h"
#include "mylib.h"

int main(void){
    int item;
    flexarray myflexi = flexarray_new();

    while( 1 ==scanf("%d", &item)){
        flexarray_append(myflexi, item);
    }

    flexarray_sort(myflexi);
    flexarray_print(myflexi);
    flexarray_free(myflexi);

    return EXIT_SUCCESS;
}
