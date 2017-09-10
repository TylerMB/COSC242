#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

int main(void){
    double item;
    queue que = queue_new();

    while(1==scanf("%lg",&item)){
        enqueue(que,item);
    }
    dequeue(que);
    queue_print(que);

    return EXIT_SUCCESS;
    

    
}
