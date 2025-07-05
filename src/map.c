/**
 * @file map.c
 * 
 * @author a.grunewald
 * 
 * @brief Define basic functions.
 */


#include "map.h"

void print_map(map *current_map){
    int width = current_map->width;
    int height = current_map->height;
    
    // Printing the height and width of the map
    printf("Map size: \n - Width: %d \n - Height: %d \n \n", width, height);

    // Printing the map
    for (int i = 0; i < width*height; i++){  
        printf("%d %d \n", current_map->p_edges[i].down, current_map->p_edges[i].right);
    }

    printf("\n");
}

void free_map(map *current_map){
    free(current_map->p_edges);
    free(current_map);
}

node_tool node_tool_function(map *current_map, int node){
    int width = current_map->width;
    int height = current_map->height;

    node_tool result;

    // Corners 
    if (node == 0){
        result.first_case = 0;
        result.second_case = 340;
    } 
    else if (node == width - 1){
        result.first_case = 0;
        result.second_case = 320;
    }
    else if (node == (height-1)*width){
        result.first_case = 0;
        result.second_case = 140;    
    }
    else if (node == height*width - 1){
        result.first_case = 0;
        result.second_case = 120;
    }

    // Borders
    else if (node % width == 0){
        result.first_case = 1;
        result.second_case = 41;    
    }
    else if ((node + 1) % width == 0){
        result.first_case = 1;
        result.second_case = 21;
    }
    else if (0 < node && node < width - 1){
        result.first_case = 1;
        result.second_case = 31;
    }
    else if ((height-1)*width < node && node < height*width - 1){
        result.first_case = 1;
        result.second_case = 11;
    }

    // Middle
    else {
        result.first_case = 2;
        result.second_case = 0;
    }

    return result;
}

neighbors *corners_neighbors(map *current_map, int node, node_tool node_position){
    // Allocating memory for the neighbors structure
    neighbors *current_neighbors = (neighbors *) malloc(sizeof(neighbors));

    int width = current_map->width;
    int height = current_map->height;

    current_neighbors->nb = 2;

    // Going throw each cases 
    if (node_position.second_case == atoi(CORNER_UP_LEFT)){
        current_neighbors->nodes_costs[0] = current_map->p_edges[0].down; 
        current_neighbors->nodes_costs[1] = current_map->p_edges[0].right;
        current_neighbors->nodes_costs[2] = INT_MAX; 
        current_neighbors->nodes_costs[3] = INT_MAX;

        current_neighbors->nodes_numbers[0] = width;
        current_neighbors->nodes_numbers[1] = 1;
        current_neighbors->nodes_numbers[2] = -1;
        current_neighbors->nodes_numbers[3] = -1;
    }
    else if (node_position.second_case == atoi(CORNER_UP_RIGHT)){
        current_neighbors->nodes_costs[0] = current_map->p_edges[width - 1].down; 
        current_neighbors->nodes_costs[1] = INT_MAX;
        current_neighbors->nodes_costs[2] = INT_MAX; 
        current_neighbors->nodes_costs[3] = current_map->p_edges[width - 2].right;

        current_neighbors->nodes_numbers[0] = 2 * width - 1;
        current_neighbors->nodes_numbers[1] = -1;
        current_neighbors->nodes_numbers[2] = -1;
        current_neighbors->nodes_numbers[3] = width - 2;
    }
    else if (node_position.second_case == atoi(CORNER_DOWN_LEFT)){
        current_neighbors->nodes_costs[0] = INT_MAX; 
        current_neighbors->nodes_costs[1] = current_map->p_edges[(height - 1)*width].right;
        current_neighbors->nodes_costs[2] = current_map->p_edges[(height - 2)*width].down; 
        current_neighbors->nodes_costs[3] = INT_MAX;

        current_neighbors->nodes_numbers[0] = -1;
        current_neighbors->nodes_numbers[1] = (height - 1)*width + 1;
        current_neighbors->nodes_numbers[2] = (height - 2)*width;
        current_neighbors->nodes_numbers[3] = -1;
    }
    else if (node_position.second_case == atoi(CORNER_DOWN_RIGHT)){
        current_neighbors->nodes_costs[0] = INT_MAX; 
        current_neighbors->nodes_costs[1] = INT_MAX;
        current_neighbors->nodes_costs[2] = current_map->p_edges[(height - 1)*width - 1].down; 
        current_neighbors->nodes_costs[3] = current_map->p_edges[height*width - 2].right;

        current_neighbors->nodes_numbers[0] = -1;
        current_neighbors->nodes_numbers[1] = -1;
        current_neighbors->nodes_numbers[2] = (height - 1)*width - 1;
        current_neighbors->nodes_numbers[3] = height*width - 2;
    }

    return current_neighbors;
}

