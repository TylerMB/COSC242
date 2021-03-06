#include <stdio.h>
#include <stdlib.h>

void display_repeats(int *my_dynamic_array, int n ){

    int i;
    
    int *repeat_array = malloc(n * sizeof repeat_array[0]);

    
    for(i = 0; i < n ; i ++){
        repeat_array[i] = 0;
    }
    
    for(i =0; i < n ; i ++){
        repeat_array[my_dynamic_array[i]] += 1;
    }

    for(i=0; i < n ; i ++){
        if(repeat_array[i] > 1){
            printf ("%d Number has been repeated : %d \n",i,repeat_array[i]);
        }
    }

    free(repeat_array);
}



int main (void) {
    int array_size = 0;
    int *my_dynamic_array;
    int i = 0;

    printf("Enter the size of the array: ");
    scanf("%d", &array_size);

    /* initialise array and the size */
    my_dynamic_array = malloc(array_size * sizeof my_dynamic_array[0]);
    if (NULL == my_dynamic_array) {
        fprintf (stderr, "memory allocation failed ! \n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < array_size; i ++ ){
        my_dynamic_array[i] = rand() % array_size;
    }

    printf("What's in the array: \n");
    for (i = 0; i < array_size; i++){
        printf("%d ", my_dynamic_array[i]);
    }
    printf("\n");
    printf("\n");
    display_repeats(my_dynamic_array,array_size);

    /* release the memory associated with the array */
    free(my_dynamic_array);
    return EXIT_SUCCESS;
}


