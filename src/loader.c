/**
 * @file loader.c
 * 
 * @author a.grunewald
 * 
 * @brief Define loading functions.
 */


#include "loader.h"

map *map_loader(const char *address) {
    // Initializing of the dynamically allocated structure representing the map  
    map *loaded_map = (map *) malloc(sizeof(map));

    // Opening the file. The filename is the first argument on the command line, stored in argv[1]
    FILE *p_file = NULL;

    p_file = fopen(address, "r");

    if (p_file == NULL) {
        fprintf(stderr, "Cannot read file %s!\n", address);
        exit(EXIT_FAILURE);
    }

    // Reading the dimensions on first line and adding them in the structure
    int width = 0;
    int height = 0;
    int fscanf_result = 0;

    fscanf_result = fscanf(p_file, "%d %d\n", &width, &height);

    if (fscanf_result != 2) {
        fprintf(stderr, "First line is not syntactically correct!\n");
        exit(EXIT_FAILURE);
    }

    loaded_map->height = height;
    loaded_map->width = width;
    

    // Allocating memory to the edges
    loaded_map->p_edges = (edge *) malloc(height * width * sizeof(edge));

    int down = 0;
    int right = 0;

    for (int i = 0; i < height * width; i++){
        fscanf_result = 0;

        fscanf_result = fscanf(p_file, "%d %d\n", &down, &right);

        if (fscanf_result != 2) {
            fprintf(stderr, "Line %d is not syntactically correct!\n", i);
            exit(EXIT_FAILURE);
        }

        loaded_map->p_edges[i].down = down;
        loaded_map->p_edges[i].right = right;
    }

    fclose(p_file);

    return loaded_map;
}