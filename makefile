all: battleship.c
quadtree:
	gcc -o battleship battleship.c quadtree.c print.c auxFunctions.c boat.c gamePlay.c cell.c 
matrix:
	gcc -o battleship battleship.c matrix.c print.c auxFunctions.c boat.c gamePlay.c cell.c 

