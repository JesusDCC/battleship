#include"gamePlay.h"

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