#include"auxFunctions.h"

int verifyInput(int min, int max, int input){
	if(input <= max && input >= min) return 1;
	else {
		printf("\nWrong input, try again!\n");
		return 0;
	}
}

void setArrayZero(int array[41][41]){
	for(int i=1;i<=40;i++){
		for(int k=1;k<=40;k++){
			//printf("K:%d",k);
			//printf("I:%d",i);
			array[i][k]=0;
		}
	}
}


int randomm(int lower,int upper){
	int num = (rand() % (upper - lower + 1)) + lower; 
	//printf("Random: %d\n", num);
	return num;
}


double coss(int angle){
	switch(angle){
		case 0:
			return 1;
		case 90:
			return 0;
		case 180: 
			return -1;
		case 270:
			return 0;
	}
}

double sinn(int angle){
	switch(angle){
		case 0:
			return 0;
		case 90:
			return 1;
		case 180: 
			return 0;
		case 270:
			return -1;
	}
}

