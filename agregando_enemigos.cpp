#include <iostream>
#include <conio2.h>
#include <windows.h>
#include <cstdio>
#include <climits>
#include <cstdlib>
#include <ctime>


using namespace std;


/// --- Primera Clase --- ///
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


/// --- Proyectil de Disparo ; Jugador --- ///
class Proyectil : public ObjetoDibuja {
	
	
	bool activa;
	

public:
	
	
	Proyectil() : ObjetoDibuja(0, 0, 25, 15) { activa = false; }
	
	void disparar(int _x, int _y) { x = _x; y = _y; activa = true; }
	
	bool estaActiva() { return activa; }
	
	void desactivar() { borrar(); activa = false; }
	void dibujar() { if(activa) { textcolor(color); putchxy(x, y, '|'); } }
	void borrar() { putchxy(x, y, ' '); }
	void update() {
		
		
		if (!activa) return;
		
		if (clock() > tempo + paso) {
			borrar();
			y--;
			if (y < 3) activa = false;
			else dibujar();
			tempo = clock();
			
			
		}
		
		
	}
	
	
};


/// --- Proyectil de los Enemigos --- ///
class ProyectilEnemigo : public ObjetoDibuja {
	
	
	bool activa;
	
	
public:
	
	
	ProyectilEnemigo() : ObjetoDibuja(0, 0, 10, 12) { activa = false; }
	
	void disparar(int _x, int _y) { x = _x; y = _y; activa = true; }
	
	bool estaActiva() { return activa; }
	
	void desactivar() { borrar(); activa = false; }
	void dibujar() { if(activa) { textcolor(color); putchxy(x, y, 'v'); } }
	void borrar() { putchxy(x, y, ' '); }
	void update() {
		
		
		if (!activa) return;
		
		if (clock() > tempo + paso) {
			
			
			borrar();
			y++;
			if (y > 23) activa = false;
			else dibujar();
			tempo = clock();
			
			
		}
		
		
	}
	
	
};


/// --- Nave Jugador --- ///
class Nave : public ObjetoDibuja {
	
	
	int vidas;
	
	
public:
	
	
	Nave() : ObjetoDibuja(35, 22, 0, 10) { vidas = 3; }
	int getVidas() { return vidas; }
	
	void quitarVida() { vidas--; }
	void dibujar() {
		
		
		textcolor(color);
		putchxy(x, y, '^');
		putchxy(x-1, y+1, '/'); putchxy(x, y+1, 'M'); putchxy(x+1, y+1, '\\');
		
		
	}
	
	
	void borrar() {
		
		
		putchxy(x, y, ' ');
		putchxy(x-1, y+1, ' '); putchxy(x, y+1, ' '); putchxy(x+1, y+1, ' ');
		
		
	}
	
	
	void mover(int t) {
		
		
		borrar();
		if (t == 'a' && x > 3) x--;
		if (t == 'd' && x < 67) x++;
		dibujar();
		
		
	}
	
	
};


// --- Enemigos --- //
class Marciano : public ObjetoDibuja {
	
	
	bool vivo;
	char forma;
	
	
