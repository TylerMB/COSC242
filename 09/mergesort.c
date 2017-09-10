#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_LEN 2000000
int my_array[ARRAY_LEN];
int workspace[ARRAY_LEN];

void merge(int *array, int *workspace, int len){
    int left =0, right= len/2;

    while(left < len/2 && right < len){
        if(array[left] < array[right]){
            *workspace = array[left];
            workspace ++;
            left ++;

        }else{
            *workspace = array[right];
            workspace++;
            right++;
        }
    }
    while(left < len/2){
        *workspace = array[left];
        workspace++;
        left++;
    }
    while(right < len){
        *workspace = array[right];
        workspace++;
        right++;
    }
    
}

void insertion_sort(int *a, int n){
    int key, i,current;

    for(i=1 ; i < n ; i ++){
        key = a[i];
        for(current = i; current > 0 && key < a[current-1]; current--){
            a[current] = a[current - 1];
        }
        a[current] = key;
        
    }


}


void merge_sort(int *a, int *w, int n){
    int i;

    if(n < 40){
        insertion_sort(a,n);
    }else{

        merge_sort(a,w, n/2);
        merge_sort(a + n /2 ,w, n - n/2);

        merge(a,w,n);

        for(i =0; i < n; i ++){
            a[i] = w[i];
        }
    }
               
}

int main(void) {
   
    clock_t start, end;
    int i, count = 0;
    while (count < ARRAY_LEN && 1 == scanf("%d", &my_array[count])) {
        count++;
    }
    start = clock();
    merge_sort(my_array,workspace, count);
    end = clock();
    for (i = 0; i < count; i++) {
        printf("%d\n", my_array[i]);
    }
    fprintf(stderr, "%d %f\n", count, (end - start) / (double)CLOCKS_PER_SEC);
    return EXIT_SUCCESS;
}
