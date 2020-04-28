#include "print.h"
#include "matrix.c"

int structMode;

void defineGlobal(int var){
	structMode = var;
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
