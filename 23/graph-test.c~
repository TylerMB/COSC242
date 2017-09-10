#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "mylib.h"

int main(void){

    graph g =NULL; 
    int u, v;

    if(1 ==scanf("%d", &u) && u >0){
       g = graph_new(u);
    }

    while(2==scanf(" %d %d", &u,&v)){
        graph_add_bidirectional_edges(g,u,v);
    }
    graph_bfs(g,1);
    graph_print(g);
    graph_free(g);

    return EXIT_SUCCESS;
}
