/**
 * @file tree.c
 * @author Josh Crosbie, Tyler Baker, David Fontein.
 * @date September 2016.
 * tree.c contains all the methods that are to be used in the construction of
 * a combination ADT, tree which can either be a balanced RBT or an ordinary 
 * BST. 
 * */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tree.h"
#include "mylib.h"

#define IS_BLACK(x) ((NULL == (x)) || (BLACK == (x)->colour))
#define IS_RED(x) ((NULL != (x)) && (RED == (x)->colour))

/* holds the value passed to the tree constructor */
static tree_t tree_type;

struct tree_node{
    char *key;
    colour_t colour; 
    tree left;
    tree right;
    int frequency;
};

/**
 * Combination ADT that which can either be a RBT or BST
 * @return NULL.
 */
tree tree_new(tree_t tree_choice){
    tree_type = tree_choice;
    return NULL;
}

    /** 
     * Compute the "tree_depth" of a tree -- the number of 
     * nodes along the longest path from the root node 
     * down to the farthest leaf node.
     * @param t the root node of the tree.
     * @param the depth of the tree.
     */

int tree_depth(tree t) {
   if(t->left != NULL && t->right != NULL){
    return tree_depth(t->left) > tree_depth(t->right) 
      ? tree_depth(t->left)+1 : tree_depth(t->right)+1;
   }else if(t->left != NULL){
    return tree_depth(t->left)+1;
  }else if(t->right != NULL){
    return tree_depth(t->right)+1;
  }else{
    return 0;
  }
}

/** Performs a left rotation of the tree.
 * @param t the tree to be rotated.
 * @return t the rotated tree.
 */

tree left_rotate(tree t){
    tree temp = t;
    t = t->right;
    temp->right = t->left;
    t->left = temp;
    return t;
}

/** Performs a right rotation of the tree.
 * @param t the tree to be rotated.
 * @return t the rotated tree.
 */
tree right_rotate(tree t){
    tree temp = t;
    t = t->left;
    temp->left = t->right;
    t->right = temp;
    return t;
}

/** Makes the first node black
 * @oaram t
 * @return t
 * */
 
 tree fix_root(tree t){
     t->colour = BLACK;
     return t;
 }

/** Fixes the layout of the RBT.
 * @param t the RBT to be fixed.
 * @return t the fixed RBT.
 */
static tree tree_fix(tree t){
    if (IS_RED(t->left) && IS_RED(t->left->left)) {
        if (IS_RED(t->right)) {
            t->colour = RED;
            t->left->colour = BLACK;
            t->right->colour = BLACK;
        } else {
            t = right_rotate(t);
            t->colour = BLACK;
            t->right->colour = RED;
        }
    }
    else if (IS_RED(t->left) && IS_RED(t->left->right)) {
        if (IS_RED(t->right)) {
            t->colour = RED;
            t->left->colour = BLACK;
            t->right->colour = BLACK;
        } else {
            t->left = left_rotate(t->left);
            t = right_rotate(t);
            t->colour = BLACK;
            t->right->colour = RED;
        }
    }
    else if (IS_RED(t->right) && IS_RED(t->right->left)) {
        if (IS_RED(t->left)) {
            t->colour = RED;
            t->left->colour = BLACK;
            t->right->colour = BLACK;
        } else {
            t->right = right_rotate(t->right);
            t = left_rotate(t);
            t->colour = BLACK;
            t->left->colour = RED;
        }
    }
    else if (IS_RED(t->right) && IS_RED(t->right->right)) {
        if (IS_RED(t->left)) {
            t->colour = RED;
            t->left->colour = BLACK;
            t->right->colour = BLACK;
        } else {
            t = left_rotate(t);
            t->colour = BLACK;
            t->left->colour = RED;
        }
    }
    return t;
}

/**
 * A function to do an inorder traversal of a tree 
 * @param t the tree that is being traversed inorder.
 * @param f a function which to send each key value.
 */
