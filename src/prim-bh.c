/**
 * @file prim-bh.c
 * 
 * @author a.grunewald
 * 
 * @brief Define prim-bh functions.
 */

#include "prim-bh.h"

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

maze *prim_algorithm(map *current_map){
    // Allocating memory for the output maze & adding obvious data to the structure
    maze *output_maze = (maze*) malloc(sizeof(maze));

    int width = current_map->width;
    int height = current_map->height;
    int size = width * height;

    output_maze->width = width;
    output_maze->height = height;

    int total_cost = 0;

    
    // Creating an empty set, and an array predecessors and cheapest based on the dimensions of the map
    // Contains the vertex (cf Prim's algorithm)
    int *set = (int *) malloc(size * sizeof(int));
    // Contains the current_cost (cf Prim's algorithm)
    heap *cheapest_heap = (heap *) malloc(sizeof(heap));
    int *cheapest_memory = (int *) malloc(size * sizeof(int));
    // Contains the predecessor
    int *predecessors = (int *) malloc(size * sizeof(int));
    // An array of 0 and 1, playing the role of a memory in the while loop, in order to solve the issue presented in 4.7.3, 0 = not explored, 1 = explored
    int *memory = (int *) malloc(size *sizeof(int));


    for (int v = 0; v < size; v++){
        // Allocating memory to the cell and adding the data
        predecessors[v] = -1;
        set[v] = v;
        cheapest_memory[v] = INT_MAX;
        memory[v] = 0;
    }
    
    
    // Initializing one node (we take node 0) to a cheapest value of 0, to start the algorithm
    cheapest_heap = insert(cheapest_heap, 0, 0);
    cheapest_memory[0] = 0;

    for (int i = 1; i < size; i++){
       cheapest_heap = insert(cheapest_heap, INT_MAX, i);
       cheapest_memory[i] = INT_MAX;
    }

    // Loops to go throw all the maze
    neighbors *current_neighbors = NULL;
    int node_neighbors_number = 0;
    int current_node = 0;

    while (size != 0){
        // Extracting the min of the heap, then checking if the ID has already been checked in the past, if yes find the first cheapest value not already checked
        current_node = extract_min(cheapest_heap);

        if (memory[current_node] == 0){
            memory[current_node] = 1;
        } else {
            while (memory[current_node] == 1){
                current_node = extract_min(cheapest_heap);
            }
            memory[current_node] = 1;
        }

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
                    if (current_neighbors->nodes_costs[nb] < cheapest_memory[node_neighbors_number]){
                        cheapest_heap = insert(cheapest_heap, current_neighbors->nodes_costs[nb], node_neighbors_number);
                        cheapest_memory[node_neighbors_number] = current_neighbors->nodes_costs[nb];
                        predecessors[node_neighbors_number] = current_node;
                    }
                }
            }
        }

        free(current_neighbors);
    }

    // Adding the cost to the total cost of the MST
    for (int i = 0; i < width * height; i++){
        total_cost += cheapest_memory[i];
    }

    // Filling the maze structure with the rest 
    output_maze->cost = total_cost;
    output_maze->predecessors = predecessors;

    // Deallocating the memory that isn't useful anymore
    free(cheapest_memory);
    free(cheapest_heap);
    free(set);

    return output_maze;
}