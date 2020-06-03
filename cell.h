#ifndef _Cell_h_
#define _cell_h_
typedef struct _Cell Cell;

struct _Cell {
	struct _Boat* boat;
	int shot;
};


Cell* createCell();

#endif