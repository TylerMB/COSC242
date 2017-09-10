#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

struct queue {
    double *items;
    int head;
    int capacity;
    int num_items;
};

queue queue_new() {
    queue result = malloc (sizeof *result);
    result -> head =0;
    result -> capacity =7;
    result -> items = calloc(result-> capacity,sizeof result->items[0]);
    result -> num_items=0;

    return result;
}

void enqueue(queue q, double item) {
    if (q->num_items < q->capacity) {
        q->items[(q->head + q->num_items++) % q->capacity] = item;
    }
}

double dequeue(queue q) {
    double item=0;


    item = q->items[q->head];
    q->head = (q->head +1)%q->capacity;
    q->num_items--;
    
    return item;
}

void queue_print(queue q) {
    /* print queue contents one per line to 2 decimal places */
    int i;
    int x = q->head;
    for(i =0; i < q->num_items; i++){
        printf("%.2f\n",q->items[x % q->capacity]);
        x++;
    }
}

void queue_print_info(queue q) {
    int i;
    printf("capacity %d, num_items %d, head %d\n[", q->capacity,
           q->num_items, q->head);
    for (i = 0; i < q->capacity; i++) {
        printf("%s%.2f", i == 0 ? "" : ", ", q->items[i]);
    }
    printf("]\n");
}

int queue_size(queue q) {
    return q->num_items; 
}

queue queue_free(queue q) {
    free(q->items);
    free(q);
    
    return q;
}
