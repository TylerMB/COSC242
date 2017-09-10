#include <stdlib.h>
#include <stdio.h>

void repeat(int *array, int size){
    int *repeat;
    int i;

    repeat=malloc(size *sizeof repeat[0]);
    if(repeat == NULL){
        fprintf(stderr,"Memory failed");
        exit(EXIT_FAILURE);
    }

    for(i=0; i < size; i++){
        repeat[i] = 0;
    }

    for(i=0; i < size; i++){
        repeat[array[i]] +=1;
    }

    for(i=0; i < size ; i++){
        if(repeat[i] > 1){
        printf("%d occurs %d times\n",i, repeat[i]);
        }
    }
    
    free (repeat);

}

int main(void){
    int array_size =0;
    int *my_array;
    int i;

    printf("Enter the size of the array:\n"); 
    scanf("%d", &array_size);

    my_array=malloc(array_size *sizeof my_array[0]);
    if (my_array ==NULL){
        fprintf(stderr,"Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for(i =0; i < array_size; i++){
        my_array[i] = rand() % array_size;
    }
    printf("What's in the array:\n");
    for(i=0; i < array_size; i ++){
        printf("%d ", my_array[i]);
    }
    printf("\n");
 
    repeat(my_array,array_size);
    free(my_array);

    return EXIT_SUCCESS;
}
