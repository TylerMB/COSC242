/**
 * @file htable.h
 * @author Josh Crosbie, Tyler Baker, David Fontein.
 * @date September 2016
 * This contains the headers for the htable program. All functions called by
 * htable-main.c are declared extern in here. Also defines enumerated types and 
 * the struct of htable.
 * */

#ifndef HTABLE_H_
#define HTABLE_H_

#include <stdio.h>

typedef struct htablerec *htable;

typedef enum hashing_e { LINEAR_P, DOUBLE_H } hashing_t;
extern void htable_free(htable h);
extern int htable_insert(htable h, char *str);
extern htable htable_new(int capacity, hashing_t method);
extern void htable_print(htable h, FILE *stream);
extern int htable_search(htable h, char *str);
extern void htable_print_entire_table(htable h, FILE *stream);
extern unsigned int htable_step(htable h, unsigned int i_key);
extern void htable_print_stats(htable h, FILE *stream, int num_stats);

#endif
