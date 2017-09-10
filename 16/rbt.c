#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "rbt.h"
#include "mylib.h"

#define IS_BLACK(x) ((NULL == (x)) || (BLACK == (x)->colour))
#define IS_RED(x) ((NULL != (x)) && (RED == (x)->colour))


typedef enum {RED, BLACK} rbt_colour;

struct rbt_node{
    char *key;
    rbt_colour colour; 
    rbt left;
    rbt right;
};

rbt rbt_new(){
    return NULL;
}

rbt delete_node (rbt b) {
    if(b->right == NULL && b->left ==NULL){
        free(b->key);
        
        b= NULL;
        return b; 
    }else if(b->right !=NULL){
        char *tmp = b->key;
        b->key = b->right->key;
        b->right->key = tmp;
        b = rbt_delete(b,tmp);
    }else if(b->left !=NULL){
        char *tmp = b->key;
        b->key = b->left->key;
        b->left->key = tmp;
        b = rbt_delete(b,tmp);
    }else if(b->left != NULL && b->right !=NULL){

        rbt temp = b->right;
        while(temp ->left != NULL){
            temp = temp->left;

        }
        strcpy(b->key,temp->key);
        b->right=rbt_delete(b->right,temp->key);
        

    }
    return b;
}

rbt rbt_delete(rbt b, char *str){

    if (NULL == b){
        return b;
    }
    if(strcmp(b->key,str) == 0){
        b =delete_node(b);
    }else if(strcmp(b->key,str) < 0){
        b->right = rbt_delete(b->right, str);
    }else{
        b->left = rbt_delete(b->left,str);
    }
      
    

    return b;
         
        

}

rbt left_rotate(rbt r){
    rbt temp = r;
    r = r->right;
    temp->right = r->left;
    r->left = temp;
    return r;
}

rbt right_rotate(rbt r){
    rbt temp = r;
    r = r->left;
    temp->left = r->right;
    r->right = temp;
    return r;
}

rbt rbt_fix(rbt r){
    if (IS_RED(r->left) && IS_RED(r->left->left)) {
        if (IS_RED(r->right)) {
            r->colour = RED;
            r->left->colour = BLACK;
            r->right->colour = BLACK;
        } else {
            r = right_rotate(r);
            r->colour = BLACK;
            r->right->colour = RED;
        }
    }
    else if (IS_RED(r->left) && IS_RED(r->left->right)) {
        if (IS_RED(r->right)) {
            r->colour = RED;
            r->left->colour = BLACK;
            r->right->colour = BLACK;
        } else {
            r->left = left_rotate(r->left);
            r = right_rotate(r);
            r->colour = BLACK;
            r->right->colour = RED;
        }
    }
    else if (IS_RED(r->right) && IS_RED(r->right->left)) {
        if (IS_RED(r->left)) {
            r->colour = RED;
            r->left->colour = BLACK;
            r->right->colour = BLACK;
        } else {
            r->right = right_rotate(r->right);
            r = left_rotate(r);
            r->colour = BLACK;
            r->left->colour = RED;
        }
    }
    else if (IS_RED(r->right) && IS_RED(r->right->right)) {
        if (IS_RED(r->left)) {
            r->colour = RED;
            r->left->colour = BLACK;
            r->right->colour = BLACK;
        } else {
            r = left_rotate(r);
            r->colour = BLACK;
            r->left->colour = RED;
        }
    }
    return r;
}




void rbt_inorder(rbt b, void f (char *str)){

    if(NULL == b){
        return;
    }
    rbt_inorder(b->left, f);
    f(b->key);
    rbt_inorder(b->right,f); 

}

rbt rbt_free(rbt b){

    if(NULL == b){
        return b;
    }
    
    rbt_free(b->left);
    
    rbt_free(b->right);
    free(b->key);
    free(b);

    return b;

}

rbt rbt_insert(rbt b, char *str){
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
            b->left = rbt_insert(b->left, str);
        }else{
            b->right = rbt_insert(b->right, str);
        }
    }

    return b; 
       

}

void rbt_preorder(rbt b, void f (char *str)){

    if(NULL == b){
        return;
    }

    f(b->key);
    rbt_preorder(b->left, f);
    rbt_preorder(b->right,f);

}

int rbt_search(rbt b, char *key){

    if(NULL == b){
        return 0;
    }else{
       int compare=strcmp(b->key,key);
        if(compare == 0){
            return 1;
        }else if(compare < 0){
            return rbt_search(b->right,key);
        }else{
            return rbt_search(b->left,key);
        }
    }
}




    
