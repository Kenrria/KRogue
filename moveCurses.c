#include <curses.h> 

int posX,posY,nrows,ncols;  	

void draw(char d);

int checkMovement(char d);

int main() { 
	int i;  char d;  
	WINDOW *wnd;				// Puntero del tipo ventana con la ventana que vamos a usar

	wnd = initscr();			// Inicializamos la ventana
	cbreak();					// No esperaremos un enter, es decir, siguiente linea
	noecho();					// Desactivamos el echoing, es decir, que aparezca lo que escribimos
	getmaxyx(wnd,nrows,ncols);	// getTamañoVentana
	clear();					// Limpiar ventana y mandar el cursor a la posición (0,0)
	refresh();					// refrescar, es decir, que aparezcan los últimos cambios 

	posX = 0; posY = 0;
	insch('@');
	while (1){
		d = getch();			// leer desde el teclado
		if (d == 'q') break;	// q para salir
		draw(d);				// dibujar lo leído
	}

	endwin();					// Cierra la ventana 
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
	if ( d == 'd'){					// right
		if (posX+1 > ncols){
			return 0;
		}
		return 1;
	}
	if ( d == 'a'){					// left
		if (posX-1 < 0){
			return 0;
		}
		return 1;
	}
	if ( d == 'w'){					// Up
		if (posY-1 < 0){
			return 0;
		}
		return 1;
	}
	if ( d == 's'){					// Down
		if ( posY+1 > nrows){
			return 0;
		}
		return 1;
	}
}
















