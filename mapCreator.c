
/* File: mapCreator.c
   Author: Jesus Cruz
   Time spent: about 2:30 hours
   
	This program will be used to create a map using the terminal and the library Ncurses
	
	First it asks the user to write the number of the new map.
	Then it opens a curses window with the blank map 
	Using the cursor and some keys you can modify the blank map
	After quiting the map will be saved if the file MapsUser.h

	Keys, fist press ':' if you want to change your pencil
	- 'q' for quiting
	- '#' for writing walls with the cursor
	- '+' for doors
	- 'r' for removing
	- 'm' for moving without writing

	How to use it: first you have to select what you want to place in the map: walls(w), doors(d),
	or removing(r). Once you have selected the item move the cursor to write it.
	If you want to edit one position type the cell type you want and then 'm'.

*/

#include <curses.h>
#include <stdio.h>
#include <string.h>
#include "MapsUser.h"	// The header where we will store the maps

int posX = 0, posY = 0;
int temporalMap[mapRows][mapColumns];

void printMap(int map[mapRows][mapColumns], int auxRows, int auxCols){
	int i,j;
	for ( i = 0; i < auxRows ; i++ ) {
		for ( j = 0; j < auxCols ; j++){
			printf("%c", map[i][j]);		
		}
		printf("\n");
	}
}

void saveMap (int map[mapRows][mapColumns], int auxRows, int auxCols, FILE *f){
	int i,j;
	for ( i = 0; i < auxRows ; i++ ) {
		fprintf(f, "\n%s", "{");				// add {
		for ( j = 0; j < auxCols ; j++){
			fprintf( f, "%d ", map[i][j] );	
			if ( j == auxCols -1 && i!= auxRows - 1  ) {			// Last digit
				fprintf(f, "%s", "},");
			}	
			if ( j != auxCols -1  ) {			// Last digit
				fprintf(f, "%s", ",");	
			}	
				
		}
		if ( i == auxRows - 1) {
			fprintf(f, "%s", "}};");
		}
	}
}

/* Check window boundaries*/
int checkMovement(char d){
	if ( d == 'd'){					// Check right
		if (posX+1 >= mapColumns ){
			return 0;
		}
		return 1;
	}
	if ( d == 'a'){					// Check left
		if (posX-1 < 0  ) {
			return 0;
		}
		return 1;
	}
	if ( d == 'w'){					// Check  Up
		if (posY-1 < 0  ) {
			return 0;
		}
		return 1;
	}
	if ( d == 's'){					// Check Down
		if ( posY+1 >= mapRows  ) {
			return 0;
		}
		return 1;
	}
}

int checkChar(char cellContent){
	if ( cellContent!='.' && cellContent != '+' && cellContent !='#' && cellContent != 'r' && cellContent != 'm') {
		return 0;
	}
	return 1;
}

/* Check the movement and draw it in the window */
void draw(char d, char cellContent){

	if (checkMovement(d)) {
		if ( d == 'd') {			// Move Right
			posX++;
		}
		if ( d == 'a') {			// Move Lef
			posX--;
		}
		if ( d == 'w') {			// Move Up
			posY--;
		}
		if ( d == 's') {			// Move Down
			posY++;
		}
	}

	if ( cellContent == 'm'){
		move(posY,posX);
		refresh();
		return;
	}

	mvdelch(posY,posX);
	move(posY,posX);
	insch(cellContent);
	temporalMap[posY][posX] = (int) cellContent;
	refresh(); 
}

int main (){
	
	char mapName[50];
	char mapHeader[100];
	FILE *f = fopen("MapsUser.h", "a");

	// We read the name of the new map
	printf("Enter the name of the new map: ");
	scanf("%s", mapName);		

	int i,j;
	for ( i = 0; i < mapRows ; i++ ) {
		for ( j = 0; j < mapColumns ; j++){
			temporalMap[i][j] = 46;	
		}
	}


	char d, mode, previousMode;
	WINDOW *wnd;				// The game window
	wnd = initscr();			// Some first window related steps
	cbreak();					
	noecho();				
	clear();	
	refresh();	

	mode = '.';
	while (1){					// Start the game, wait for player imput
		d = getch();
		if (d != ':') {
			draw(d,mode);
		}
		if (d == 'q') break;
		if (d == ':' ) {
			previousMode = mode;
			mode = getch();	
			if (checkChar(mode) == 0 ) mode = previousMode;	
			if ( mode == 'r' ) mode = ' ';		
		}
	}

	endwin();

	// Now we had the next string: "int "mapName"[15][20]= {"
	strcpy( mapHeader, "int ");
	strcat( mapHeader, mapName);
	strcat( mapHeader, "[mapRows][mapColumns]= {");

	fprintf( f, "\n%s\n", mapHeader );
	saveMap(temporalMap, mapRows, mapColumns, f);

	return 0;
}

