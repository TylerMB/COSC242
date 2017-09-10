#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

struct queue{
    int *items;
    int head;
    int capacity;
    int num_items;
};

queue queue_new(){

   queue result = malloc(sizeof *result);
    result -> head =0;
    result -> capacity=100;
    result ->items = malloc(result -> capacity *sizeof result->items[0]);
    result -> num_items=0;
 
    return result; 
}

void enqueue (queue q,int item){
    int index;
    if(q->num_items >= q->capacity){
        fprintf(stderr,"Capacity Full\n");
    }
    index=(q->head + q->num_items)%q->capacity;
        q->items[index] = item;
        q->num_items++;
    }

int dequeue(queue q){
    int item=0;

    if(q->num_items <= 0){
        fprintf(stderr,"Queue empty\n");
    }else{
        item = q->items[q->head];
        q->head = (q->head +1)%q->capacity;
        q->num_items--;
    }
    return item;

}

void queue_print(queue q){
    int i;
    int x = q->head;
    for(i=0; i < q->num_items; i++){
        printf("i: %.2d\n",q->items[x %q->capacity]);
        x++;
    }

}

int queue_size(queue q){
    return q->num_items;

}

queue queue_free(queue q){
    free(q->items);
    free(q);
    q=NULL;
    return q;
}
