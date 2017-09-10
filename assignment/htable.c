/**
 * @file htable.c
 * @author Josh Crosbie, Tyler Baker, David Fontein.
 * @date September 2016
 * This htable contains the functional code of the hash-table ADT. It can use
 * double hashing or linear probing to fix collisions. 
 * You can see how the htable is formed by making a new table 
 * and inserting words.
 * */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "htable.h"
#include "mylib.h" 

/**A struct that holds the capacity of the htable, the number of frequency of 
 * collisions that occur. It also shows the number of keys and the capacity in
 * the htable.
 **/

struct htablerec{
    char **keys;
    int *frequencies;
    int num_keys;
    int capacity;
    int *stats;
    hashing_t method;
    

};

/**
 * hatable_new makes the hashtable and allocates the memory. Either linear 
 * probing or double hashing can be used.
 * @param capacity the size that the hashtable should be.
 * @param method the collision resolution stratagey.
 * @return the newly created hashtable.
 */

htable htable_new(int capacity,hashing_t method){
    int i; 

    htable table = emalloc (sizeof *table);
    table -> capacity = capacity;
    table -> num_keys =0;
    table -> frequencies = emalloc(capacity *sizeof (int));
    table -> keys = emalloc(capacity *sizeof (char*) );
    table -> stats = emalloc(capacity *sizeof (int));
    table -> method = method;

    for(i=0; i < capacity; i++){
        table -> keys[i] = NULL;
        table -> frequencies[i]=0;
        table -> stats[i]=0;
    }
    
    return table; 
    
}

/**
 * This method deallocates all of the unused memory associated with the
 * hashtable.
 * @param h the hash table to free unsed memory from.
 */

void htable_free(htable h){
    int i;
    for(i=0; i < h-> capacity ; i++){
        if(h->keys[i] != NULL){
            free(h->keys[i]);
        }
    
    }
    free(h->keys);
    free(h->stats);
    free(h->frequencies);
    free(h);
    
}


/**
 * This method assigns a value to a word and this is used to decide the location
 * of the hashtable that it is inserted into.
 * @param word the character array to determine a value for.
 * @return result the associated value for the given word.
 */
 
static unsigned int htable_word_to_int(char *word){

    unsigned int result = 0;

    while (*word != '\0'){
        result = (*word++ + 31 * result);
    }
    return result;
}

/**
 * This method is used to fill the hash table with each given word. If the hash
 * table is already full, it will return false.
 * @param h the hash table to insert a value into.
 * @param str the character array to put into the hashtable.
 * @return the outcome of it method 1 = sucessful entry.
 */
  
int htable_insert(htable h, char *str){
    hashing_t method = h->method;
    int i = htable_word_to_int(str) %h->capacity;
    int setpsize= htable_step(h,i);
    int collision =0;
    
    
    if(h->num_keys == h->capacity){
        return 0;
    }
    while(collision < h->capacity){
        if(h-> keys[i] == NULL){
            h->keys[i] = emalloc ((strlen(str)+1) * sizeof *str ); 
            strcpy(h->keys[i],str);
            h->frequencies[i] =1;
            h->num_keys++;
            h->stats[i] = collision;
            return 1; 
        }

        if(0 == strcmp(h->keys[i],str)){
            h-> frequencies[i]++;
            return h->frequencies[i];
        }
        
        if(method == DOUBLE_H){
            i+=setpsize;
            i = i%h->capacity;
        } else if(method == LINEAR_P){
            i++;
            i = i%h->capacity;
        }
        collision++;
        
    }
    return 0;
}

/**
 * This method is used to determine the next hashtable cell to check based on 
 * a collision resolustion strategy.
 * @param h the hash table to insert a value into.
 * @param i_key the value of the word trying to be inserted.
 * @return the new cell in which to insert the value.
 */

unsigned int htable_step(htable h, unsigned int i_key) {
    return 1 + (i_key % (h->capacity - 1));
}