void tree_inorder(tree t, void f (char *str)){

    if(NULL == t){
        return;
    }
    tree_inorder(t->left, f);
    f(t->key);
    tree_inorder(t->right,f); 

}

/**
 * Frees the memory associated with the tree.
 * @param t the tree to be freed.
 * @return t the empty tree.
 */
tree tree_free(tree t){

    if(NULL == t){
        return t;
    }
    
    tree_free(t->left);
    
    tree_free(t->right);
    free(t->key);
    free(t);

    return t;

}

/** Inserts characters into tree, increasing memory where required.
 * @param t tree that the characters are being inserted into.
 * @param *str the characters to be inserted.
 * @return returns the the tree with the newly inserted nodes.
 */
tree tree_insert(tree t, char *str){
    int compare;
    
    /* for an empty tree, allocate a sufficient amount of space and return the tree */
    if(NULL == t){
        t = emalloc(sizeof *t);
        t->key = emalloc((strlen(str)+1)*sizeof *str);
        t->colour = RED;
        strcpy(t->key,str);
        t->frequency = 1;
        return t; 
    }
     compare = strcmp(t->key,str);
     if(0 == compare){
        t->frequency++;
        return t;
     }
        if (compare < 0){
            t->left = tree_insert(t->left, str);
        }else{
            t->right = tree_insert(t->right, str);
        }
        
    if(tree_type == RBT){
        t = tree_fix(t);
    }
    return t; 
}

/**
 * A function to do an preorder traversal of a tree.
 * @param t the tree that is being traversed inorder.
 * @param f a function which to send each key value.
 */
void tree_preorder(tree t, void f (char *str)){

    if(NULL == t){
        return;
    }

    f(t->key);
    tree_preorder(t->left, f);
    tree_preorder(t->right,f);
}

/** Searches tree for specific node, increasing memory where required.
 * @param t tree that is being searched.
 * @param *key the node that is being searched for.
 * @return returns 1 if node exists in tree, else returns 0.
 */
int tree_search(tree t, char *key){

    if(NULL == t){
        return 0;
    }else{
       int compare=strcmp(t->key,key);
        if(compare == 0){
            return 1;
        }else if(compare < 0){
            return tree_search(t->right,key);
        }else{
            return tree_search(t->left,key);
        }
    }
}



/**
 * Traverses the tree writing a DOT description about connections, and
 * possibly colours, to the given output stream.
 *
 * @param t the tree to output a DOT description of.
 * @param out the stream to write the DOT output to.
 */
static void tree_output_dot_aux(tree t, FILE *out) {
   if(t->key != NULL) {
      fprintf(out, "\"%s\"[label=\"{<f0>%s:%d|{<f1>|<f2>}}\"color=%s];\n",
              t->key, t->key, t->frequency,
              (RBT == tree_type && RED == t->colour) ? "red":"black");
   }
   if(t->left != NULL) {
      tree_output_dot_aux(t->left, out);
      fprintf(out, "\"%s\":f1 -> \"%s\":f0;\n", t->key, t->left->key);
   }
   if(t->right != NULL) {
      tree_output_dot_aux(t->right, out);
      fprintf(out, "\"%s\":f2 -> \"%s\":f0;\n", t->key, t->right->key);
   }
}

/**
 * Output a DOT description of this tree to the given output stream.
 * DOT is a plain text graph description language (see www.graphviz.org).
 * You can create a viewable graph with the command
 *
 *    dot -Tpdf < graphfile.dot > graphfile.pdf
 *
 * You can also use png, ps, jpg, svg... instead of pdf
 *
 * @param t the tree to output the DOT description of.
 * @param out the stream to write the DOT description to.
 */
void tree_output_dot(tree t, FILE *out) {
   fprintf(out, "digraph tree {\nnode [shape = Mrecord, penwidth = 2];\n");
   tree_output_dot_aux(t, out);
   fprintf(out, "}\n");
}
