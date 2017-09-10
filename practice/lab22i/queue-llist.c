#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "queue.h"

typedef struct q_item *q_item;

struct q_item {
    double item;
    q_item next;
};

struct queue {
    q_item first;
    q_item last;
    int length;
};

queue queue_new() {
    queue q = malloc(sizeof *q);
    q->first = q->last = NULL;
    q->length=0;
    return q;
}

void enqueue(queue q, double item) {
    q_item i = malloc(sizeof *i);
    i->item = item;
    i->next = NULL;
    if (q->length == 0) {
        q->first = i;
    } else {
        q->last->next = i;
    }
    q->last = i;
    q->length++;
}

double dequeue(queue q) {
    q_item old = q->first;
    double d = old ->item;
    q->first = old ->next;
    free(old);
    return d;
}

void queue_print(queue q) {
    /* print queue contents one per line to 2 decimal places */
}

void queue_print_info(queue q) {
    if (q->length == 0) {
        printf("The queue is empty\n");
    } else {
        printf("first %.2f, last %.2f, length %d\n", q->first->item,
               q->last->item, q->length);
    }
}

int queue_size(queue q) {
}

void queue_free_aux(q_item i) {
}

queue queue_free(queue q) {
}
