/**
 * @file test-heap-complexity.c
 * 
 * @author a.grunewald
 * 
 * @brief Define the heap tests complexity functions.
 */

#include "heap.h"
#include <assert.h>

int main(void){
    printf("* Starting heap complexity tests...\n\n");
    printf("  | Writing the csv file with data ...  \n");

    // Creating the csv file
    FILE *p_file = NULL;
    char *saving_path = "./data/data_complexity_heap.csv";

    p_file = fopen(saving_path, "w");
    if (p_file == NULL) {
        fprintf(stderr, "Cannot write to file data_complexity_heap.csv!\n");
        exit(EXIT_FAILURE);
    }

    // Writing the headers
    fprintf(p_file, "nb,time_to_insert,time_to_extract\n");

    heap *current_heap = (heap *) malloc(sizeof(heap));
    clock_t start;
    clock_t end;
    int nb = 0;
    srand(time(NULL));
    int random_number = 0;

    for (int j = 2; j < 23; j++){
        nb = (int) pow(2,j);
        
        // Printing in the console
        printf("  | Working with %d iterations ...  \n", nb);
    
        // Inserting
        start = clock();
        for (int i = 0; i < nb; i++) {
            random_number =  (int) (rand() % INT_MAX);
            current_heap = insert(current_heap, random_number, random_number);
        }
        end = clock();
        double time_to_insert = (double) (end - start) / CLOCKS_PER_SEC;

        // Extracting
        start = clock();
        for (int i = 0; i < nb; i++) {
            extract_min(current_heap);
        }
        end = clock();
        double time_to_extract = (double) (end - start) / CLOCKS_PER_SEC;
        
        // Writing in the csv file
        fprintf(p_file, "%d,%f,%f\n", nb, time_to_insert, time_to_extract);
    }

    fclose(p_file);
    free(current_heap);

    return 0;
}