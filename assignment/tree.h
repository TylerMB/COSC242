/**
 * @file tree.h
 * @author Josh Crosbie, Tyler Baker, David Fontein.
 * @date September 2016
 * This contains the headers for the tree program. All functions called by
 * tree-main.c are declared extern in here. Also defines enumerated types and 
 * the struct of tree.
 */

#ifndef TREE_H_
#define TREE_H_

#include <stdio.h> 

typedef struct tree_node *tree;
typedef enum tree_e {BST,RBT} tree_t;
typedef enum colour_e {RED,BLACK} colour_t;

extern tree tree_new(tree_t tree_choice);
extern tree tree_insert(tree t,char *str);
extern int tree_search(tree t,char *key);
extern void tree_inorder(tree t,void f(char *str));
extern void tree_preorder(tree t,void f(char *str));
extern int tree_depth(tree t);
extern void tree_output_dot(tree t, FILE *out);
extern tree tree_free(tree t);
extern tree fix_root(tree t);

#endif