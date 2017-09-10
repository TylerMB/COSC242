#include <stdio.h>
#include <stdlib.h>
#include "flexiarray.h"
#include "mylib.h"

struct flexarrayrec{
    int capacity;
    int itemcount;
    int *items;
};


static void merge(int *array, int *workspace, int len){
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
static void insertion_sort(int *a, int n){
    int key, i,current;

    for(i=1 ; i < n ; i ++){
        key = a[i];
        for(current = i; current > 0 && key < a[current-1]; current--){
            a[current] = a[current - 1];
        }
        a[current] = key;
        
    }


}


static void merge_sort(int *a, int *w, int n){
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
        f->items = erealloc(f->items,f->capacity * sizeof f[0]);

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
    int *workspace = emalloc (f->itemcount * sizeof workspace[0]);
    merge_sort(f->items, workspace,f->itemcount);

    free(workspace);

}

void flexarray_free(flexarray f){
    free(f->items);
    free(f);
}

