#include"boat.h"
#include<math.h>
#include <stdlib.h> // for malloc
#include <time.h>
#include"boats.h"
#include <unistd.h>

int structMode;

void defineGlobalBoat(int var){
	structMode = var;
}

int boatPlacing;

void createBoats(GameMap* map,int boatPlacing){
	boatPlacing=boatPlacing;
	//BOAT OF SIZE 1
	Boat* one = (Boat*) malloc(sizeof(Boat));
	one->kind = ONE;
	one->matrixSize = map->size;
	one->shots = 0;
	one->cells = 1;
	setArrayZero(one->boatMatrix);
	setBoatMatrix(one,boatOne);
	placeBoat(map,one);
	
	//BOAT OF SIZE 2
	Boat* two = (Boat*) malloc(sizeof(Boat));
	two->kind = TWO;
	two->cells = 2;
	two->matrixSize = map->size;
	two->shots = 0;
	setArrayZero(two->boatMatrix);
	setBoatMatrix(two,boatTwo);
	placeBoat(map,two);

	//BOAT OF SIZE 3
	Boat* three = (Boat*) malloc(sizeof(Boat));
	three->kind = THREE;
	three->cells = 3;
	three->matrixSize = map->size;
	three->shots = 0;
	setArrayZero(three->boatMatrix);
	setBoatMatrix(three,boatThree);
	placeBoat(map,three);

	//BOAT OF SIZE 4
	Boat* four = (Boat*) malloc(sizeof(Boat));
	four->kind = FOUR;
	four->cells = 4;
	four->matrixSize = map->size;
	four->shots = 0;
	setArrayZero(four->boatMatrix);
	setBoatMatrix(four,boatFour);
	placeBoat(map,four);

	//BOAT IN L
	Boat* l = (Boat*) malloc(sizeof(Boat));
	l->kind = L;
	l->matrixSize = map->size;
	l->cells=4;
	l->shots = 0;
	setArrayZero(l->boatMatrix);
	setBoatMatrix(l,boatL);	
	placeBoat(map,l);
}

void placeBoat(GameMap* map, Boat* boat){
	switch(boatPlacing){
		case 1:// MANUALLY BOAT PALCING
			printf("Your game map until now!\n");
			showMapBoats(map);
			printf("\n\n");
			printf("Let's place this Boat!\n");
			printBoat(boat);
			printf("Choose rotation!\n1)0º\n2)90º\n3)180º\n4)270º\n");
			int angle;
			scanf("%d", &angle);
			while(!verifyInput(1,4,angle)){
				scanf("%d", &angle);
			}
			rotation(boat,angle);
			printBoat(boat);
	
			moveLoop(map,boat);	
			break;
		case 2:;//RANDOMLY BOAT PLACING
			int rotationChoice = randomm(1,4);
			//printf("Rotation random: %d", rotationChoice);
			rotation(boat,rotationChoice);
			makeRandomMoves(map,boat);
	}
}	

void placeInMap(GameMap* map, Boat* boat){
	int size = map->size;
	for(int k=size;k>=1;k--){
		for(int i=1;i<=size;i++	){
			Cell* cell = getCell(map,i,k);
			if(boat->boatMatrix[i][k]==1){
				if(cell!=NULL){
						if(cell->boat!=NULL || near(map,boat)==0){
							if(boatPlacing==1){
								printf("Invalid location! Choose another location\n");
								moveLoop(map,boat);	
							}
							else{
								makeRandomMoves(map,boat);
							}
							return;
						}
				}
				else {
					if(near(map,boat)==0){
						if(boatPlacing==1){
								printf("Invalid location! Choose another location\n");
								moveLoop(map,boat);	
							}
							else{
								makeRandomMoves(map,boat);
							}
							return;
					}
				}

			}
		}
	}
	for(int k=size;k>=1;k--){
		for(int i=1;i<=size;i++	){
			Cell* cell = getCell(map,i,k);
			if(boat->boatMatrix[i][k]==1){
				//Cell can only be null if we're working with quadtree, so getCell isn't needed
				if(cell==NULL){
					insert(map->val.qt->root,i,k,createCell());
					cell = lookup(map->val.qt->root,i,k);
				}

				cell->boat = boat;
				cell->shot=1;
			}
		}
	}
}

//returns 0 if the boat is near other boat(adjacent), 1 if it isnt
int near(GameMap* map, Boat* boat){
	int size = map->size;
	for(int k=size;k>=1;k--){
		for(int i=1;i<=size;i++	){
			if(boat->boatMatrix[i][k]==1){
				if(k+1<=map->size){
					Cell* cellUp = getCell(map,i,k+1);
					if(cellUp!=NULL){
						if(cellUp->boat!=NULL) return 0;
					}

				}
				if(k-1>=1){
					Cell* cellDown = getCell(map,i,k-1);
					if(cellDown!=NULL){
						if(cellDown->boat!=NULL) return 0;
					}
				}
				if(i-1>=1){
					Cell* cellLeft = getCell(map,i-1,k);
					if(cellLeft!=NULL){
						if(cellLeft->boat!=NULL) return 0;
					}
				}
				if(i+1<=map->size){
					Cell* cellRight = getCell(map,i+1,k);
					if(cellRight!=NULL){
						if(cellRight->boat!=NULL) return 0;
					}

				}

			}
		}
	}
	return 1;
}

