#include "gameStruct.h"
#include <stdlib.h> // for malloc


int getStructMode(){
	return 1;
}

void insert(void* root,int x,int y,Cell* cell){
	return;
};

void* init(int size,int turn){
	Matrix* tab = (Matrix*) malloc(sizeof(Matrix));
 	tab->player = turn;
	for(int k=1;k<=size;k++){
		for(int i=1;i<=size;i++){
			tab->cell[i][k]=createCell();
		}
	}
	return tab;
}

Cell* lookup(void* matrixVoid,int x,int y){
	Matrix* matrix = (Matrix*)matrixVoid;
	return matrix->cell[x][y];
}