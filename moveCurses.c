/* A very small game, it's just a character '@' moving around the terminal */
/* Press 'q' for exit, and 'w','s','a','d' for moving */
#include <curses.h> 

int posX,posY,nRows,nCols;  	// Actual character position and terminal size

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

	posX = 0; posY = 0;
	insch('@');
	while (1){					// Start the game, wait for player imput
		d = getch();			
		if (d == 'q') break;	// Exit!
		draw(d);				// Try to move the character
	}

	endwin();					// Close it
	return 0;
}

/* Check the movement and draw it in the window */
void draw(char d){
	if (checkMovement(d)) {
		if ( d == 'd') {			// Move Right
			delch();
			posX++;
			move(posY,posX);
			insch('@');	
			refresh(); 
		}
		if ( d == 'a') {			// Move Lef
			delch();
			posX--;
			move(posY,posX);
			insch('@');	
			refresh(); 
		}
		if ( d == 'w') {			// Move Up
			delch();
			posY--;
			move(posY,posX);
			insch('@');	
			refresh(); 
		}
		if ( d == 's') {			// Move Down
			delch();
			posY++;
			move(posY,posX);
			insch('@');	
			refresh(); 
		}
	}
}

/* Check window boundaries*/
int checkMovement(char d){
	if ( d == 'd'){					// Check right
		if (posX+1 > nCols){
			return 0;
		}
		return 1;
	}
	if ( d == 'a'){					// Check left
		if (posX-1 < 0){
			return 0;
		}
		return 1;
	}
	if ( d == 'w'){					// Check  Up
		if (posY-1 < 0){
			return 0;
		}
		return 1;
	}
	if ( d == 's'){					// Check Down
		if ( posY+1 > nRows){
			return 0;
		}
		return 1;
	}
}  
















