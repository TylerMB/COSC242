#include <stdlib.h>
#include <stdio.h>

int is_prime(int candidate){
    int i;
    for(i=2; i < candidate; i++){
        if(candidate%i == 0){
            return 0;
        }
    }
    return 1;
}

int main(void){

    int candidate =2;
    int num_print=0;
    while (num_print < 200){
        if(is_prime(candidate)){
            printf("%5d", candidate);
            num_print++;
            if(num_print%10 ==0){
                printf("\n");
            }
        }
        candidate++;
    }
    return EXIT_SUCCESS;
}
