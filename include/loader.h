/**
 * @file loader.h
 * 
 * @author a.grunewald
 * 
 * @brief Define the declarations of loading functions.
 */


#ifndef LOADER_H
#define LOADER_H

#include "map.h"

/**
 * @brief Reads a text file containing the map description and a structure representing the map.
 * 
 * @param address the address of the file that need to be open.
 * 
 * @return the pointer to the map. 
 */
map *map_loader(const char *address);

#endif