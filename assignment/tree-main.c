/**
 * @file tree-main.c
 * @author Josh Crosbie, Tyler Baker, David Fontein.
 * @date september 2016.
 * this tree-main runs the tree ADT either a balanced RBT or ordinary BST. 
 * You can see the layout of either a RBT or BST by using the two 
 * output_dot graph printing functions to display a visual image.
 */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>
#include <string.h>
#include "mylib.h"
#include "tree.h"

/**
 * Prints out a help message outlining all of the options to stderr.
 * @param program the name of the program to include in the help message.
 */
static void help(char *program) {
    fprintf(stderr, "Invalid input to: %s\n\n%s", program,
        " -c filename  Check spelling of words in filename using words \n"
        "              read from stdin as the dictionary.  Print all\n"
        "              unknown words to stdout. Print timing info and\n"
        "              unknown word count to stderr. When this option \n"
        "               is given then the -p option should be ignored. \n\n"
        " -d           Prints the tree depth and nothing else\n");
    fprintf(stderr, 
        " -f filename  Write dot output to filename instead of the defult\n"
        "              file name if -o is also given \n\n"
        " -o           Output a representation of the tree in dot form to\n"
        "              the file 'tree-view.dot' using the functions given\n"
        "              in outup-dot.txt\n\n"
        " -r           Make the tree an RBT instead of the default BST\n\n"
        " -h           Print this help message\n\n");
}



/**
 * Spell check a file using a tree dictionary.
 * Prints all words not in the dictionary to stdout and statistics to stderr.
 * @param filename name of file to be spell-checked.
 * @param dictionary tree to use as a dictionary.
 * @param fill_time time taken to fill the dictionary.
 */

static void command_line_args(int argc, char **argv, char **file_name,
 tree_t *tree_type, int *print_graph, int *print_depth, int *spell_check,
 char **dot_file_name) {
    const char *optstring = "c:df:orh";
    char option;
    while ((option = getopt(argc, argv, optstring)) != EOF) {
        switch (option) {
            case 'c':
                *file_name = emalloc((strlen(optarg)+1)*sizeof (char));
                strcpy(*file_name, optarg);
                *spell_check =1;
                break;
            case 'd':
                *print_depth =1;
                break;
            case 'f':
                *dot_file_name = emalloc((strlen(optarg)+1)*sizeof (char));
                strcpy(*dot_file_name, optarg);
                break;
            case 'o':
                *print_graph =1;
                break;
            case 'r':
                *tree_type = RBT;
                break;
            case 'h':
            default:
                help(argv[0]);
                exit(EXIT_SUCCESS);
        }
    }
 }

 /**
  * A spell_checker function that prints out any words that are not also found
  * in a given file (usually dictionary.txt).
  * @param t the tree to compare against file_name.
  * @param file_name the file that will act as a dictionary.
  * @parm time the time taken to fill the tree.
  */

static void spell_checker(tree t, char *file_name, double time){
    clock_t start,stop;
    char word [250];
    int random_word_count = 0;
    FILE *f = fopen(file_name, "r");
    start = clock();
    
    while((getword(word, sizeof word, f)) != EOF) {
        if(tree_search(t, word) == 0){
            printf("%s\n", word);
            random_word_count++;
        }
    }
    
    stop = clock();
    fclose(f);
    fprintf(stderr, "Time to fill tree:   %f\n"
        "Time checking words:   %f\n",
        time, (stop - start)/(double)CLOCKS_PER_SEC);
        fprintf(stdout, "Random words:   %d\n", random_word_count);
}
    
    

/**
 * Creates a tree and fills it with string values read from STDIN.
 * Prints the tree in preorder by default, but this can be altered to
 * output a DOT representation if -o is given as a command-line
 * argument, or just ouput the depth of the tree when given -d.  For a
 * detailed description of all options see the message printed by
 * usage().  All allocated memory is freed before finishing.
 *
 * @param argc the number of command-line arguments. 
 * @param argv an array containing the command-line arguments, which
 * can be any of the options specified in usage().
 *
 * @return the exit status of program (EXIT_SUCCESS or EXIT_FAILURE).
 */
int main(int argc, char **argv) {
    
    time_t start, stop;
    int print_graph = 0, print_depth = 0, spell_check = 0;
    double time_taken;
    tree_t tree_type = BST;
    tree t;
    char word[256];
    char *dot_file_name = "tree-view.dot";
    char *file_name;
    FILE *file;
    
    command_line_args(argc, argv, &file_name, &tree_type, &print_graph,
    &print_depth, &spell_check, &dot_file_name);
    t = tree_new(tree_type);
    
    
    start = clock();
    while ((getword(word, sizeof word, stdin)) != EOF) {
        t = tree_insert(t, word);
    }
    fix_root(t);
    stop = clock();
    time_taken = (double)(stop -start)/(double)CLOCKS_PER_SEC;
    
    
    if(spell_check && (print_depth == 0)) {
        spell_checker(t,file_name,time_taken);
    }
    if(print_depth && (spell_check == 0)) {
        fprintf(stdout,"Depth: %d\n",tree_depth(t));
    }
    if(print_graph && (spell_check == 0) && (print_depth == 0)) {
        file = fopen(dot_file_name, "w");
        tree_output_dot(t, file);
        fclose(file);
    }

    t = tree_free(t);
    return EXIT_SUCCESS;
}
