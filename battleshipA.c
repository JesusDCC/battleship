#include<stdio.h>
#include<math.h>
#include <stdlib.h> // for malloc
#include "battleshipA.h"
#include <time.h>
#include <unistd.h>

#define SIZEMIN 20
#define SIZEMAX 40
#define MAXBOATSIZE 5

int turn = 1;
//MATRIX OR QUADTREE
int structMode;
//RANDOM OR MANUAL
int boatPlacing;

int main(int argc, char *argv[]) {
	int stop=0;
	while(stop!=1){
		printf("Choose game structure mode!\n1)Matrix\n2)QuadTree\n");
		scanf("%d", &structMode);
		while(!verifyInput(1,2,structMode)){
			scanf("%d", &structMode);
		}
		printf("Define square size! (Between 20 and 40)\n");
		int size;
		scanf("%d", &size);
		while(!verifyInput(SIZEMIN,SIZEMAX,size)){
			scanf("%d", &size);
		}
		///////////////////////////7
		printf("Let's Place those Boats!\n1)Manually\n2)Randomly\n");
		scanf("%d", &boatPlacing);
		while(!verifyInput(1,2,boatPlacing)){
			scanf("%d", &boatPlacing);
		}
		User* user1 = newUser(size);
		userBoats(user1);
		turn = 2;
		User* user2 = newUser(size);
		userBoats(user2);
		turn = 1;
		User* user=user1;
		while(checkWinner(user)!=0){
			if(turn == 1){
				user = user2;
			}
			else if(turn==2){
				user = user1;
			}
			printf("Player %d turn!\n", turn);
			showMap(user->map);
			printf("\nEnter X and Y to shoot!\n");
			int x;
			int y;
			scanf("%d",&x);
			while(!verifyInput(1,user->map->size,x)){
				scanf("%d", &x);
			}
			scanf("%d",&y);
			while(!verifyInput(1,user->map->size,y)){
				scanf("%d", &y);
			}
			int shot = shoot(user->map,x,y);
			showMap(user->map);
			if(shot==2){
				printf("Looks like you shot there already! Try again\n");
				while(shot==2){
					int x;
					int y;
					scanf("%d",&x);
					while(!verifyInput(1,user->map->size,x)){
						scanf("%d", &x);
					}
					scanf("%d",&y);
					while(!verifyInput(1,user->map->size,y)){
						scanf("%d", &y);
					}
					shot = shoot(user->map,x,y);
					showMap(user->map);
				}
			}
			if(shot==1)printf("Good job! You shot a boat\n");
			else if(shot==0)printf("You missed! More luck next time\n");
			else if(shot==3)printf("Good job! You sank a boat\n");
			sleep(5);
			system("clear");
			if(turn==1) turn = 2;
			else turn = 1;
		}
		int winner=0;
		if(turn==1) winner = 2;
		else winner = 1;
		printf("Looks like we have a winner!\nCongratulations to player %d\n",winner);
		printf("1)Leave Game\n2)play again\n");
		scanf("%d",&stop);
	}
}
int checkWinner(User* user){
	GameMap* map = user->map;
	int size = map->size;
	switch(structMode){
		case 1:;
			Matrix* matrix = map->tab;
			for(int k=size;k>=1;k--){
				for(int i=1;i<=size;i++	){
					Cell* cell = matrix->cell[i][k];
					if(cell->shot==1){
						return 1;
					}
				}
			}
			return 0;
		case 2:;
	}
}

int shoot(GameMap* map,int x, int y){
	switch(structMode){
		case 1:;
			Matrix* tab = map->tab;
			Cell* cell = tab->cell[x][y];
			//BOAT THAT HAD'NT BEEN SHOT YET
			if(cell->shot==1){
				cell->shot = 2;
				cell->boat->shots+=1;
				//destroyed a boat
				if(cell->boat->shots==cell->boat->cells)
					return 3;
				else
				return 1;
			}
			else if(cell->shot==2 || cell->shot==3){
				return 2;
			}
			else if(cell->boat==NULL){
				cell->shot=3;
				return 0;
			}
	}
	return 2;
}



void userBoats(User* user){
	
		createBoats(user->map);
		printf("Player %d\n",turn);
		showMapBoats(user->map);
		int ok;
		printf("1)Confirm\n");
		scanf("%d",&ok);
		system("clear");
}

User* newUser(int size){
	User* user = (User*) malloc(sizeof(User));
	user->map = createMap(size);
	return user;
}

