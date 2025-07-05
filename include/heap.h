/**
 * @file heap.h
 * 
 * @author a.grunewald
 * 
 * @brief Define necessary structures (see 1), redefinition of constants (see 2) and the declarations of basic functions (see 3).
 */


#ifndef HEAP_H
#define HEAP_H

#include "maze.h"

/** 1 - STRUCTURES */

// Renaming all the structures. 
typedef struct node node;
typedef struct heap heap;
typedef struct node_set node_set;
typedef struct node_set * heap_set;


/**
 * @brief The structure representing the node of a binary heap.
 * 
 */
struct node {
    /** The ID of the node*/
    int ID;

    /** The cost of the node*/
    int cost;

    /** The pointer to the left child*/
    node *left;

    /** The pointer to the right child*/
    node *right;

    /** The pointer to the parent node*/
    node *parent;
};


/**
 * @brief The structure representing the heap.
 * 
 */
struct heap {
    /** The number of nodes*/
    int number;

    /** The pointer to the root node*/
    node *root;
};


/**
 * @brief The structure representing the node of a binary heap.
 * 
 */
struct node_set {
    /** The ID of the node*/
    int ID;

    /** The pointer to the left child*/
    node *left;

    /** The pointer to the right child*/
    node *right;
};


/** 2 - REDEFINITION OF CONSTANTS */

/** 3 - FUNCTIONS */

/**
 * @brief Find the father node of a given node (see algorithm 4.1).
 * 
 * @param current_heap The pointer to the heap.
 * 
 * @param node_number The ID of the node.
 * 
 * @return A pointer to the searched father node.
 */
node *find_father_node(heap *current_heap, int node_number);


/**
 * @brief Find the last node of the heap.
 * 
 * @param current_heap The pointer to the heap.
 * 
 * @return A pointer to the last node of the heap.
 */
node *find_last_node(heap *current_heap);

/**
 * @brief Add a new node in the heap in the right position.
 * 
 * @param current_heap The pointer to the heap.
 * 
 * @param new_node_cost The cost of the node that we're adding to the heap.
 *
 * @param new_node_ID The ID of the node that we're adding to the heap.
 *  
 * @return A pointer to the modified heap.
 */
heap *adding_new_node(heap *current_heap, int new_node_cost, int new_node_ID);

/**
 * @brief The insert function wanted for the heap.
 * 
 * @param current_heap The pointer to the heap.
 * 
 * @param new_node_cost The cost of the node that we're adding to the heap.
 * 
 * @param new_node_ID The ID of the node that we're adding to the heap.
 * 
 * @return A pointer to the final heap.
 */
heap *insert(heap *current_heap, int new_node_cost, int new_node_ID);

/**
 * @brief Extract the min value of the heap and modify it following the rules.
 * 
 * @param current_heap The pointer to the heap.
 * 
 * @return The min value of the heap.
 */
int extract_min(heap *current_heap);

#endif