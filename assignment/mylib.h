/**
 * @file mylib.h
 * @author Josh Crosbie, Tyler Baker, David Fontein.
 * @date September 2016
 * This contains the headers for the mylib program. All functions in mylib.c
 * are declared extern in here.
 * */

#ifndef MYLIB_H_
#define MYLIB_H_

#include <stddef.h>

extern void *emalloc(size_t);
extern void *erealloc(void *, size_t);
extern int getword(char *,int, FILE*);

#endif