void rotation(Boat* boat,int angleChoice){
	int angle;
	//printf("angle choice: %d\n", angleChoice);
	if(angleChoice==1) angle = 0;
	else if(angleChoice==2) angle = 90;
	else if(angleChoice==3) angle = 180;
	else angle =270;
	//printf("angle: %d\n", angle);
	int newBoat[41][41];
	int size = boat->matrixSize;
	setArrayZero(newBoat);
	for(int k=1;k<=size;k++){
		for(int i=1;i<=size;i++){
			if(boat->boatMatrix[i][k]==1){
				boat->boatMatrix[i][k]=0;
				int x = (coss(angle)*i) + (sinn(angle)*k);
				int y = (sinn(angle)*i) + (coss(angle)*k);
				if(x<=0)
					x = size + x;
				if(y<=0)
					y = size + y;
				//printf("x:%d\n",x);
				//printf("y:%d\n",y);
				newBoat[x][y]=1;
			}
		}
	}
	for(int k=1;k<=size;k++){
		for(int i=1;i<=size;i++){
			if(newBoat[i][k]==1){
				boat->boatMatrix[i][k]=1;
			}
			else{
				boat->boatMatrix[i][k]=0;
			}		
		}
	}

}

void moveLoop(GameMap* map, Boat* boat){
	int verify=0;
	printf("Now lets move the boat!\n");
	int move=0;
	while(move!=5){
		printf("\n1)Move left\n2)Move right\n3)Move Up\n4)Move down\n5)confirm\n");
		scanf("%d",&move);
		while(!verifyInput(1,5,move)){
			scanf("%d", &move);
		}
		if(move!=5)
			verify = moveBoat(boat, move);
		if(verify==1){
			printf("Can't make that move :/ try again\n");
			continue;
		}
		if(move!=5)
		printBoat(boat);
	}
	//save it in the map
	placeInMap(map,boat);
}

int moveBoat(Boat* boat, int direction){
	int newBoat[41][41];
	setArrayZero(newBoat);

	int size = boat->matrixSize;
	int rowDeslocation;
	int colDeslocation;
	switch(direction){
		case 1://left;
			for(int k=1;k<=size;k++){
				if(boat->boatMatrix[1][k]==1){
					return 1;
				}
			}
			rowDeslocation = -1;
			colDeslocation = 0;			
			break;
		case 2://right
			for(int k=1;k<=size;k++){
				if(boat->boatMatrix[size][k]==1){
					return 1;
				}
			}
			rowDeslocation = 1;
			colDeslocation = 0;
			break;
		case 3://up
			for(int k=1;k<=size;k++){
				if(boat->boatMatrix[k][size]==1){
					return 1;
				}
			}
			rowDeslocation = 0;
			colDeslocation = 1;
			break;
		case 4://down
			for(int k=1;k<=size;k++){
				if(boat->boatMatrix[k][1]==1){
					return 1;
				}
			}
			rowDeslocation = 0;
			colDeslocation = -1;
			break;
	}
	//SET NEW VALUES IN NEWBOAT MATRIX
	for(int k=size;k>=1;k--){
		for(int i=1;i<=size;i++){
			if(boat->boatMatrix[i][k]==1){
				boat->boatMatrix[i][k]=0;
				newBoat[i+rowDeslocation][k+colDeslocation]=1;
			}
		}
	}
	//COPY THE NEW MATRIX 
	for(int k=size;k>=1;k--){
		for(int i=1;i<=size;i++){
			if(newBoat[i][k]==1){
				boat->boatMatrix[i][k]=1;
			}
			else{
				boat->boatMatrix[i][k]=0;
			}		
		}
	}
	return 0;

}

void makeRandomMoves(GameMap* map, Boat* boat){
	int lastRand;
	int move = randomm(1,4);
	int i=0;
	while(move!=5){
		if(i==20) break;
		if(move==5) break;
		int verify = moveBoat(boat, move);
		srand ( time(NULL) );
		lastRand=move;
		move = (rand() % (5 - 1 + 1)) + 1;
		if(move==lastRand && verify == 1){	
			srand ( time(NULL) );
			move = (rand() % (5 - 1 + 1)) + 1;
		}
		//printf("MOVE : %d",move);
		i++;
	}
	placeInMap(map,boat);
}

void setBoatMatrix(Boat* boat,int boatM[5][5]){
	int centerBoat = boat->matrixSize/2;
	centerBoat-=2;
	for(int i=0;i<5;i++){
		for(int k=0;k<5;k++){
			if(boatM[i][k]==1)
			//printf("K:%d",k);
			//printf("I:%d",i);
			boat->boatMatrix[i+centerBoat][k+centerBoat]=boatM[i][k];
		}
	}
}

void printBoat(Boat* boat){
	int size = boat->matrixSize;
	for(int k=size;k>=1;k--){
		for(int i=1;i<=size;i++){
			if(boat->boatMatrix[i][k]==1){
				printf("_");
				printf("X");
				printf("_");
			}
			else{
				printf("___");
			}
			printf("|");

		}
		printf("\n");
	}
}

void showMapBoats(GameMap* map){
	int size = map->size;
	for(int k=size;k>=1;k--){
		for(int i=1;i<=size;i++	){
			Cell* cell = getCell(map,i,k);
			if(cell!=NULL){
				if(cell->boat!=NULL){
				printf("_");
				printf("X");
				printf("_");
				}
				else{
					printf("___");
				}
			}
			else{
				printf("___");
			}
			
			printf("|");
		}
		printf("\n");
	}
}

Cell* getCell(GameMap* map,int x, int y){
	Cell* cell;
	if(structMode==1){
		cell = lookup(map->val.tab,x,y);
	}
	else{
		cell = lookup(map->val.qt->root,x,y);
	}
	return cell;
}