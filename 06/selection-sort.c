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
void print_array(int *a, int n){
    if ( n > 0 ) {
        printf("%d\n", a[0]);
        print_array(a + 1, n -1);
    }
}

int main (void) {
    int my_array[ARRAY_MAX];
    int count = 0;

    while (count < ARRAY_MAX && 1 == scanf("%d", &my_array[count])){
        count ++;
    }

    selection_sort(my_array, count);
    print_array(my_array, count);
 

                     
    return EXIT_SUCCESS;
}
