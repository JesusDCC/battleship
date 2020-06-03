#include"cell.h"
#include <stdlib.h> // for malloc

Cell* createCell(){
	Cell* cell = (Cell*) malloc(sizeof(Cell));
	cell->boat = NULL;
	cell->shot=0;
	return cell;
}
