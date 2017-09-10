/**
 * @file mylib.c
 * @author Josh Crosbie, Tyler Baker, David Fontein.
 * @date September 2016.
 * The implementation file of the specification file mylib.h.
 * The functional code to be used by both tree and htable programs.
 */

#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include "mylib.h"

/**
 * When you get memory from emalloc(), even if you forget to free it, you
 * won't leak because it will be cleaned up for you at request end.  
 * Also, in debug mode it gives you info on where things were allocated and it
 * watches for overflows. It also checks the memory limit setting.
 * @param s the size you wish to allocate.
 * @return result the result of the memory allocation.
*/

void *emalloc(size_t s){
 void *result = malloc(s);
if(result == NULL){
    fprintf(stderr,"Memory allocation failed \n");
    exit(EXIT_FAILURE);
 }
 return result; 

}

/**
 * The erealloc function takes the pointer that you wish to reallocate 
 * and a size. It returns a (possibly different) pointer whose contents up 
 * to the minimum of the old and new sizes are unchanged.
 * @param *p the pointer that you wish to reallocate.
 * @param s the size you wish to change to.
 * @return p the reallocated pointer.
 */
void *erealloc(void *p, size_t s){

    p = realloc (p, s);
    if(p == NULL){
        fprintf(stderr,"Memory relocation failed \n");
        exit(EXIT_FAILURE);
    }
    return p; 
}

/**
 * This function retrieves words from a file and trims them to return to the 
 * spell_checker function of both tree-main and htable-main.
 * @param s the char array received from the main file.
 * @param limit the maximum size that a word can be.
 * @param stream a file to print the word into.
 * @return returns the char arry.
 * */
 
 
int getword(char *s, int limit, FILE *stream) {
    int c;
    char *w = s;
    assert(limit > 0 && s != NULL && stream != NULL);
    /* skip to the start of the word */
    while (!isalnum(c = getc(stream)) && EOF != c)
        ;
    if (EOF == c) {
        return EOF;
    } else if (--limit > 0) { /* reduce limit by 1 to allow for the \0 */
        *w++ = tolower(c);
    }
    while (--limit > 0) {
        if (isalnum(c = getc(stream))) {
            *w++ = tolower(c);
        } else if ('\'' == c) {
            limit++;
        } else {
            break;
        }
    }
    *w = '\0';
    return w - s;
}
