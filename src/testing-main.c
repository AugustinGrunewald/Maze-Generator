/**
 * @file testing-main.c
 *
 * @author a.grunewald
 * 
 * @brief Simple program to test basic functions 
 */

#include "prim.h"
#include "loader.h"

int main() {
    // Creating a map
    map *current_map = (map *) malloc(sizeof(map));

    current_map->height = 2;
    current_map->width = 3;
    current_map->p_edges = (edge *) malloc(current_map->height * current_map->width * sizeof(edge));

    for (int i = 0; i < current_map->height * current_map->width; i++){
        current_map->p_edges[i].down = rand();
        current_map->p_edges[i].right = rand();
    }

    // Printing the map and deallocating the memory
    print_map(current_map);
    free_map(current_map);


    // Testing loader
    map *current_map_bis = map_loader("./data/map_2_3_42.txt");
    print_map(current_map_bis);
    free_map(current_map_bis);
    
    return 0;
}
