#include<stdio.h>

struct _Cell {
	struct _Boat* boat;
	int shot;
};


struct _GameMap {
	enum{
		MATRIX,
		QUADTREE
	}kind;
	int size;
	union{
		//struct _QuadTree* root;
		struct _Matrix* tab;	
	};
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
typedef struct _Cell Cell;

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

Cell* createCell();



