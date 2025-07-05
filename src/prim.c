/**
 * @file prim.c
 * 
 * @author a.grunewald
 * 
 * @brief Define prim functions.
 */

#include "prim.h"

int *remove_from_set(int *set, int node_to_remove, int size){
    // Contains the new vertex (cf Prim's algorithm)
    int *new_set = (int*) malloc((size - 1) * sizeof(int));

    int index = 0;
    while (set[index] != node_to_remove){
        index += 1;
        if (index == size){
            fprintf(stderr, "Cannot find the node to remove !\n");
            exit(EXIT_FAILURE);
        }
    }

    // Filling the new set
    for (int v = 0; v < index; v++){
        new_set[v] = set[v];
    }
    for (int v = index + 1; v < size; v++){
        new_set[v - 1] = set[v];  
    }

    // Deallocating memory
    free(set);
    return new_set;
}

bool is_in_the_set(int *set, int node, int size){
    for (int i = 0; i < size; i++){
        if (set[i] == node){
            return true;
        }
    }
    return false;
}

int min_set(int *set, int *cheapest, int size){
    int min_set = set[0];
    int min_value = cheapest[set[0]];

    for (int i = 0; i < size; i++){
        if (cheapest[set[i]] < min_value){
            min_value = cheapest[set[i]];
            min_set = set[i];
        }
    }
    return min_set;
}

maze *prim_algorithm(map *current_map){
    // Allocating memory for the output maze & adding obvious data to the structure
    maze *output_maze = (maze*) malloc(sizeof(maze));

    int width = current_map->width;
    int height = current_map->height;

    output_maze->width = width;
    output_maze->height = height;

    int total_cost = 0;

    
    // Creating an empty set, and an array predecessors and cheapest based on the dimensions of the map
    // Contains the vertex (cf Prim's algorithm)
    int *set = (int*) malloc(width * height * sizeof(int));
    // Contains the current_cost (cf Prim's algorithm)
    int *cheapest = (int*) malloc(width * height * sizeof(int));
    // Contains the predecessor
    int *predecessors = (int*) malloc(width * height * sizeof(int));

    for (int v = 0; v < width * height; v++){
        // Allocating memory to the cell and adding the data
        cheapest[v] = INT_MAX;
        predecessors[v] = -1;
        set[v] = v;
    }
    
    
    // Initializing one node (we take node 0) to a cheapest value of 0, to start the algorithm
    cheapest[0] = 0;

    // Loops to go throw all the maze
    neighbors *current_neighbors = NULL;
    int node_neighbors_number = 0;
    int current_node = 0;
    int size = width * height;

    while (size != 0){
        current_node = min_set(set, cheapest, size);
        set = remove_from_set(set, current_node, size);
        size -= 1;


        // Getting the neighbors (number of neighbors and node numbers)
        current_neighbors = find_neighbors(current_map, current_node);

        for (int nb = 0; nb < 4; nb++){
            // Adding an IF test, to avoid the INT_MAX case (see map.c, find_neighbors function)
            if (current_neighbors->nodes_numbers[nb] != -1){
                // We go back to the algorithm and follow it
                node_neighbors_number = current_neighbors->nodes_numbers[nb];

                if (is_in_the_set(set, node_neighbors_number, size) == true){
                    if (current_neighbors->nodes_costs[nb] < cheapest[node_neighbors_number]){
                        cheapest[node_neighbors_number] = current_neighbors->nodes_costs[nb];
                        predecessors[node_neighbors_number] = current_node;
                    }
                }
            }
        }

        free(current_neighbors);
    }

    // Adding the cost to the total cost of the MST
    for (int i = 0; i < width * height; i++){
        total_cost += cheapest[i];
    }

    // Filling the maze structure with the rest 
    output_maze->cost = total_cost;
    output_maze->predecessors = predecessors;

    // Deallocating the memory that isn't useful anymore
    free(cheapest);
    free(set);

    return output_maze;
}