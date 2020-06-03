#ifndef _gameStruct_h_
#define _gameStruct_h_
#include"cell.h"	

typedef struct _Quadtree QuadTree;
typedef struct _QuadTreeNode QuadTreeNode;
typedef struct _Rectangle Rectangle;
typedef struct _Point Point;
typedef struct _Matrix Matrix;


struct _Matrix {
	int player;
	Cell* cell[41][41];	
};

struct _Point {
	float x;
	float y;
};
struct _Rectangle{
	float x;
	float y;
	float w;
	float h;
};

struct _Quadtree {
	int player;
	struct _QuadTreeNode* root;
};

struct _QuadTreeNode {
	enum {
		NODE,
		LEAF
	}kind;
	struct _Rectangle* boundary;
	union{
		struct _QuadTreeNode* quadrants[4];
		struct {
			Cell* cell;
			struct _Point* p;
		}leaf;
	}node;
};

int getStructMode();
void insert(void* node, int x,int y, Cell* cell);
void subdivide(QuadTreeNode* node);
QuadTreeNode* createNode(Rectangle* bounds);
Rectangle* createRectangle(float x,float y, float w, float h);
Point* makePoint(float x, float y);
int contains(QuadTreeNode* node, Point* p);
int equalPoints(Point* one, Point* two);
Cell* lookup(void* root, int x,int y);
void* init(int size, int player);

#endif