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


/// --- Enemigos --- ///
class Marciano : public ObjetoDibuja {
	
	
	bool vivo;
	
	char forma;
	
	
public:
	
	
	Marciano(int _x, int _y, int c, char f) : ObjetoDibuja(_x, _y, 2, c) {
		
		
		vivo = true; forma = f;
		
		
	}
	
	
	bool estaVivo() { return vivo; }
	
	void morir() { borrar(); vivo = false; }
	void dibujar() { if(vivo) { textcolor(color); putchxy(x, y, forma); } }
	void borrar() { putchxy(x, y, ' '); }
	
	void mover(int dx, int dy) {
		
		
		if(!vivo) return;
		borrar();
		x += dx; y += dy;
		dibujar();
		
		
	}
	
	
};


/// --- Juego --- ///
class Juego {
	
	
	Nave *p;
	Marciano *m[3][10];
	
	Proyectil b[5];
	ProyectilEnemigo be;
	
	int puntos, dir;
	clock_t tHorda;
	
	bool salirJuego;
	bool reiniciar;
	
	
	
public:
	
	
	Juego() {
		
		
		srand(time(NULL));
		p = new Nave();
		puntos = 0; dir = 1; salirJuego = false; reiniciar = false;
		tHorda = clock();
		
		
		for(int i=0; i<3; i++)
			for(int j=0; j<10; j++)
			m[i][j] = new Marciano(8+j*5, 4+i*2, (i==0?12:14), (i==0?'W':'X'));
			
			
	}
	
	
	void imprimirNumero(int x, int y, int num) {
		
		
		char buffer[10];
		sprintf(buffer, "%d", num);
		textcolor(15);
		for(int i=0; buffer[i] != '\0'; i++) putchxy(x+i, y, buffer[i]);
		
		
	}

	
	void dibujarMarco() {
		
		
		textcolor(15);
		
		for(int i=1; i<=70; i++) { putchxy(i, 2, '-'); putchxy(i, 24, '-'); }
		for(int i=2; i<=24; i++) { putchxy(1, i, '|'); putchxy(70, i, '|'); }
		
		
	}

	
	void pantallaInicio() {
		
		
		clrscr();
		
		dibujarMarco();
		
		
		textcolor(4); // Color Rojo  (Revisar y Verificar) //
		gotoxy(28, 8); cout << "SPACE INVADERS";
		
		
		textcolor(15); // Color Blanco (Revisar y Verificar) //
		gotoxy(20, 12); cout << "CONTROLES:";
		
		gotoxy(20, 14); cout << "TECLA A: IZQUIERDA";
		gotoxy(20, 15); cout << "TECLA D: DERECHA";
		gotoxy(20, 16); cout << "ESPACIO: DISPARAR, piu piu...";
		
		gotoxy(20, 18); cout << "EVITAR LOS DISPAROS ENEMIGOS";
		gotoxy(20, 19); cout << "SOBREVIVE Y ELIMINA A TODOS LOS ENEMIGOS";
		
		
		textcolor(2); // Color Verde (Revisar y Verificar) //
		gotoxy(20, 22); cout << "DALE, PRESIONA CUALQUIER TECLA PARA INICIAR...";
		
		
		getch(); 
		clrscr();
		
		
	}
	
	
	void dibujarInterfaz() {
		
		
		dibujarMarco();
		textcolor(10);
		
		gotoxy(2, 1); cout << "PUNTOS: ";
		imprimirNumero(10, 1, puntos);
		
		gotoxy(50, 1); cout << "VIDAS: ";
		imprimirNumero(57, 1, p->getVidas());
		
		
	}

	
	void gameOver() {
		
		
		clrscr();
		
		
		textcolor(12);
		gotoxy(30, 10); cout << "JUEGO TERMINADO";
		
		
		textcolor(2);
		gotoxy(25, 12); cout << "Puntos Finales: " << puntos;
		gotoxy(20, 14); cout << "ESC: Salir | M: Menu | R: Reiniciar";
		
		
		bool opcionValida = false;
		
		
		while(!opcionValida) {
			
			
			if(kbhit()) {
				
				
				int tec = getch();
				if(tec == 27) { salirJuego = true; opcionValida = true; }
				else if(tec == 'm' || tec == 'M') { opcionValida = true; }
				else if(tec == 'r' || tec == 'R') { reiniciar = true; opcionValida = true; }
				
				
			}
			
			
		}
		
		
	}
	
	
	void play() {
		
		
		pantallaInicio();
		
		p->dibujar();
		
		
		while(p->getVidas() > 0 && !salirJuego && !reiniciar) {
			if(kbhit()) {
				
				
				int tec = getch();
				if(tec == 'a' || tec == 'd') p->mover(tec);
				if(tec == ' ') {
					
					
					for(int i=0; i<5; i++) if(!b[i].estaActiva()) { b[i].disparar(p->getX(), p->getY()-1); break; }
					
					
				}
				
				
			}
			
			
			for(int i=0; i<5; i++) {
				
				if(b[i].estaActiva()) {
					
					
					b[i].update();
					
					for(int fi=0; fi<3; fi++)
						for(int co=0; co<10; co++)
						if(m[fi][co]->estaVivo() && b[i].getX() == m[fi][co]->getX() && b[i].getY() == m[fi][co]->getY()) {
						m[fi][co]->morir(); b[i].desactivar(); puntos += 100;
						
						
					}
				 
				}
			 
			}
			
			
			if(!be.estaActiva()) {
				
				
				int rF = rand() % 3;
				int rC = rand() % 10;
				if(m[rF][rC]->estaVivo()) {
					be.disparar(m[rF][rC]->getX(), m[rF][rC]->getY() + 1);
					
					
				}
				
				
			} else {
				
				be.update();
				if(be.getY() >= p->getY() && be.getY() <= p->getY()+1 && 
				   be.getX() >= p->getX()-1 && be.getX() <= p->getX()+1) {
					p->quitarVida();
					be.desactivar();
					
					
				}
				
				
			}
			
			
