/**
 * @file htable-main.c
 * @author Josh Crosbie, Tyler Baker, David Fontein.
 * @date September 2016
 * This htable-main runs the hash-table ADT. It can use
 * double hashing or linear probing to fix collisions. 
 * You can see how the htable is formed by making a new table 
 * and inserting words.
 */


#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>
#include "mylib.h"
#include "htable.h"
htable h;


    
/** Method to print out a help message that shows all of the flags that
 * can be choosen when running the program.
 * @param program the name of the program run that received a flag error.
 */
    
    static void help(char *program) {
    fprintf(stderr, "Invalid input to: %s\n\n%s", program,
            "\n -c           filename  Check the spelling of words in filename \n"
            "              using words read from stdin as the dictionary. Print \n"
            "              all unknown words to stdout. Print timing information \n"
            "              and unknown word count to stderr. When this option \n"
            "              is given then the -p option should be ignored.\n\n"
            " -d           Use double hasing as the collision resolution \n"
            "              strategy\n\n");
            
    fprintf(stderr,
            " -e           Dispay entire contents of h-table on stderr in \n"
            "              string format \n"
            "              the index, freq, stats, and key.\n\n"
            " -p           Print stats info using the funtions provided in \n"
            "              print-stats.txt instead of printing the \n"
            "              frequencies and words. \n\n");
    fprintf(stderr,        
            " -s           Snapshots to display the given numper of snaps \n"
            "              when given -p.\n\n"
            " -t           Use the first prime >=tablesize as the size of \n"
            "              your hash table. You can assume that tablesize \n"
            "              will be a number greater than 0\n\n"
            " -h           print this help message.");
}

/**
 * A method to find the next prime number given any positive input.
 * @param input an integer received from the command line
 * @return a prime number greater than or equal to the input
 */

static int next_prime(int input){
    int n;
    if(input < 2) return 2;
    for(n = 2; n < input; n++){
        if(input % n == 0){
            return next_prime(++input);
        }
    }
    return input;
} 

 
/**
 * A function that takes all command line flags and changes corresponding
 * variables accordingly.
 * @param argc the number of flags passed into the command line.
 * @param argv the char array associated with each input.
 * @param file_name the name of a file to perfom a spell check with.
 * @param hashing_type determines linear probing or double hashing for
 *        collision resolution strategy.
 * @print_table prints the contents of the hash table if activated.
 * @param print_stats prints the statistics of the hash table for a
 *        set number of snapshots.
 * @param spell_check activates the spell_checker function to compare files.
 * @param snapshot manually change the amount of statistical snapsots given
 *        through the command line.
 * @param table_size change the size of the hash table to a given value. finds
 *        the next prime number after any positive input.
 */

static void command_line_args(int argc, char **argv, char **file_name,
 int *hashing_type, int *print_table, int *print_stats, int *spell_check,
 int *snapshot, int *table_size) {
    char *optstring = "c:dept:s:h";
    char option;
    int input;
    while ((option = getopt(argc, argv, optstring)) != EOF) {
        switch (option) {
            case 'c':
                *file_name = optarg;
                *spell_check =1;
                break;
            case 'd':
                *hashing_type =1;
                break;
            case 'e':
                *print_table =1;
                break;
            case 'p':
                *print_stats =1;
                break;
            case 's':
                input = atoi(optarg);
                if(input > 0){
                    *snapshot = input;
                }
                break;
            case 't':
                input = atoi(optarg);
                *table_size = next_prime(input);
                break;
            case 'h':
                help(argv[0]);
                exit(EXIT_SUCCESS);
        }
    }
 }
 /**
  * A spell_checker function that prints out any words that are not also found
  * in a given file (usually dictionary.txt).
  * @param h the hash table to compare against file_name.
  * @param file_name the file that will act as a dictionary.
  * @parm time the time taken to fill the table.
  */

static void spell_checker(htable h, char *file_name, double time){
    clock_t start,stop;
    char word [250];
    int random_word_count = 0;
    FILE *f = fopen(file_name, "r");
    start = clock();
    
    while((getword(word, sizeof word, f)) != EOF) {
        if( 0 ==  htable_search(h, word)){
            printf("%s\n", word);
            random_word_count++;
        }
    }
    
    stop = clock();
    fclose(f);
    fprintf(stderr, "Time to fill table:   %f\n"
        "Time checking words:   %f\n",
        time, (stop - start)/(double)CLOCKS_PER_SEC);
        fprintf(stdout, "Random words:   %d\n", random_word_count);
}

/** The main function that conrols the order of htable.c.
 * @param argc takes the command line argument count.
 * @param argv arguement value, the string of flags put into the comand line.
 * @return EXIT_SUCCESS terminates the program after completing all tasks.
 * 
 */


int main(int argc, char **argv) {
    time_t start,stop;
    int table_size = 113;
    double time_taken;
    int snapshot = 10;
    char word[250];
    char *file_name;
    int hashing_type = 0, print_table = 0, print_stats = 0, spell_check = 0;
    
    
    command_line_args(argc, argv, &file_name, &hashing_type,
    &print_table, &print_stats, &spell_check, &snapshot, &table_size);
    h = htable_new(table_size, hashing_type);
 
 
    start = clock();
    while (getword(word, sizeof word, stdin) != EOF) {
        htable_insert(h, word);
    }
    stop = clock();
    time_taken = (double)(stop - start)/(double)CLOCKS_PER_SEC;
    
    
    if(spell_check) {
        spell_checker(h, file_name, time_taken);
    }
    if (print_table) {
        htable_print_entire_table(h, stderr);
    }
    if (print_stats && spell_check == 0) {
        printf("%d\n", snapshot);
        htable_print_stats(h, stdout,snapshot);
    }
    htable_print(h, stdout);

    htable_free(h);
    return EXIT_SUCCESS;
 }
