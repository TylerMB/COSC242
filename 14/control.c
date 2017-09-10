#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "bst.h"

int main(void) {
    bst h = bst_new(18143);
    char word[256];
    char op;
    
    while (2== scanf (" %c %255s", &op, word)){
        if('+' == op){
            bst_insert(h,word);
        }else if ('?' == op){
            printf("%d %s\n", bst_search(h,word),word);
        }
    }
    bst_free(h);

    return EXIT_SUCCESS;
}
