/**
 * @file test-heap-correctness.c
 * 
 * @author a.grunewald
 * 
 * @brief Define the heap tests functions.
 */

#include "heap.h"
#include <assert.h>

int main(void){
    printf("* Starting heap correctness tests...\n\n");

    // Inserting 50 nodes with costs from 1 to 50
    heap *current_heap = (heap *) malloc(sizeof(heap));

    for (int i = 0; i < 50; i++){
        printf("  | Inserting a node of ID and cost %d ...  \n", i+1);
        current_heap = insert(current_heap, i+1, i+1);
    }

    // Extracting 50 times and printing in the console the values obtained
    for (int i = 0; i < 50; i++){
        printf("  | Extracting the min node ...  \n");

        int min_value = extract_min(current_heap);
        printf("  | Value returned: %d ...  \n", min_value);

        assert(i+1 == min_value);
    }
    
    free(current_heap);

    return 0;
}