#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "mylib.h"
#include "queue.h"

typedef enum { UNVISTED, VISTED_SELF,VISTED_DESCENDANTS } state_t;
typedef struct vertex vertex;

struct vertex{
    int predeccessor;
    int distance;
    int finish;
    state_t state; 
};

struct graphrec{
    int size;
    int **edges;
    vertex *vertices; 
};
/*Creates a new graph*/
graph graph_new(int vert){
    int i;
    graph g = emalloc(sizeof *g);
    g->size=vert;
    g->edges =emalloc(sizeof(int*)*vert);
    g->vertices = emalloc(vert *sizeof (vertex));
    for(i=0; i < g->size ; i++){
        g->edges[i] = calloc(g->size,sizeof (int));
    }
 
    return g;
}
/*Function for adding a edge*/
void graph_add_edge(graph g, int u , int v){
    g->edges[u][v] = 1;

}
/*Function for adding bidirectional edges*/
void graph_add_bidirectional_edges(graph g, int u, int v){
    g->edges[u][v] =1;
    g->edges[v][u] =1;
}
/*Free function for graph*/
void graph_free(graph g){
    int i;
    for(i=0; i < g->size; i++){
        free(g->edges[i]);
    }
    free(g->edges);
    free(g->vertices);
    free(g);
}
/*Print function for matrix*/
void graph_print(graph g){
    int i,j;
    printf("The Matrix\n");
    printf("  ");
    for(i=0; i < g->size; i++){
        printf("%d ", i);
    }
    printf("\n");
    for(i=0; i < g->size; i++){
        printf("%d ",i);
        for(j=0; j < g->size; j++){
            printf("%d ", g->edges[i][j]);
        }
        printf("\n");
    }
}
/*Prints function for adjacency list and graph table*/
void graph_print_table(graph g){
    int i,j,first=1;
    /*printing adjacency list*/
    printf("adjacency list:\n");
    for(i=0; i<g->size; i++){
        printf("%d | ",i);
      
        for(j=0;j< g->size;j++){
            if(g->edges[i][j]==1){
                if(first == 0){
                    printf(", ");
                }
                printf("%d",j);
                first=0;
            }
        }
        first=1;
        printf("\n");
       
    }
    /*Printing graph table*/
    printf("\n");
    printf("vertex distance pred\n");
    for(i=0; i< g->size; i++){
        printf("%4d %6d %7d\n",i,g->vertices[i].distance,g->vertices[i].predeccessor);
    }
    printf("\n");
}

/*Breadth first Search implementation */

void graph_bfs(graph g, int s){

    int i,v;
    int source =s;
    queue que = queue_new(); 
    for(i=0; i < g->size; i++){
        g->vertices[i].state= UNVISTED;
        g->vertices[i].distance =-1;
        g->vertices[i].predeccessor =-1; 
    }

    g->vertices[source].state=VISTED_SELF;
    g->vertices[source].distance=0;

    enqueue(que,source);

    while(queue_size(que) != 0){
      int u =  dequeue(que);
          for(v=0; v < g->size ; v++){
              if(g->edges[u][v] ==1 && g->vertices[v].state==UNVISTED){
                  g->vertices[v].state=VISTED_SELF;
                  g->vertices[v].distance =1 + g->vertices[u].distance;
                  g->vertices[v].predeccessor = u;
                  enqueue(que,v);
              }
  
      }
      g->vertices[u].state=VISTED_DESCENDANTS;
    }
    graph_print_table(g);
    queue_free(que);
   
    
    
    
}
