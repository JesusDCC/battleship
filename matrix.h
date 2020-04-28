struct _Matrix {
	int player;
	struct _Cell* cell[41][41];	
};

typedef struct _Matrix Matrix;

Matrix* createMatrix(int size,int turn);
