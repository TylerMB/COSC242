#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_LEN 100
#define STRING_LEN 80

void *emalloc(size_t s){
    void *result = malloc(s);
    if(NULL == result){
        fprintf(stderr, "Memory failed mate\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

void print_words(char **words, int len, double average){
    if (len > 0){
        if (strlen(words[0]) > average){
            printf("%s\n", words[0]);
        }
        print_words(words +1, len -1, average);
    }
}
    
      
int main(void){
    char *words[ARRAY_LEN];
    char word[STRING_LEN];
    int count =0,i;
    double average=0.0;

    while(count < ARRAY_LEN && 1 == scanf("%79s", word)){
        words[count] = emalloc((strlen(word) +1) *sizeof word[0]);
        strcpy(words[count], word);
        average += strlen(word);
        count ++;
    }

    if(count > 0){
        average /= count;
        fprintf(stderr,"%.2f\n", average);
        print_words(words, count, average);
    }

    for(i=0; i < count; i++){
        free(words[i]);
    }


    return EXIT_SUCCESS;
} 
        
