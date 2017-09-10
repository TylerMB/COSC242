#include <stdio.h>
#include <stdlib.h>
#define ARRAY_SIZE 10000

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

int binary_search(int *a, int n , int target){
    int middle;

    if (n <= 0){
        return 0;
    }
    middle = n/2;
    
    if(a[middle] == target){
        return 1;
    }
    if(middle > target){
        return binary_search(a,middle,target);
    }else{
        return binary_search(a+middle +1, n-(middle + 1),target);
    }
}

         
    
int main (int argc, char **argv) {
    int my_array[ARRAY_SIZE];
    FILE *infile;
    int num_item,i,result;
    

    if(argc == 1 || NULL == (infile = fopen(argv[1], "r"))){
        fprintf(stderr, "%s: can't find file %s\n", argv[0],argv[1]);
        return EXIT_FAILURE;
    }
    
    num_item =0;
    
    while (num_item <ARRAY_SIZE && 1==fscanf(infile,"%d", &my_array[num_item])){
        num_item++;
    }
    
    fclose(infile);

    while( 1== scanf("%d", &i)){
        result = binary_search(my_array,num_item,i);
        if (result == 1){
            printf("+\n");
        }else{
            printf("-\n");
        }
    }
        
                


    selection_sort(my_array, num_item);

 
    return EXIT_SUCCESS;
}
