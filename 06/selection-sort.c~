#include <stdio.h>
#include <stdlib.h>
#define ARRAY_MAX 10

void selection_sort(int *a, int n){
    int i,temp,min,store;

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
    }

}

int main (void) {
    int my_array[ARRAY_MAX];
    int i, count = 0;

    while (count < ARRAY_MAX && 1 == scanf("%d", &my_array[count])){
        count ++;
    }

    selection_sort(my_array, count);
    for ( i = 0; i < count; i ++ ){
        printf ("%d\n", my_array[i]);
    }
    return EXIT_SUCCESS;
}
