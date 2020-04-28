
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

typedef struct _Boat Boat;

/** 
Initialize  boat structures with the matrix's defined in boats.h
After initializing each boat it calls placeBoat to place the boat in the game map
boatPlacing manual = 1, random = 2
*/
void createBoats(GameMap* map,int boatPlacing);


/**
Choose the rotation angle(can be random) then it calls moveLoop
to place the boat manually or makeRandomMoves for random placing
*/
void placeBoat(GameMap* map, Boat* boat);


/**
verifies if boat can be placed, if not it calls moveLoop
or makeRandomMoves again. Does this until the location is valid
*/
void placeInMap(GameMap* map, Boat* boat);

/**
verifies if there are boats near the boat we want to place
to respect the rule that boats can't be touching each other
*/
int near(GameMap* map, Boat* boat);

/**
makes the rotation of the boat
*/
void rotation(Boat* boat,int angle);

/**
moves the boat to the specified direction in the boatMatrix
*/
int moveBoat(Boat* boat, int direction);

//the move options loop, where user moves the boat as he wants, after confirm calls palceInMap
void moveLoop(GameMap* map, Boat* boat);

/**
Makes random moves using moveBoat to place the boat randomly
*/
void makeRandomMoves(GameMap* map, Boat* boat);

/**
place the boat defined in boats.h by a [5][5] matrix in the boatMatrix[41][41]  
*/
void setBoatMatrix(Boat* boat,int boatM[5][5]);
