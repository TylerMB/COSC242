#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_LEN 80
#define ARRAY_LEN 10000

void(*emalloc(size_t s)){
        void *result = malloc(s);
        if (NULL == result){
            fprintf(stderr, "Memory allocation failed \n");
            exit (EXIT_FAILURE);
        }
        return result;
    }

    void insertion_sort(char *a[], int n){
        char *key;
        int i,current;

        for(i=1 ; i < n ; i ++){
            key = a[i];
            for(current = i; current > 0 && strcmp(key ,a[current-1]) < 0; current--){
                a[current] = a[current - 1];
            }
            a[current] = key;
            printf(": %s\n", key);
        }


    }

    int main (void) {
        char word[STRING_LEN];
        char *wordlist[ARRAY_LEN];
        int i,num_words;

        num_words =0;
            
        while (num_words < ARRAY_LEN && 1 == scanf("%79s",word)){
            wordlist[num_words] = emalloc((strlen(word) + 1) * sizeof wordlist[0][0]);
            strcpy(wordlist[num_words], word);
            
            num_words ++;
        }

        insertion_sort(wordlist, num_words);

        for ( i = 0; i < num_words; i ++ ){
            printf ("%s\n", wordlist[i]);
        }

        for (i =0; i < num_words; i++){
        free(wordlist[i]);
        }
        return EXIT_SUCCESS;
    }