/**
 * This method is used to determine if a value is located in the hash table.
 * @param h the hash table to check for a value in.
 * @param str the word trying to be searched for.
 * @return the frequency of the word being searched for. 0 = not in the table.
 */


int htable_search(htable h ,char *str){

    int collisions=0;
    int i =htable_word_to_int(str) %h->capacity;

    while(h->keys[i] !=NULL && collisions < h->capacity){
        if(strcmp(h->keys[i],str) ==0){
            return h->frequencies[i];
        }
        collisions++;
        i++;
    }
    return 0;
}

/**
 * Prints out a line of data from the hash table to reflect the state
 * the table was in when it was a certain percentage full.
 * Note: If the hashtable is less full than percent_full then no data
 * will be printed.
 *
 * @param h - the hash table.
 * @param stream - a stream to print the data to.
 * @param percent_full - the point at which to show the data from.
 */

static void print_stats_line(htable h, FILE *stream, int percent_full) {
   int current_entries = h->capacity * percent_full / 100;
   double average_collisions = 0.0;
   int at_home = 0;
   int max_collisions = 0;
   int i = 0;

   if (current_entries > 0 && current_entries <= h->num_keys) {
      for (i = 0; i < current_entries; i++) {
         if (h->stats[i] == 0) {
            at_home++;
         } 
         if (h->stats[i] > max_collisions) {
            max_collisions = h->stats[i];
         }
         average_collisions += h->stats[i];
      }
    
      fprintf(stream, "%4d %10d %10.1f %10.2f %11d\n", percent_full, 
              current_entries, at_home * 100.0 / current_entries,
              average_collisions / current_entries, max_collisions);
   }
}

/**
 * Print the hash table out to a file stream.
 * @param h The hash table to print out.
 * @param stream file-stream to print to.
 */
void htable_print(htable h,FILE *stream){
  int i;
  for(i=0;i<h->capacity;i++){
    if(h->keys[i] != NULL){
      fprintf(stream,"%d\t%s\n",h->frequencies[i],h->keys[i]);
    }
  }
}

/**
 * Prints out a table showing what the following attributes were like
 * at regular intervals (as determined by num_stats) while the
 * hashtable was being built.
 *
 * @li Percent At Home - how many keys were placed without a collision
 * occurring.
 * @li Average Collisions - how many collisions have occurred on
 *  average while placing all of the keys so far.
 * @li Maximum Collisions - the most collisions that have occurred
 * while placing a key.
 *
 * @param h the hashtable to print statistics summary from.
 * @param stream the stream to send output to.
 * @param num_stats the maximum number of statistical snapshots to print.
 */

void htable_print_stats(htable h, FILE *stream, int num_stats) {
   int i;

   fprintf(stream, "\n%s\n\n", 
           h->method == LINEAR_P ? "Linear Probing" : "Double Hashing"); 
   fprintf(stream, "Percent   Current   Percent    Average      Maximum\n");
   fprintf(stream, " Full     Entries   At Home   Collisions   Collisions\n");
   fprintf(stream, "-----------------------------------------------------\n");
   for (i = 1; i <= num_stats; i++) {
      print_stats_line(h, stream, 100 * i / num_stats);
   }
   fprintf(stream, "-----------------------------------------------------\n\n");
}

/**
 * Prints out the entire contents of the hashtable, including empty cells.
 * This function will only print key values if they are not empty.
 *
 * @param h the hash table to print.
 * @param stream the destination to print the data to.
 */

void htable_print_entire_table(htable h, FILE *stream){
    int v;
    fprintf(stream, "Position\tFrequency\tStats\tWord\n");
    fprintf(stream,"----------------------------------------\n");
    for (v=0;v<h->capacity;v++){
        fprintf(stream,"%5d %5d  %5d   %s\n",v, h->frequencies[v],
                h->stats[v], (h->keys[v] == NULL) ? "": h->keys[v]);
    }
    for (v=0;v<h->capacity;v++){
        if(h->keys[v] != NULL){
            fprintf(stream, "%d\t%s\n", h->frequencies[v], h->keys[v]);
        }
    }
    
}
