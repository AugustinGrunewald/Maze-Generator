/**
 * @file maze.h
 * 
 * @author a.grunewald
 * 
 * @brief Define necessary structures (see 1), redefinition of constants (see 2) and the declarations of basic functions (see 3).
 */


#ifndef MAZE_H
#define MAZE_H

#include "map.h"

/** 1 - STRUCTURES */

// Renaming all the structures. 
typedef struct maze maze;

/**
 * @brief The structure representing the maze.
 * 
 */
struct maze {
    /** The size of the map*/
    int height;
    int width;

    /** The array predecessors of int values such that predecessors[i] is the number 
     * of the node that is the predecessor of node i in the minimum spanning tree*/
    int *predecessors;

    /** The sum of all edges in the corresponding minimum spanning tree*/
    int cost;
};


/** 2 - REDEFINITION OF CONSTANTS */

// Used in the find_neighbors function to improve readability. 
#define WALL '#'
#define SPACE ' '


/** 3 - FUNCTIONS */

/**
 * @brief Build a character string representing the maze. 
 * 
 * @param current_maze The pointer to the structure representing the maze.
 * 
 * @return A character string with walls and spaces.
*/
char *building_matrix(maze *current_maze);


/**
 * @brief Print the maze in the console.
 * 
 * @param current_maze The pointer to the structure representing the maze.
 */
void print_maze(maze *current_maze);


/**
 * @brief Generate a PPM file of the maze.
 * 
 * @param current_maze The pointer to the structure representing the maze.
 * 
 * @param address The address of the file .pbm that is created : must contain the path and the extension, example : ./data/name_file.pbm
 */
void generate_image(maze *current_maze, const char *address);


/**
 * @brief Compare two structures maze to see if all the values are similar (not the addresses).
 * 
 * @param maze1 The first maze.
 * 
 * @param maze2 The second maze.
 * 
 * @return True if the value are equals, false in the other case.
 */
bool comparaison_two_maze(maze maze1, maze maze2);


#endif