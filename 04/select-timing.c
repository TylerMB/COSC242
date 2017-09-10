#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ARRAY_MAX 30000

/*selection-sort function*/ 

void selection_sort(int *a, int n){
    int i,temp,min,store;

    for(i=0; i < n -1; i ++){
        min = i; /* assume first index is min */

        /*search for next min in array*/

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


/*MainMethod initialising and creating array */ 
int main(void) {
    int my_array[ARRAY_MAX];
    clock_t start, end;
    int i, count = 0;
    while (count < ARRAY_MAX && 1 == scanf("%d", &my_array[count])) {
        count++;
    }
    start = clock();
    selection_sort(my_array, count);
    end = clock();
    for (i = 0; i < count; i++) {
        printf("%d\n", my_array[i]);
    }
    fprintf(stderr, "%d %f\n", count, (end - start) / (double)CLOCKS_PER_SEC);
    return EXIT_SUCCESS;
}
