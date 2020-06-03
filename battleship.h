#ifndef _battleship_h_
#define _battleship_h_
#include<stdio.h>
#include"gameStruct.h"

struct _GameMap {
	enum{
		MATRIX,
		QUADTREE
	}kind;
	int size;
	union{
		QuadTree* qt;
		Matrix* tab;	
	}val;
};	

struct _User {
	struct _GameMap* map;
};

/*
typedef
*/
typedef struct _User User;
typedef struct _GameMap GameMap;
//typedef struct _QuadTree QuadTree;

/**
Calls createBoats and showMapBoats after all boats got placed
*/
void userBoats(User* user);

/**
Initialize User structure
*/
User* newUser(int size);

/**
structMode 1 = matrix, structMode 2 = QuadTree
Creates the map, depending on the structure choosen 
*/
GameMap* createMap(int size);



#endif
