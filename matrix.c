#include "matrix.h"

Matrix* createMatrix(int size,int turn){
	Matrix* tab = (Matrix*) malloc(sizeof(Matrix));
 	tab->player = turn;
	for(int k=1;k<=size;k++){
		for(int i=1;i<=size;i++){
			tab->cell[i][k]=createCell();
		}
	}
	return tab;
}