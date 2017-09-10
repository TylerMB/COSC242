#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bst.h"
#include "mylib.h" 

struct bst_node{
    char *key;
    bst left;
    bst right;
};

bst bst_new(){
    return NULL;
}

bst delete_node (bst b) {
    if(b->right == NULL && b->left ==NULL){
        free(b->key);
        
        b= NULL;
        return b; 
    }else if(b->right !=NULL){
        char *tmp = b->key;
        b->key = b->right->key;
        b->right->key = tmp;
        b = bst_delete(b,tmp);
    }else if(b->left !=NULL){
        char *tmp = b->key;
        b->key = b->left->key;
        b->left->key = tmp;
        b = bst_delete(b,tmp);
    }else if(b->left != NULL && b->right !=NULL){

        bst temp = b->right;
        while(temp ->left != NULL){
            temp = temp->left;

        }
        strcpy(b->key,temp->key);
        b->right=bst_delete(b->right,temp->key);
        

    }
    return b;
}

bst bst_delete(bst b, char *str){

    if (NULL == b){
        return b;
    }
    if(strcmp(b->key,str) == 0){
        b =delete_node(b);
    }else if(strcmp(b->key,str) < 0){
        b->right = bst_delete(b->right, str);
    }else{
        b->left = bst_delete(b->left,str);
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

bst bst_insert(bst b, char *str){
    int compare;
    if(NULL == b){
        b = emalloc(sizeof *b);
        b->key = emalloc((strlen(str)+1)*sizeof *str);
        strcpy(b->key,str);
        return b; 
    }

    compare = strcmp(b->key,str);
    if (compare != 0){
        if (compare < 0){
            b->left = bst_insert(b->left, str);
        }else{
            b->right = bst_insert(b->right, str);
        }
    }

    return b; 
       

}

void bst_preorder(bst b, void f (char *str)){

    if(NULL == b){
        return;
    }

    f(b->key);
    bst_preorder(b->left, f);
    bst_preorder(b->right,f);

}

int bst_search(bst b, char *key){

    if(NULL == b){
        return 0;
    }else{
       int compare=strcmp(b->key,key);
        if(compare == 0){
            return 1;
        }else if(compare < 0){
            return bst_search(b->right,key);
        }else{
            return bst_search(b->left,key);
        }
    }
}




    