neighbors *borders_neighbors(map *current_map, int node, node_tool node_position){
    // Allocating memory for the neighbors structure
    neighbors *current_neighbors = (neighbors *) malloc(sizeof(neighbors));

    int width = current_map->width;

    current_neighbors->nb = 3;

    // Going throw each cases 
    if (node_position.second_case == atoi(BORDER_LEFT)){
        current_neighbors->nodes_costs[0] = current_map->p_edges[node].down; 
        current_neighbors->nodes_costs[1] = current_map->p_edges[node].right;
        current_neighbors->nodes_costs[2] = current_map->p_edges[node - width].down; 
        current_neighbors->nodes_costs[3] = INT_MAX;

        current_neighbors->nodes_numbers[0] = node + width;
        current_neighbors->nodes_numbers[1] = node + 1;
        current_neighbors->nodes_numbers[2] = node - width;
        current_neighbors->nodes_numbers[3] = -1;
    }
    else if (node_position.second_case == atoi(BORDER_RIGHT)){
        current_neighbors->nodes_costs[0] = current_map->p_edges[node].down; 
        current_neighbors->nodes_costs[1] = INT_MAX;
        current_neighbors->nodes_costs[2] = current_map->p_edges[node - width].down; 
        current_neighbors->nodes_costs[3] = current_map->p_edges[node - 1].right;

        current_neighbors->nodes_numbers[0] = node + width;
        current_neighbors->nodes_numbers[1] = -1;
        current_neighbors->nodes_numbers[2] = node - width;
        current_neighbors->nodes_numbers[3] = node - 1;
    }
    else if (node_position.second_case == atoi(BORDER_ABOVE)){
        current_neighbors->nodes_costs[0] = current_map->p_edges[node].down; 
        current_neighbors->nodes_costs[1] = current_map->p_edges[node].right;
        current_neighbors->nodes_costs[2] = INT_MAX; 
        current_neighbors->nodes_costs[3] = current_map->p_edges[node - 1].right;

        current_neighbors->nodes_numbers[0] = node + width;
        current_neighbors->nodes_numbers[1] = node + 1;
        current_neighbors->nodes_numbers[2] = -1;
        current_neighbors->nodes_numbers[3] = node - 1;
    }
    else if (node_position.second_case == atoi(BORDER_BELOW)){
        current_neighbors->nodes_costs[0] = INT_MAX; 
        current_neighbors->nodes_costs[1] = current_map->p_edges[node].right;
        current_neighbors->nodes_costs[2] = current_map->p_edges[node - width].down; 
        current_neighbors->nodes_costs[3] = current_map->p_edges[node - 1].right;

        current_neighbors->nodes_numbers[0] = -1;
        current_neighbors->nodes_numbers[1] = node + 1;
        current_neighbors->nodes_numbers[2] = node - width;
        current_neighbors->nodes_numbers[3] = node - 1;
    }

    return current_neighbors;
}

neighbors *middle_neighbors(map *current_map, int node){
    // Allocating memory for the neighbors structure
    neighbors *current_neighbors = (neighbors *) malloc(sizeof(neighbors));

    int width = current_map->width;

    // Filling the structure
    current_neighbors->nb = 4;

    current_neighbors->nodes_costs[0] = current_map->p_edges[node].down; 
    current_neighbors->nodes_costs[1] = current_map->p_edges[node].right;
    current_neighbors->nodes_costs[2] = current_map->p_edges[node - width].down; 
    current_neighbors->nodes_costs[3] = current_map->p_edges[node - 1].right;

    current_neighbors->nodes_numbers[0] = node + width;
    current_neighbors->nodes_numbers[1] = node + 1;
    current_neighbors->nodes_numbers[2] = node - width;
    current_neighbors->nodes_numbers[3] = node - 1;

    return current_neighbors;
}

neighbors *find_neighbors(map *current_map, int node){
    neighbors *current_neighbors = NULL;

    node_tool node_position = node_tool_function(current_map, node);

    switch (node_position.first_case){
    case 0:
        current_neighbors = corners_neighbors(current_map, node, node_position);
        break;
    
    case 1:
        current_neighbors = borders_neighbors(current_map, node, node_position);
        break;
    
    case 2:
        current_neighbors = middle_neighbors(current_map, node);
        break;
    
    default:
        break;
    }

    return current_neighbors;
}

bool comparaison_two_neighbors(neighbors *neighbors1, neighbors *neighbors2){
    bool result = true;

    // Checking the number of neighbors
    if (neighbors1->nb != neighbors2->nb){
        result = false;
        return result;
    } 
    
    // Checking the value of the cost and node number
    for (int i = 0; i < 4; i++){
        if ((neighbors1->nodes_costs[i] != neighbors2->nodes_costs[i]) || (neighbors1->nodes_numbers[i] != neighbors2->nodes_numbers[i])){
            return result;
        }
    }

    return result;
}

