#include<stdio.h>
#include"boats.h"
struct _Boat {
	enum{
		ONE,
		TWO,
		THREE,
		FOUR,
		L
	}kind;
	int shots;
	int cells;
	int matrixSize;
	int boatMatrix[41][41];
};

struct _Cell {
	struct _Boat* boat;
	int shot;
};

struct _Matrix {
	int player;
	struct _Cell* cell[41][41];	
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
typedef struct _Matrix Matrix;
typedef struct _Cell Cell;
typedef struct _Boat Boat;


/*
functions
*/
void showMap(GameMap* map);

//for keyboard input verification
int verifyInput(int min, int max, int size);

User* newUser(int size);

// structMode 1 = matrix, structMode 2 = QuadTree
GameMap* createMap(int size);

Matrix* createMatrix(int size);
Cell* createCell();

//used to test if it's printing right
void testShot(GameMap* map, int x, int y);

//print the boat in a matrix
void printBoat(Boat* boat);

//random number generator
int randomm(int lower, int upper);



//shows the map with the boats in it
void showMapBoats(GameMap* map);

double coss(int angle);
double sinn(int angle);



//set all array values to 0
void setArrayZero(int array[41][41]);

int shoot(GameMap* map, int x, int y);


int checkWinner(User* user);


//boatPlacing manual = 1, random = 2
void createBoats(GameMap* map);

void userBoats(User* user);


//choose the rotation and call moveLoop
void placeBoat(GameMap* map, Boat* boat);


//verifies if boat can be placed, if not it calls moveloop again
void placeInMap(GameMap* map, Boat* boat);

//verifies if there are boats near the boat we want to place
int near(GameMap* map, Boat* boat);


//makes the rotation
void rotation(Boat* boat,int angle);

//moves the boat to the direction in the boatMatrix
int moveBoat(Boat* boat, int direction);

//the move options loop, calls palceInMap
void moveLoop(GameMap* map, Boat* boat);

void makeRandomMoves(GameMap* map, Boat* boat);

void setBoatMatrix(Boat* boat,int boatM[5][5]);

