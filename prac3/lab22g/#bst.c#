#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bst.h"
#include "mylib.h" 

struct bstnode{
    char *key;
    bst left;
    bst right;
};

bst bst_new(){
    return NULL;
}

bst bst_insert(bst b, char *str){
    int compare;
    if(NULL == b){
        b = emalloc(sizeof (*b));
        b->left = b->right = NULL;
        b->key = emalloc((strlen(str)+1)*sizeof (*str));
        strcpy(b->key,str);
        return b; 
    }

    compare = strcmp(b->key,str);
    if (compare != 0){
        if (compare > 0){
            b->left = bst_insert(b->left, str);
        }else{
            b->right = bst_insert(b->right, str);
        }
    }

    return b; 
       

}

void bst_inorder(bst b, void f (char *str)){

    if(NULL == b){
        return;
    }
    bst_inorder(b->left, f);
    f(b->key);
    bst_inorder(b->right,f); 

}


int bst_search(bst b, char *str){

    if(NULL == b){
        return 0;
    }else{
        int compare=strcmp(b->key,str);
        if(compare == 0){
            return 1;
        }else if(compare < 0){
            return bst_search(b->right,str);
        }else{
            return bst_search(b->left,str);
        }
    }
}

void bst_preorder(bst b, void f (char *str)){

    if(NULL == b){
        return;
    }

    f(b->key);
    bst_preorder(b->left, f);
    bst_preorder(b->right,f);

}

bst bst_free(bst b){

    if(NULL == b){
        return b;
    }
    
    bst_free(b->left);
    
    bst_free(b->right);
    free(b->key);
    free(b);

    return b;

}