GameMap* createMap(int size){
	switch(structMode){
		case 1:
			;//empty satement for switch to work
			GameMap* map = (GameMap*) malloc(sizeof(GameMap));
			map->kind = MATRIX;
			map->size=size;
			map->tab = createMatrix(size);
			return map;
		case 2:
			;//empty statement for switch to work
			//CODE TO CREATE MAP WITH QUADTREE
			break;
	}
}

Matrix* createMatrix(int size){
	Matrix* tab = (Matrix*) malloc(sizeof(Matrix));
 	tab->player = turn;
	for(int k=1;k<=size;k++){
		for(int i=1;i<=size;i++){
			tab->cell[i][k]=createCell();
		}
	}
	return tab;
}

Cell* createCell(){
	Cell* cell = (Cell*) malloc(sizeof(Cell));
	cell->boat = NULL;
	cell->shot=0;
	return cell;
}

void createBoats(GameMap* map){
	//BOAT OF SIZE 1
	Boat* one = (Boat*) malloc(sizeof(Boat));
	one->kind = ONE;
	one->matrixSize = map->size;
	one->shots = 0;
	one->cells = 1;
	setArrayZero(one->boatMatrix);
	one->boatMatrix[10][10]=1;
	placeBoat(map,one);
	
	//BOAT OF SIZE 2
	Boat* two = (Boat*) malloc(sizeof(Boat));
	two->kind = TWO;
	two->cells = 2;
	two->matrixSize = map->size;
	two->shots = 0;
	setArrayZero(two->boatMatrix);
	two->boatMatrix[10][10]=1;
	two->boatMatrix[10][11]=1;
	placeBoat(map,two);

	//BOAT OF SIZE 3
	Boat* three = (Boat*) malloc(sizeof(Boat));
	three->kind = THREE;
	three->cells = 3;
	three->matrixSize = map->size;
	three->shots = 0;
	setArrayZero(three->boatMatrix);
	three->boatMatrix[10][10]=1;
	three->boatMatrix[10][11]=1;
	three->boatMatrix[10][12]=1;
	placeBoat(map,three);

	//BOAT OF SIZE 4
	Boat* four = (Boat*) malloc(sizeof(Boat));
	four->kind = FOUR;
	four->cells = 4;
	four->matrixSize = map->size;
	four->shots = 0;
	setArrayZero(four->boatMatrix);
	four->boatMatrix[10][10]=1;
	four->boatMatrix[10][11]=1;
	four->boatMatrix[10][12]=1;
	four->boatMatrix[10][13]=1;
	placeBoat(map,four);

	//BOAT IN L
	Boat* l = (Boat*) malloc(sizeof(Boat));
	l->kind = L;
	l->matrixSize = map->size;
	l->cells=4;
	l->shots = 0;
	setArrayZero(l->boatMatrix);
	l->boatMatrix[8][10]=1;
	l->boatMatrix[9][10]=1;
	l->boatMatrix[10][10]=1;
	l->boatMatrix[10][11]=1;
	placeBoat(map,l);
}


//METER O BARCO NA POSICAO ESCOLHIDA NA BOATMATRIX
//NAS POSICOES Q TEM 1 NA BOATMATRIX, NO TABULEIRO APONTAR P BARCO


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


