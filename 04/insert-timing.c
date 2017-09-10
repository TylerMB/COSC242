#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ARRAY_MAX 30000

/*Insertion-sort function*/

void insertion_sort(int *a, int n){
int key,i,current;

/*Searching through array setting key to index at 1 ignoring first element*/ 
 for(i=1 ; i < n ; i ++){
     key = a[i];
     /*swapping element with previous index*/
     for(current = i; current > 0 && key < a[current - 1]; current --){
         a[current] = a[current - 1];
     }
     a[current] = key;
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
    insertion_sort(my_array, count);
    end = clock();
    for (i = 0; i < count; i++) {
        printf("%d\n", my_array[i]);
    }
    fprintf(stderr, "%d %f\n", count, (end - start) / (double)CLOCKS_PER_SEC);
    return EXIT_SUCCESS;
}
