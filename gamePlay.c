#include"gamePlay.h"

int structMode;

void defineGlobalGp(int var){
	structMode = var;
}

int shoot(GameMap* map,int x, int y){
	Cell* cell;
	if(structMode==1){
		cell = lookup(map->val.tab,x,y);
	}
	else{
		cell = lookup(map->val.qt->root,x,y);
		//in case we didnt insert a point there
		if(cell==NULL){
			insert(map->val.qt->root,x,y,createCell());
		}
		cell = lookup(map->val.qt->root,x,y);
	}
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

int checkWinner(User* user){
	GameMap* map = user->map;
	int size = map->size;
	for(int k=size;k>=1;k--){
		for(int i=1;i<=size;i++	){
			Cell* cell;
			if(structMode==1){
				cell = lookup(map->val.tab,i,k);
			}
			else{
				cell = lookup(map->val.qt->root,i,k);
			}
			if(cell!=NULL){
				if(cell->shot==1){
					return 1;
				}
			}
		
		}
	}
}