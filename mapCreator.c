
/* File: mapCreator.c
   Author: Jesus Cruz
   Time spent: about 8 hours
   
	This program will be used to create a map using the terminal and the library Ncurses
	
	First it asks the user to write the number of the new map.
	Then it opens a curses window with the blank map 
	Using the cursor and some keys you can modify the blank map
	After quiting the map will be saved if the file MapsUser.h

	Keys: first press ':' if you want to change your pencil,then on the next keys
	- 'q' for quiting without saving
	- 'g' for saving
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

/* Check if the char is a valid one, if yes return 1*/
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
	/* If the char is 'm' it means moving without drawing */
	if ( cellContent == 'm'){
		move(posY,posX);
		refresh();
		return;
	}
	/* In other cases draw the valid character */
	else{
		mvdelch(posY,posX);
		move(posY,posX);
		insch(cellContent);
		temporalMap[posY][posX] = (int) cellContent;
		refresh(); 
	}
}

/* Update the notification window with the actual pencil */
void updateEchoWindow(WINDOW *echoWindow,WINDOW *map,char mode){

	mvwprintw(echoWindow, 0, 0, "Printing:" );
	char aux[2];
	aux[0]=mode;
	aux[1]='\0';						// We mark the end of the char[]
	mvwprintw(echoWindow,0,10, aux);	// We show the actual pencil
	wrefresh(echoWindow);				// show the changes in the window
	wmove(map,posY,posX);				// And move the cursor to the main window 


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


	// Here goes the window related code and the main loop
	char d, mode = '.', previousMode;

	initscr();
	noecho();

	// Two windows, map is where we draw and echoWindow is a small notification area
	WINDOW *map = newwin(25,100,0,0);				
	WINDOW *echoWindow = newwin(1,20,26,0);

	// Main loop, right now is an active wait, not good
	while (1){	
		updateEchoWindow(echoWindow,map,mode);		// We update the notification area
		d = wgetch(map);							// is there any imput? if not continue
		if (d != ':') {
			draw(d,mode);
		}
		if (d == 'q') return 0;
		if (d == 'g') break;
		if (d == ':' ) {
			previousMode = mode;
			mode = getch();	
			if (checkChar(mode) == 0 ) mode = previousMode;	
			if ( mode == 'r' ) mode = ' ';		
			draw(d,mode);
		}
	}

	// Close the windows 
	endwin();

	// Now we had the next string: "int "mapName"[15][20]= {"
	strcpy( mapHeader, "int ");
	strcat( mapHeader, mapName);
	strcat( mapHeader, "[mapRows][mapColumns]= {");

	fprintf( f, "\n%s\n", mapHeader );
	saveMap(temporalMap, mapRows, mapColumns, f);

	return 0;
}

