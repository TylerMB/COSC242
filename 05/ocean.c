#include <stdio.h>
#include <stdlib.h>
#define OCEAN_MAX 41981

    struct ocean_datum {
        int x; /* grid-reference east-west */
        int y; /* grid-reference north-south */
        double conc; /* concentration of O_2 in mL/L found at grid-ref (x,y) */
    };
void print_ocean_datum(struct ocean_datum *o) {
    printf("%d %d %.4f\n", o->x, o->y, o->conc);
}
int read_ocean_datum(struct ocean_datum *o) {
    return 3 == scanf("%d %d %lg", &o->x, &o->y, &o->conc);
}
int main(void) {
    struct ocean_datum ocean_data[OCEAN_MAX];
    int num_items;
    int i;
    num_items = 0;
    while (num_items < OCEAN_MAX && read_ocean_datum(&ocean_data[num_items])) {
        num_items++;
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
    for (i = 0; i < num_items; i++) {
        print_ocean_datum(&ocean_data[i]);
    }
    return EXIT_SUCCESS;
}
