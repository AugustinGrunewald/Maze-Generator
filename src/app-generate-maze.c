/**
 * @file app-generate-maze.c
 * 
 * @author a.grunewald
 * 
 * @brief Generate maze with an argument in the command line.
 */

#include "prim.h"
#include "loader.h"

int main(int argc, char *argv[]) {
    // testing if a filename has been given
    if (argc != 2) {
        fprintf(stderr, "You must provide a file name!\n");
        exit(EXIT_FAILURE);
    }

    // Loading the map
    map *current_map = map_loader(argv[1]);

    // Creating the saving path by changing the .txt extension
    char *saving_address = argv[1];
    char *new_extension = "pbm";
    int length = strlen(argv[1]);

    strcpy(saving_address + (length - 3), new_extension);

    // Creating the maze and generating the .pbm file
    maze *current_maze = prim_algorithm(current_map);
    generate_image(current_maze, saving_address);
}
