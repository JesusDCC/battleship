#ifndef _gamePlay_h_
#define _gamePlay_h_

#include"print.h"
// to shoot a position
int shoot(GameMap* map, int x, int y);
// check if there's already a winner 
int checkWinner(User* user);
//define a global variable
void defineGlobalGp(int var);

#endif