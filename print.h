#ifndef _print_h_
#define _print_h_
#include"boat.h"
/**
prints a game map with a specific boat only
*/

/**
Prints the map, with the hidden boats and the already made shots
*/
void showMap(GameMap* map);

//define structMode global variable from other module
void defineGlobal(int var);

#endif