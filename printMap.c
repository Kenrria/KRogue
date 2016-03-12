/*
 * Just print the map using the standar output
 */ 
#include <stdio.h>
#include "Maps.h"


void printMap(int map[mapRows][mapColumns], int rows,int columns);

int main () {
	
	printMap(mapWalls1Ascii, mapRows, mapColumns);

	return 0;
}


void printMap(int map[mapRows][mapColumns], int rows,int columns){
	int i,j;
	for ( i = 0; i < rows ; i++ ) {
		for ( j = 0; j < columns ; j++){
			printf("%c", map[i][j]);		
		}
		printf("\n");
	}
}