void placeInMap(GameMap* map, Boat* boat){
	int size = map->size;
	Matrix* matrix = map->tab;
	for(int k=size;k>=1;k--){
		for(int i=1;i<=size;i++	){
			Cell* cell = matrix->cell[i][k];
			if(boat->boatMatrix[i][k]==1){
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
		}
	}
	for(int k=size;k>=1;k--){
		for(int i=1;i<=size;i++	){
			Cell* cell = matrix->cell[i][k];
			if(boat->boatMatrix[i][k]==1){
				cell->boat = boat;
				cell->shot=1;
			}
		}
	}

}
//returns 0 if the boat is near other boat(adjacent), 1 if it isnt
int near(GameMap* map, Boat* boat){
	int size = map->size;
	Matrix* matrix = map->tab;
	for(int k=size;k>=1;k--){
		for(int i=1;i<=size;i++	){
			if(boat->boatMatrix[i][k]==1){
				if(k+1<=map->size){
					Cell* cellUp = matrix->cell[i][k+1];
					if(cellUp->boat!=NULL) return 0;
				}
				if(k-1>=1){
					Cell* cellDown = matrix->cell[i][k-1];
					if(cellDown->boat!=NULL) return 0;
				}
				if(i-1>=1){
					Cell* cellLeft = matrix->cell[i-1][k];
					if(cellLeft->boat!=NULL) return 0;
				}
				if(i+1<=map->size){
					Cell* cellRight = matrix->cell[i+1][k];
					if(cellRight->boat!=NULL) return 0;
				}

			}
		}
	}
	return 1;
}


int moveBoat(Boat* boat, int direction){
	int newBoat[41][41];
	setArrayZero(newBoat);

	int size = boat->matrixSize;
	switch(direction){
		case 1://left;
			for(int k=1;k<=size;k++){
				if(boat->boatMatrix[1][k]==1){
					return 1;
				}
			}
			//SET NEW VALUES TO -1
			for(int k=size;k>=1;k--){
				for(int i=1;i<=size;i++){
					if(boat->boatMatrix[i][k]==1){
						boat->boatMatrix[i][k]=0;
						newBoat[i-1][k]=1;
					}
				}
			}
			break;
		case 2://right
			for(int k=1;k<=size;k++){
				if(boat->boatMatrix[size][k]==1){
					return 1;
				}
			}
			for(int k=size;k>=1;k--){
				for(int i=1;i<=size;i++){
					if(boat->boatMatrix[i][k]==1){
						boat->boatMatrix[i][k]=0;
						newBoat[i+1][k]=1;
					}
				}
			}
			break;
		case 3://up
			for(int k=1;k<=size;k++){
				if(boat->boatMatrix[k][size]==1){
					return 1;
				}
			}
			for(int k=size;k>=1;k--){
				for(int i=1;i<=size;i++){
					if(boat->boatMatrix[i][k]==1){
						boat->boatMatrix[i][k]=0;
						newBoat[i][k+1]=1;
					}
				}
			}
			break;
		case 4://down
			for(int k=1;k<=size;k++){
				if(boat->boatMatrix[k][1]==1){
					return 1;
				}
			}
			for(int k=size;k>=1;k--){
				for(int i=1;i<=size;i++){
					if(boat->boatMatrix[i][k]==1){
						boat->boatMatrix[i][k]=0;
						newBoat[i][k-1]=1;
					}
				}
			}
			break;
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
	switch(structMode){
		case 1:;
			int size = map->size;
			Matrix* matrix = map->tab;
			for(int k=size;k>=1;k--){
				for(int i=1;i<=size;i++	){
					Cell* cell = matrix->cell[i][k];
					if(cell->boat!=NULL){
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
			break;
		case 2:;
			break;
		default:
			break;
	}
}

void showMap(GameMap* map){
	switch(structMode){
		case 1:;
			int size = map->size;
			Matrix* matrix = map->tab;
			for(int i=1;i<=9;i++){
				printf("_%d_|",i);
			}
			for(int i=10;i<=size;i++){
				printf("_%d|",i);
			}
			printf("\n");
			for(int k=size;k>=1;k--){
				for(int i=1;i<=size;i++	){
					Cell* cell = matrix->cell[i][k];
					//SHOT BOAT
					if(cell->shot==2){
						printf("_");
						printf("X");
						printf("_");
					}
					//MISSED SHOT
					else if(cell->shot==3){
						printf("_");
						printf("O");
						printf("_"); 
					}
					else{
						printf("___");
					}
					printf("|");
				}
				printf("%d\n",k);
			}
			break;
		case 2:;//QUADTREE
			break;
		default:
			break;
	}
}


/*void testShot(GameMap* map, int x, int y){
	Matrix* tab = map->tab;
	Cell* cell = tab->cell[x][y];
	cell->shot = 2;
}*/

double coss(int angle){
	switch(angle){
		case 0:
			return 1;
		case 90:
			return 0;
		case 180: 
			return -1;
		case 270:
			return 0;
	}
}

double sinn(int angle){
	switch(angle){
		case 0:
			return 0;
		case 90:
			return 1;
		case 180: 
			return 0;
		case 270:
			return -1;
	}
}


int verifyInput(int min, int max, int input){
	if(input <= max && input >= min) return 1;
	else {
		printf("\nWrong input, try again!\n");
		return 0;
	}
}


void setArrayZero(int array[41][41]){
	for(int i=1;i<=40;i++){
		for(int k=1;k<=40;k++){
			//printf("K:%d",k);
			//printf("I:%d",i);
			array[i][k]=0;
		}
	}
}

int randomm(int lower,int upper){
	int num = (rand() % (upper - lower + 1)) + lower; 
	//printf("Random: %d\n", num);
	return num;
}