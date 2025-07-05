/**
 * @file test-find-neighbors.c
 *
 * @author a.grunewald
 * 
 * @brief Simple program to test the find neighbors functions
 */

#include <assert.h>
#include "map.h"
#include "loader.h"

int main(void){
    printf("* Starting find-neighbors tests...\n\n");

    // Loading the map
    map *current_map = map_loader("./data/map_10_8_tests.txt"); 

    int node_index [9] = {0, 5, 9, 20, 42, 59, 70, 74, 79};

    // Creating the neighbors structures related to the neighbors in the txt document
    neighbors **nodes = (neighbors**) malloc(9 * sizeof(neighbors *));
    for (int i = 0; i < 9; i++){
        nodes[i] = (neighbors*) malloc(sizeof(neighbors));
    }

    nodes[0]->nb = 2;
    nodes[1]->nb = 3;
    nodes[2]->nb = 2;
    nodes[3]->nb = 3;
    nodes[4]->nb = 4;
    nodes[5]->nb = 3;
    nodes[6]->nb = 2;
    nodes[7]->nb = 3;
    nodes[8]->nb = 2;

    // Nodes numbers
    nodes[0]->nodes_numbers[0] = 10;
    nodes[0]->nodes_numbers[1] = 1;
    nodes[0]->nodes_numbers[2] = -1;
    nodes[0]->nodes_numbers[3] = -1;

    nodes[1]->nodes_numbers[0] = 15;
    nodes[1]->nodes_numbers[1] = 6;
    nodes[1]->nodes_numbers[2] = -1;
    nodes[1]->nodes_numbers[3] = 4;

    nodes[2]->nodes_numbers[0] = 19;
    nodes[2]->nodes_numbers[1] = -1;
    nodes[2]->nodes_numbers[2] = -1;
    nodes[2]->nodes_numbers[3] = 8;

    nodes[3]->nodes_numbers[0] = 30;
    nodes[3]->nodes_numbers[1] = 21;
    nodes[3]->nodes_numbers[2] = 10;
    nodes[3]->nodes_numbers[3] = -1;

    nodes[4]->nodes_numbers[0] = 52;
    nodes[4]->nodes_numbers[1] = 43;
    nodes[4]->nodes_numbers[2] = 32;
    nodes[4]->nodes_numbers[3] = 41;

    nodes[5]->nodes_numbers[0] = 69;
    nodes[5]->nodes_numbers[1] = -1;
    nodes[5]->nodes_numbers[2] = 49;
    nodes[5]->nodes_numbers[3] = 58;

    nodes[6]->nodes_numbers[0] = -1;
    nodes[6]->nodes_numbers[1] = 71;
    nodes[6]->nodes_numbers[2] = 60;
    nodes[6]->nodes_numbers[3] = -1;

    nodes[7]->nodes_numbers[0] = -1;
    nodes[7]->nodes_numbers[1] = 75;
    nodes[7]->nodes_numbers[2] = 64;
    nodes[7]->nodes_numbers[3] = 73;

    nodes[8]->nodes_numbers[0] = -1;
    nodes[8]->nodes_numbers[1] = -1;
    nodes[8]->nodes_numbers[2] = 69;
    nodes[8]->nodes_numbers[3] = 78;

    // Nodes costs
    nodes[0]->nodes_costs[0] = 1;
    nodes[0]->nodes_costs[1] = 0;
    nodes[0]->nodes_costs[2] = INT_MAX;
    nodes[0]->nodes_costs[3] = INT_MAX;

    nodes[1]->nodes_costs[0] = 11;
    nodes[1]->nodes_costs[1] = 10;
    nodes[1]->nodes_costs[2] = INT_MAX;
    nodes[1]->nodes_costs[3] = 8;

    nodes[2]->nodes_costs[0] = 19;
    nodes[2]->nodes_costs[1] = INT_MAX;
    nodes[2]->nodes_costs[2] = INT_MAX;
    nodes[2]->nodes_costs[3] = 16;

    nodes[3]->nodes_costs[0] = 41;
    nodes[3]->nodes_costs[1] = 40;
    nodes[3]->nodes_costs[2] = 21;
    nodes[3]->nodes_costs[3] = INT_MAX;

    nodes[4]->nodes_costs[0] = 85;
    nodes[4]->nodes_costs[1] = 84;
    nodes[4]->nodes_costs[2] = 65;
    nodes[4]->nodes_costs[3] = 82;

    nodes[5]->nodes_costs[0] = 119;
    nodes[5]->nodes_costs[1] = INT_MAX;
    nodes[5]->nodes_costs[2] = 99;
    nodes[5]->nodes_costs[3] = 116;

    nodes[6]->nodes_costs[0] = INT_MAX;
    nodes[6]->nodes_costs[1] = 140;
    nodes[6]->nodes_costs[2] = 121;
    nodes[6]->nodes_costs[3] = INT_MAX;

    nodes[7]->nodes_costs[0] = INT_MAX;
    nodes[7]->nodes_costs[1] = 148;
    nodes[7]->nodes_costs[2] = 129;
    nodes[7]->nodes_costs[3] = 146;

    nodes[8]->nodes_costs[0] = INT_MAX;
    nodes[8]->nodes_costs[1] = INT_MAX;
    nodes[8]->nodes_costs[2] = 139;
    nodes[8]->nodes_costs[3] = 156;

    for (int i = 0; i < 9; i++){
        printf("  | Testing with node %d ...  \n", node_index[i]);
        neighbors *current_neighbors = find_neighbors(current_map, node_index[i]);
        assert(comparaison_two_neighbors(nodes[i], current_neighbors) == true);
        printf("  | Success\n\n");
        free(current_neighbors);
        free(nodes[i]);
    }

    printf("  | OK!\n");
    printf("\n");

    free(nodes);
    free_map(current_map);

    return 0;
}