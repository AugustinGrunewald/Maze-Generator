/**
 * @file test-prim.c
 *
 * @author a.grunewald
 * 
 * @brief Simple program to test the prim functions
 */

#include <assert.h>
#include "prim.h"
#include "loader.h"

int main(void){
    printf("* Starting prim tests...\n\n");

    // Loading the mazes
    // MAZE 42
    maze maze_42 = {
        .width = 10,
        .height = 8,
        .predecessors = NULL,
        .cost = -762,
    };

    int maze_array_42[] = { -1,
        0, 1, 2, 3, 4, 16, 17, 18, 8, 0,
        1, 11, 12, 13, 14, 15, 27, 28, 9, 30,
        31, 21, 24, 14, 24, 25, 26, 27, 19, 31,
        41, 33, 23, 33, 34, 35, 27, 28, 29, 50,
        42, 32, 33, 45, 46, 36, 37, 38, 39, 51,
        41, 42, 52, 53, 65, 55, 47, 57, 58, 50,
        62, 72, 53, 63, 64, 65, 66, 69, 79, 60,
        70, 73, 63, 64, 76, 77, 67, 77, 78 
	};

    maze_42.predecessors = maze_array_42;

    // MAZE 76
    maze maze_76 = {
        .width = 10,
        .height = 8,
        .predecessors = NULL,
        .cost = -695,
    };

    int maze_array_76[] = { -1,
        2, 3, 4, 5, 15, 16, 17, 18, 8, 0,
        10, 13, 14, 4, 25, 26, 16, 17, 18, 30,
        11, 21, 22, 23, 24, 36, 17, 18, 19, 31,
        21, 31, 34, 35, 25, 35, 36, 39, 29, 30,
        51, 52, 42, 43, 44, 45, 48, 38, 39, 40,
        50, 51, 52, 53, 45, 57, 58, 59, 49, 61,
        71, 63, 73, 65, 55, 56, 57, 67, 68, 60,
        72, 62, 74, 64, 74, 75, 78, 68, 69 
	};

    maze_76.predecessors = maze_array_76;

    // MAZE 1024
    maze maze_1024 = {
        .width = 10,
        .height = 8,
        .predecessors = NULL,
        .cost = -742,
    };

    int maze_array_1024[] = { -1,
        0, 1, 13, 14, 4, 16, 8, 18, 19, 0,
        1, 11, 12, 24, 5, 26, 27, 28, 18, 10,
        11, 12, 13, 23, 35, 25, 28, 38, 19, 31,
        41, 22, 23, 24, 36, 46, 36, 37, 49, 30,
        42, 32, 42, 34, 44, 56, 57, 38, 48, 51,
        41, 42, 52, 53, 65, 55, 56, 57, 58, 50,
        62, 52, 62, 54, 66, 76, 66, 78, 79, 60,
        61, 71, 72, 73, 74, 75, 76, 77, 78 
	};

    maze_1024.predecessors = maze_array_1024;

    // MAZE 2048
    maze maze_2048 = {
        .width = 10,
        .height = 8,
        .predecessors = NULL,
        .cost = -666,
    };

    int maze_array_2048[] = { -1,
        0, 3, 13, 14, 4, 7, 17, 18, 19, 11,
        1, 22, 12, 13, 14, 15, 18, 28, 29, 10,
        20, 21, 22, 34, 26, 16, 26, 38, 28, 20,
        21, 31, 32, 44, 25, 37, 27, 37, 38, 50,
        51, 32, 42, 43, 46, 36, 37, 58, 59, 51,
        52, 42, 63, 53, 56, 46, 47, 59, 69, 61,
        62, 52, 73, 54, 64, 65, 66, 67, 79, 60,
        72, 62, 72, 75, 65, 66, 78, 68, 78 
	};

    maze_2048.predecessors = maze_array_2048;



    // Loading the mazes
    printf("  | Loading the mazes ...  \n\n");
    map *map_42 = map_loader("./data/map_10_8_42.txt"); 
    map *map_76 = map_loader("./data/map_10_8_76.txt"); 
    map *map_1024 = map_loader("./data/map_10_8_1024.txt"); 
    map *map_2048 = map_loader("./data/map_10_8_2048.txt"); 

    maze *maze_42_loaded = prim_algorithm(map_42);
    maze *maze_76_loaded = prim_algorithm(map_76);
    maze *maze_1024_loaded = prim_algorithm(map_1024);
    maze *maze_2048_loaded = prim_algorithm(map_2048);


    printf("  | Testing with maze 42 ...  \n");
    assert(comparaison_two_maze(*maze_42_loaded, maze_42) == true);
    printf("  | Success\n\n");

    printf("  | Testing with maze 76 ...  \n");
    assert(comparaison_two_maze(*maze_76_loaded, maze_76) == true);
    printf("  | Success\n\n");

    printf("  | Testing with maze 1024 ...  \n");
    assert(comparaison_two_maze(*maze_1024_loaded, maze_1024) == true);
    printf("  | Success\n\n");

    printf("  | Testing with maze 2048 ...  \n");
    assert(comparaison_two_maze(*maze_2048_loaded, maze_2048) == true);
    printf("  | Success\n\n");

    printf("  | OK!\n\n");

    free(maze_42_loaded);
    free(maze_76_loaded);
    free(maze_1024_loaded);
    free(maze_2048_loaded);
    free_map(map_42);
    free_map(map_76);
    free_map(map_1024);
    free_map(map_2048);

    return 0;
}