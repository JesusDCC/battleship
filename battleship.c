#include<stdio.h>
#include<math.h>
#include <stdlib.h> // for malloc
#include "battleship.h"
#include <time.h>
#include <unistd.h>
#include "boat.c"
#include "gamePlay.c"

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
			defineGlobal(structMode);
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

void userBoats(User* user){
	createBoats(user->map, boatPlacing);
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
			map->tab = createMatrix(size,turn);
			return map;
		case 2:
			;//empty statement for switch to work
			//CODE TO CREATE MAP WITH QUADTREE
			break;
	}
}

Cell* createCell(){
	Cell* cell = (Cell*) malloc(sizeof(Cell));
	cell->boat = NULL;
	cell->shot=0;
	return cell;
}

