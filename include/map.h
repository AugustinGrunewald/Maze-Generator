/**
 * @file map.h
 * 
 * @author a.grunewald
 * 
 * @brief Define necessary structures (see 1), redefinition of constants (see 2) and the declarations of basic functions (see 3).
 */


#ifndef MAP_H
#define MAP_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>


/** 1 - STRUCTURES */

// Renaming all the structures. 
typedef struct map map;
typedef struct edge edge;
typedef struct neighbors neighbors;
typedef struct node_tool node_tool;

/**
 * @brief The structure representing the map (used to generate the maze).
 * 
 */
struct map {
    /** The size of the map*/
    int height;
    int width;

    /** The pointer to a edges structure*/
    edge *p_edges;
};


/**
 * @brief The structure representing the edges starting from a node.
 * 
 */
struct edge {
    /** The int value representing the cost of the edge starting from the node and going to the node below it*/
    int down;

    /** The int value representing the cost of the edge starting from the node and going to the node at its right*/
    int right;
};


/**
 * @brief The structure representing the neighbors of a node.
 * 
 */
struct neighbors {
    /** The int value representing the number of neighbors*/
    int nb;

    /** The array of 4 int representing the number of the nodes that are neighbors (order: below, right, above, left)*/
    int nodes_numbers[4];

    /** The array of 4 int representing the cost to go to the neighbors (order: below, right, above, left)*/
    int nodes_costs[4];
};


/**
 * @brief The structure that is used by the node tool function, to allow us using a switch.
 * 
 */
struct node_tool {
    /** The int value between 0 and 2 (0 = corner, 1 = border, 2 = middle)*/
    int first_case;

    /** The int value built with int between 1 and 4 (1 = bellow, 2 = right, 3 = above, 4 = left)*/
    int second_case;
};


/** 2 - REDEFINITION OF CONSTANTS */

// Used in the find_neighbors function to improve readability. 
#define BORDER_LEFT "41"
#define BORDER_RIGHT "21"
#define BORDER_ABOVE "31"
#define BORDER_BELOW "11"

#define CORNER_UP_LEFT "340"
#define CORNER_UP_RIGHT "320"
#define CORNER_DOWN_LEFT "140"
#define CORNER_DOWN_RIGHT "120"

#define MIDDLE "2"


/** 3 - FUNCTIONS */

/**
 * @brief Print the map in the console.
 * 
 * @param current_map The pointer to the structure representing the map.
 */
void print_map(map *current_map);


/**
 * @brief Free the memory allocated to a map.
 * 
 * @param current_map The pointer to the map.
 */
void free_map(map *current_map);


/**
 * @brief Returns useful information about the position of the node in the map (in a corner, a border or in the middle, ... see redefinition of constants).
 * 
 * @param current_map The pointer to the map.
 * 
 * @param node The int of the given node.
 * 
 * @return An explicit word to know in which case we are.
*/
node_tool node_tool_function(map *current_map, int node);


/**
 * @brief Complete the neighbors structure with the data in case we're in a corner of the map.
 * 
 * @param current_map The pointer to the map.
 * 
 * @param node The int of the given node.
 * 
 * @param node_position The structure node_tool filled with the postion of the current node.
 * 
 * @return A pointer to the neighbors structure completed with the data.
 */
neighbors *corners_neighbors(map *current_map, int node, node_tool node_position);


/**
 * @brief Complete the neighbors structure with the data in case we're in a border of the map.
 * 
 * @param current_map The pointer to the map.
 * 
 * @param node The int of the given node.
 * 
 * @param node_position The structure node_tool filled with the postion of the current node.
 * 
 * @return A pointer to the neighbors structure completed with the data.
 */
neighbors *borders_neighbors(map *current_map, int node, node_tool node_position);


/**
 * @brief Complete the neighbors structure with the data in case we're in the middle of the map.
 * 
 * @param current_map The pointer to the map.
 * 
 * @param node The int of the given node.
 * 
 * @return A pointer to the neighbors structure completed with the data.
 */
neighbors *middle_neighbors(map *current_map, int node);


/**
 * @brief Find all the elements of the neighbors structure for a given node.
 * 
 * @param current_map The pointer to the map.
 * 
 * @param node The int of the given node.
 * 
 * @return A pointer to the neighbors structure completed with the data.
 */
neighbors *find_neighbors(map *current_map, int node);


/**
 * @brief Compare two structures neighbors to see if all the values are similar (not the addresses).
 * 
 * @param neighbors1 The pointer to the first neighbors.
 * 
 * @param neighbors2 The pointer to the second neighbors.
 * 
 * @return True if the value are equals, false in the other case.
 */
bool comparaison_two_neighbors(neighbors *neighbors1, neighbors *neighbors2);

#endif