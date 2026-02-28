#include <iostream>
#include <conio2.h>
#include <windows.h>
#include <cstdio>
#include <climits>
#include <cstdlib>
#include <ctime>


using namespace std;


// --- Primera Clase --- //


class ObjetoDibuja {
	
	
protected:
	
	int x, y;
	int color;
	clock_t tempo;
	clock_t paso;
	int velocidad;
	
	
public:
	
	ObjetoDibuja(int _x, int _y, int _vel, int _col) {
		
		
		x = _x; y = _y; velocidad = _vel; color = _col;
		if (velocidad > 0) paso = CLOCKS_PER_SEC / velocidad;
		else paso = 0;
		tempo = clock();
		
		
	}
	
	
	virtual void dibujar() = 0;
	virtual void borrar() = 0;
	int getX() { return x; }
	int getY() { return y; }
	
	
};

