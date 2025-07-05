/**
 * @file maze.c
 * 
 * @author a.grunewald
 * 
 * @brief Define maze functions.
 */

#include "maze.h"


char *building_matrix(maze *current_maze){
    int width_map = current_maze->width;
    int height_map = current_maze->height;

    int width_maze = 2*width_map + 1;
    int height_maze = 2*height_map + 1;

    // Allocating memory 
    char *matrix = (char*) malloc(width_maze * height_maze * sizeof(char));

    // Filling all the matrix with walls
    for (int i = 0; i < width_maze * height_maze; i++){
        matrix[i] = WALL;
    }

    // Updating the matrix to put all the nodes and in between nodes in SPACE character
    for (int i = 0; i < width_map * height_map; i++){
        int index_node = width_maze * (1 + 2*(i/width_map)) + 2*(i%width_map) + 1;
        int index_in_between = index_node;

        // Finding if the predecessor is below, right, above or left, and saving the coordinate of the space in between
        if (current_maze->predecessors[i] == i + width_map){
            index_in_between += width_maze;
        }
        else if (current_maze->predecessors[i] == i + 1){
            index_in_between += 1;
        }
        else if (current_maze->predecessors[i] == i - width_map){
            index_in_between -= width_maze;
        }
        else if (current_maze->predecessors[i] == i - 1){
            index_in_between -= 1;
        }

        // Updating into a SPACE, the node and the character in between the node and the predecessor, in case the predecessor is -1 we don't fill the space in between
        if (current_maze->predecessors[i] != -1){
            matrix[index_in_between] = SPACE;
        }
        matrix[index_node] = SPACE;
    }

    return matrix;
}

void print_maze(maze *current_maze){
    int width_map = current_maze->width;
    int height_map = current_maze->height;

    int width_maze = 2*width_map + 1;
    int height_maze = 2*height_map + 1;

    char *matrix = building_matrix(current_maze);

    // Printing the maze: going throw each lines
    for (int i = 0; i < height_maze; i++){
        for (int j = 0; j < width_maze; j++){
            printf("%c", matrix[i*width_maze + j]);
        }
        printf("\n");
    }

    free (matrix);
}


void generate_image(maze *current_maze, const char *address){
    // Initializing all the useful data
    FILE *p_file = NULL;
    int width = current_maze->width;
    int height = current_maze->height;

    int width_maze = 2*width + 1;
    int height_maze = 2*height + 1;

    int wall = 1;
    int space = 0;

    char *matrix = building_matrix(current_maze); 

    // The address must contain the path : ./data/name.ppm 
    p_file = fopen(address, "w");

    if (p_file == NULL) {
        fprintf(stderr, "Cannot write to file %s !\n", address);
        exit(EXIT_FAILURE);
    }

    // Writing the maze in the file
    fprintf(p_file, "P1\n");
    fprintf(p_file, "%d %d\n", width_maze, height_maze);

    // Going throw each lines
    for (int i = 0; i < height_maze; i++){
        for (int j = 0; j < width_maze; j++){
            if (matrix[i*width_maze + j] == WALL){
                fprintf(p_file, "%d", wall);
            } else {
                fprintf(p_file, "%d", space);
            }

            // Adding space between the numbers
            if (j != width_maze - 1){
                fprintf(p_file, " ");
            }
        }
        fprintf(p_file, "\n");
    }

    fclose(p_file);

    free(matrix);  
}


bool comparaison_two_maze(maze maze1, maze maze2){
    bool result = true;

    // Checking the dimensions and the cost 
    if (maze1.cost != maze2.cost){
        result = false;
        return result;
    } else if (maze1.height != maze2.height){
        result = false;
        return result;        
    } else if (maze1.width != maze2.width){
        result = false;
        return result;        
    }
    
    int length = maze1.height * maze1.width;

    // Checking the value of the predecessors array
    for (int i = 0; i < length; i++){
        if (maze1.predecessors[i] != maze2.predecessors[i]){
            return result;
        }
    }

    return result;
}