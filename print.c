#include "print.h"

int structMode;

void defineGlobal(int var){
	structMode = var;
}



void showMap(GameMap* map){
	int size = map->size;
	for(int i=1;i<=9;i++){
		printf("_%d_|",i);
	}
	for(int i=10;i<=size;i++){
		printf("_%d|",i);
	}
	printf("\n");
	for(int k=size;k>=1;k--){
		for(int i=1;i<=size;i++	){
			Cell* cell;
			if(structMode==1){
				cell = lookup(map->val.tab,i,k);
			}
			else{
				cell = lookup(map->val.qt->root,i,k);
			}
			//SHOT BOAT
			if(cell!=NULL){
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
			}
			else{
				printf("___");
			}
			
			printf("|");
		}
		printf("%d\n",k);
	}
}
