#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"


void insertion_sort(int *a, int n){
    int key,i,current;

    for(i=1 ; i < n ; i ++){
        key = a[i];
        for(current = i; current > 0 && key < a[current - 1]; current --){
            a[current] = a[current - 1];
        }
        a[current] = key;
    }
}


static void arrayprint(int *a, int n){
    int i;

    for(i=0; i < n; i++){
        printf("%d\n",a[i]);
    }
}

int main(void){
    int capacity =2;
    int itemcount =0;
    int item;
    int *myarray = emalloc(capacity * sizeof myarray[0]);

   

    while( 1== scanf("%d", &item)) {
        if(itemcount == capacity){
            capacity += capacity;
            myarray = erealloc(myarray, capacity * sizeof myarray[0]);
           
        }
        myarray[itemcount] = item;
        itemcount++;
    }
    insertion_sort(myarray,itemcount);

    arrayprint(myarray, itemcount);
    free(myarray);

    return EXIT_SUCCESS;
}
