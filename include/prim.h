/**
 * @file prim.h
 * 
 * @author a.grunewald
 * 
 * @brief Define necessary structures (see 1), redefinition of constants (see 2) and the declarations of basic functions (see 3).
 */


#ifndef PRIM_H
#define PRIM_H

#include "maze.h"

/** 1 - STRUCTURES */

/** 2 - REDEFINITION OF CONSTANTS */

/** 3 - FUNCTIONS */

/**
 * @brief Removes an int from a set.
 * 
 * @param set A set of int.
 * 
 * @param node_to_remove The int value of the node to remove.
 * 
 * @param size The int giving the current size of the set.
 * 
 * @return A new set without the node that has been removed.
*/
int *remove_from_set(int *set, int node_to_remove, int size);


/**
 * @brief Search in the set if a certain value is present.
 * 
 * @param set A set of int.
 * 
 * @param node The int of the given node to search.
 * 
 * @param size The int giving the current size of the set.
 * 
 * @return A boolean true or false.
*/
bool is_in_the_set(int *set, int node, int size);


/**
 * @brief Search cheapest value of the set (based on the array cheapest).
 * 
 * @param set A set of int.
 * 
 * @param cheapest The array cheapest defined in the algorithm.
 * 
 * @param size The int giving the current size of the set.
 * 
 * @return The node index of the cheapest.
*/
int min_set(int *set, int *cheapest, int size);


/**
 * @brief Implementation of the prim's algorithm.
 * 
 * @param current_map The map that's used to generate the maze.
 * 
 * @return The maze that has been builded.
*/
maze *prim_algorithm(map *current_map);


#endif