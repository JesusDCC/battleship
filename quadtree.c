#include "gameStruct.h"
#include <stdlib.h> // for malloc
#include<stdio.h>

//returns 2 because gamestruct == 2 means that it's working with quadtree structure
int getStructMode(){
	return 2;
}



QuadTreeNode* createNode(Rectangle* bounds){
	QuadTreeNode* node = (QuadTreeNode*) malloc(sizeof(QuadTreeNode));
	node->kind = LEAF;
	node->boundary = bounds;
	return node;
}

Rectangle* createRectangle(float x,float y,float w,float h){
	//create Rectangle structure
	Rectangle* boundary = (Rectangle*) malloc(sizeof(Rectangle));
	boundary->x=x;
	boundary->y=y;
	boundary->w=w;
	boundary->h=h;
	return boundary;
}

void* init(int size, int player){
	QuadTree* quadTree = (QuadTree*) malloc(sizeof(QuadTree));
	Rectangle* boundary = createRectangle(0,0,size,size);
	quadTree->root = createNode(boundary);
	quadTree->player = player;
	return quadTree;
} 

//the cell argument is used to re insert the point that was already in the node
void insert(void* nodeVoid, int x, int y, Cell* cell){
	QuadTreeNode* node = (QuadTreeNode*) nodeVoid;
	Point* p = makePoint(x,y);
	if(!contains(node,p)){
		//printf("hereee");
		return;
	}
	//if the node is a leaf
	if(node->kind == LEAF ){
		//verificar se o node contem o ponto
		//empty leaf
		if(node->node.leaf.p==NULL){
			node->node.leaf.cell = cell;
			node->node.leaf.p = p;
			return;
		}
		//leaf with a point on it
		else{
			Point* rePoint = node->node.leaf.p;
			Cell* reCell = node->node.leaf.cell;
			//changes node type from leaf to node
			subdivide(node);
			//re insert the old point
			insert(node->node.quadrants[0],rePoint->x,rePoint->y,reCell);
			insert(node->node.quadrants[1],rePoint->x,rePoint->y,reCell);
			insert(node->node.quadrants[2],rePoint->x,rePoint->y,reCell);
			insert(node->node.quadrants[3],rePoint->x,rePoint->y,reCell);
			//insert the a new point
			insert(node->node.quadrants[0], p->x,p->y, createCell());
			insert(node->node.quadrants[1], p->x,p->y, createCell());
			insert(node->node.quadrants[2], p->x,p->y, createCell());
			insert(node->node.quadrants[3], p->x,p->y, createCell());
			return;
		}
	}
	//if the node isn't a leaf
	if(node->kind == NODE){
		insert(node->node.quadrants[0],p->x,p->y,createCell());
		insert(node->node.quadrants[1],p->x,p->y,createCell());
		insert(node->node.quadrants[2],p->x,p->y,createCell());
		insert(node->node.quadrants[3],p->x,p->y,createCell());
	}
}


//change kind from leaf to node and subdivide
void subdivide(QuadTreeNode* node){
	Rectangle* boundary = node->boundary;
	float x = boundary->x;
	float y = boundary->y;
	float w = boundary->w;
	float h = boundary->h;
	node->kind = NODE;
	float l = w-x;

	
	Rectangle* tl = createRectangle(x,y+l/2,x+l/2,h);
	node->node.quadrants[0] = createNode(tl);
	Rectangle* tr = createRectangle(x+l/2,y+l/2,w,h);
	node->node.quadrants[1] = createNode(tr);
	Rectangle* bl = createRectangle(x,y,x+l/2,y+l/2);
	node->node.quadrants[2] = createNode(bl);
	Rectangle* br = createRectangle(x+l/2,y,w,y+l/2);
	node->node.quadrants[3] = createNode(br);
}



Point* makePoint(float x, float y){
	Point* point = (Point*) malloc(sizeof(Point));
	point->x = x;
	point->y = y;
	return point;
}

int contains(QuadTreeNode* node, Point* p){
	Rectangle* boundary = node->boundary;
	if(p->x >= boundary->x && p->x <= boundary->w ){
		if(p->y >= boundary->y && p->y <= boundary->h){
			return 1;
		}
	}
	return 0;
}

int equalPoints(Point* one, Point* two){
	if(one->x == two->x && one->y == two->y){
		return 1;
	}
	return 0;
}


Cell* lookup(void* rootVoid, int x, int y){
	QuadTreeNode* root = (QuadTreeNode*) rootVoid;
	Point* p = makePoint(x,y);
	if(root->kind == LEAF){
		if(!contains(root,p)){
			return NULL;
		}
		if(root->node.leaf.p==NULL){
			return NULL;
		}
		else{
			if(equalPoints(p,root->node.leaf.p)){
				return root->node.leaf.cell;
			}
		}
	}
	else{
		Cell* cell;
		cell = lookup(root->node.quadrants[0],p->x,p->y);
		if(cell==NULL){
			cell = lookup(root->node.quadrants[1],p->x,p->y);
			if(cell==NULL){
				cell = lookup(root->node.quadrants[2],p->x,p->y);
			}
			if(cell==NULL){
				cell = lookup(root->node.quadrants[3],p->x,p->y);
			}
		}
		return cell;	
	}
}

