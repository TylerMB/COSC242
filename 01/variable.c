#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void){

    int i =0;
    double j = 1.0;

    for( i =0; i < 10; i ++){
        printf ("%4d %12f %14f \n",i,j,sqrt(j));
        j *=2;
    }

    return EXIT_SUCCESS;
}
