/**
 * @file test-loader.c
 *
 * @author a.grunewald
 * 
 * @brief Simple program to test the loader
 */

#include "map.h"
#include "loader.h"

int main(int argc, char *argv[]){
    printf("* Starting loader tests...\n\n");

    for (int i = 1; i < argc; i++){
        const char * address = argv[i];

        printf("  | Testing the loader with %s ...  \n\n", address);
        map *current_map = map_loader(address);
        print_map(current_map);
        free_map(current_map);
    }

    printf("  | OK!\n");
    printf("\n");

    return 0;
}