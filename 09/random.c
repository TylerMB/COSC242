#include <stdlib.h>
#include <stdio.h>

int main(int argsc,char **argv){

    int hold = 0;
    hold = atoi(argv[1]);

    if(argsc < 2){
        fprintf(stderr,"failed lol");
        return EXIT_FAILURE;
    }

    while(hold > 0){
        printf("%d\n", rand());
        hold--; 
       
    }
    
    return EXIT_SUCCESS; 
}
