#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "mylib.h"


typedef enum { UNVISTED, VISTED_SELF,VISTED_DESCENDANTS } state_t;


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
    printf("vertex distance pred finish\n");
    for(i=0; i< g->size; i++){
        printf("%4d %6d %7d %5d\n",i,g->vertices[i].distance,g->vertices[i].predeccessor,g->vertices[i].finish);
    }
    printf("\n");
}

/*Graph Depth first Search implementation */
 int step;

void graph_dfs(graph g){
    int i;
    for(i =0; i< g->size; i++){
        g->vertices[i].state = UNVISTED;
        g->vertices[i].predeccessor = -1;
    }

    step =0;
    for(i=0; i< g->size; i++){
        if(g->vertices[i].state == UNVISTED){
            visit(g,i);
        }
    }
    graph_print_table(g);
}

void visit(graph g ,int v){
    int u;
    g->vertices[v].state=VISTED_SELF;
    step++;
    g->vertices[v].distance = step;

    for(u=0; u < g->size; u++){
        if(g->edges[v][u] ==1 && g->vertices[u].state ==UNVISTED){
            g->vertices[u].predeccessor=v;
            visit(g,u);
        }
    }
    step++;
    g->vertices[v].state=VISTED_DESCENDANTS;
    g->vertices[v].finish=step;

    

}
