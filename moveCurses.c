
/* A very small game, it's just a character '@' moving around the terminal within a map */
/* '.' represents an empty cell
/* '#' represents a wall (you cannot walk through it)
/* '+' represents a door (use it to enter rooms)
/* Press 'q' for exit, and 'w','s','a','d' for moving */

#include <curses.h> 
#include "Maps.h"

int posX,posY,nRows,nCols;  	// Actual character position and terminal size

void printMap(int map[mapRows][mapColumns], int rows,int columns); // 12 y 175

void draw(char d);

int checkMovement(char d);

int main() { 
	int i;  char d;  
	WINDOW *wnd;				// The game window

	wnd = initscr();			// Some first window related steps
	cbreak();					
	noecho();				
	getmaxyx(wnd,nRows,nCols);	
	clear();	
	refresh();	
	
	nRows = mapRows -1 ;
	nCols = mapColumns -1 ;
	posX = 0; posY = 0;
	printMap(mapWallsDoorsAscii, mapRows, mapColumns);	// draw the initial map
	move(posX,posY);
	mvdelch(posY,posX);
	insch('@');
	refresh();
	while (1){					// Start the game, wait for player imput
		d = getch();			
		if (d == 'q') break;	// Exit!
		printMap(mapWallsDoorsAscii, mapRows, mapColumns);
		draw(d);				// Try to move the character
		move(posY,posX);
	}

	endwin();					// Close it
	return 0;
}

/* Check the movement and draw it in the window */
void draw(char d){
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
	mvdelch(posY,posX);
	move(posY,posX);
	insch('@');	
	refresh(); 
}

/* Check window boundaries*/
int checkMovement(char d){
	if ( d == 'd'){					// Check right
		if (posX+1 > nCols || mapWallsDoorsAscii[posY][posX+1] ==35 ){
			return 0;
		}
		return 1;
	}
	if ( d == 'a'){					// Check left
		if (posX-1 < 0 || mapWallsDoorsAscii[posY][posX-1] ==35 ){
			return 0;
		}
		return 1;
	}
	if ( d == 'w'){					// Check  Up
		if (posY-1 < 0 || mapWallsDoorsAscii[posY-1][posX] ==35 ){
			return 0;
		}
		return 1;
	}
	if ( d == 's'){					// Check Down
		if ( posY+1 > nRows || mapWallsDoorsAscii[posY+1][posX] ==35 ){
			return 0;
		}
		return 1;
	}
}


void printMap(int map[mapRows][mapColumns], int rows,int columns){
	int i,j;
	for ( i = 0; i < rows ; i++ ) {
		for ( j = 0; j < columns ; j++){
			mvaddch(i,j,map[i][j]);
		}
	}
}



