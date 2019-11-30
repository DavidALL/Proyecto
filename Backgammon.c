#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Elem.h"
#include "Bicola.h"
#define true 1
#define false 0

void inicializa(Bicola);
void draw(Bicola);
int decideturno(void);
void tirardados(int *, int *);
int disponible(Bicola, int, int, int);
int pedirlugar(Bicola, int);
int pedirespacios(Bicola, int, int, int, int);
void actualizar(Bicola, int, int, int);
int haycomidas(Bicola, int);
int anymove(Bicola, int, int, int);
int moves(Bicola, int, int, int, int);
void todascuarto(Bicola, int);
int ganador(Bicola);
int cambiarturno(int);
int absoluto(int);
int cc1 = 0, cc2 = 0;

int main(int argc, char const *argv[]) {
	
	Bicola pos = nuevab();
	int d1, d2, daux;
	int turno;
	int fich_mov, esp_mov; //ficha y espacios a mover
	char s, r;
	
	inicializa(pos);
	srand(time(NULL));

	limp();
	turno = decideturno();
	puts("Presiona ENTER para comenzar...");
	esperar();

	while(true) {
		
		if(turno == 1) 
			s = '#';
		else
			s= '*';

		limp();
		draw(pos);
		printf("Jugador %c: presiona ENTER para tirar dados.\n", s);
		esperar();
		tirardados(&d1, &d2);

		if(!anymove(pos, d1, d2, turno)) {
			printf("No hay movimientos posibles.\n");
			esperar();
			turno = cambiarturno(turno);
			continue;
		}
		
		if(d1 != d2)
			r = 1;
		else
			r = 2;

		for(int j=0; j<r; j++) {
			if(r == 2) {
				if(j == 0) {
					daux = d1;
				}
				else {
					d1 = daux;
					d2 = daux;
				}
			}
			for(int i=0;i<2;i++) {
				printf("%c. Tus numeros son:\n", s);
				printf("%d y %d\n", d1, d2);
				
				while(true) {
					fich_mov = pedirlugar(pos, turno);

					if(!moves(pos, d1, d2, fich_mov, turno)) 
						printf("No hay movimientos posibles para esta ficha, intenta otra.\n");
					else
						break;

				} 

				esp_mov = pedirespacios(pos, fich_mov, d1, d2, turno);				

				if(esp_mov == d1) d1 = 0;
				else d2 = 0;

				actualizar(pos, fich_mov, esp_mov, turno);
				todascuarto(pos, turno);
				if(ganador(pos))
					goto gana;
				limp();
				draw(pos);
			}
		}

		turno = cambiarturno(turno);
	}

	gana: puts("Fin del juego.");

	if(datoDI(27, pos) == 15)
		puts("El jugador de fichas #, gana la partida.");
	else if(datoDI(28, pos) == -15)
		puts("El jugador de fichas *, gana la partida.");
	else
		puts("Empate?");

	return 0;
}

int ganador(Bicola dq) {
	if(datoDI(27, dq) == 15)
		return true;
	else if(datoDI(28, dq) == -15)
		return true;
	else 
		return false;
}

void tirardados(int *d1, int *d2) {
	*d1 = rand()%6+1;
	*d2 = rand()%6+1;
}

int absoluto(int a) {
	if(a >= 0) 
		return a;
	else
		return -a;
}

int cambiarturno(int turno) {
	if(turno == 1)
		return 2;
	else
		return 1;
}

int decideturno(void) {
	int d1, d2;
	while(true) {
		limp();
		puts("Jugador #: Presiona ENTER para tirar dado...");
		esperar();
		d1 = rand()%6+1;
		printf("# Tu resultado es: %d\n", d1);
		puts("\n\nJugador *: Presiona ENTER para tirar dado...");
		esperar();
		d2 = rand()%6+1;
		printf("* Tu resultado es: %d\n\n\n", d2);
		if(d1 == d2) 
			puts("Resultados iguales, repite.");
		else
			break;
		esperar();
	}

	if(d1 > d2) {
		puts("Comienza jugador con fichas #.");
		return 1;
	}
	else {
		puts("Comienza jugador con fichas *.");
		return 2;
	} 
}

void inicializa(Bicola dq) {
	int valor, i;
	for(i=1; i<=24+4; i++) {
		if(i == 1)
			valor = -2;
		else if(i == 2)
			valor = -2;
		else if(i == 3)
			valor = -1;
		else if(i == 4)
			valor = -3;
		else if(i == 5)
			valor = -1;
		else if(i == 6)
			valor = -6;
		else if(i == 19)
			valor = 5;
		else if(i == 20)
			valor = 4;
		else if(i == 21)
			valor = 3;
		else if(i == 22)
			valor = 1;
		else if(i == 23)
			valor = 1;
		else if(i == 24)
			valor = 1;
		else
			valor = 0;

		dq = formari(valor, dq);
	}
}

int haycomidas(Bicola dq, int turno) {
	if(turno == 1 && datoDI(25, dq) != 0)
		return true;
	else if(turno == 2 && datoDI(26, dq) != 0)
		return true;
	else return false;
}

void todascuarto(Bicola dq, int turno) {
	int i, count = 0;
	if(turno == 1) {
		for(i = 19; i <= 24; i++) {
			if(datoDI(i, dq) > 0)
				count += datoDI(i, dq);
		}
		if(count == 15)
			cc1 = 1;
	}
	else {
		for(i = 19+4; i <= 24+4; i++) {
			if(datoID(i, dq) < 0)
				count += datoID(i, dq);
		}
		if(count == -15)
			cc2 = 1;
	}
}

int pedirlugar(Bicola dq, int turno) {
	int fich_mov;

	while(true) {
		printf("Escribe el numero de ficha a mover: ");
		scanf("%d", &fich_mov);
		
		if(haycomidas(dq, turno)) {
			if(turno==1 && fich_mov==25) {
				fich_mov = 0;
				break;
			}
			else if(turno == 2 && fich_mov==26) {
				fich_mov = 25;
				break;
			}
			else {
				printf("Primero debes sacar la comida.\n");
			}
		}
		else if(turno == 1 && datoDI(fich_mov, dq) > 0)
				break;
		else if(turno == 2 && datoDI(fich_mov, dq) < 0) 
				break;
		else
			printf("Posición invalida.\n");
	}

	return fich_mov;

}

int pedirespacios(Bicola dq, int indice, int d1, int d2, int turno) {
	int esp_mov, i;

	while(true) {
		printf("Elige un numero: ");
		scanf("%d", &esp_mov);

		if(esp_mov == d1 || esp_mov == d2) {
			if(esp_mov == 0)
				printf("Numero invalido.\n");
				
			else if(disponible(dq, indice, esp_mov, turno))
				break;

			else
				printf("Numero no disponible.\n");
		}
		else 
			printf("No coincide el numero.\n");
	}

	return esp_mov;
}

int disponible(Bicola dq, int indice, int esp_mov, int turno) {
	int i;
	if(turno == 1) {
		i = indice + esp_mov;
		if(i > 24) {
			if(cc1 == 1)
				return 1;
			else
				return 0;
		}
		else if(datoDI(i, dq) >= 0 || datoDI(i, dq) == -1)
			return 1;
		else return 0;
	}
	else {
		i = indice - esp_mov;
		if(i < 1) {
			if(cc2 == 1)
				return 1;
			else
				return 0;
		}
		else if(datoDI(i, dq) <= 0 || datoDI(i, dq) == 1)
			return 1;
		else return 0;
	}
}

int anymove(Bicola dq, int d1, int d2, int turno) {
	int final = 0;

	if(haycomidas(dq, turno)) {
		if(turno == 1) {
			if(disponible(dq, 0, d1, 1) || disponible(dq, 0, d2, 1))
				final = 1;
		}
		else {
			if(disponible(dq, 25, d1, 2) || disponible(dq, 25, d2, 2))
				final = 1;
		}
	}

	for(int i = 1; i <=24; i++) {
		if(turno == 1 && datoDI(i, dq) > 0) {
			if((disponible(dq, i, d1, 1) && d1 != 0) || (disponible(dq, i, d2, 1) && d2 != 0)) {
				final = 1;
				break;
			}
		}
		else if(turno == 2 && datoDI(i, dq) < 0) {
			if((disponible(dq, i, d1, 2) && d1 != 0) || (disponible(dq, i, d2, 2) && d2 != 0)) {
				final = 1;
				break;
			}
		}
	}
	return final;	
}

int moves(Bicola dq, int d1, int d2, int pos, int turno) {
	int final = 0;
	if((turno == 1 && cc1 == 1) || (turno == 2 && cc2 == 1))
		final = 1;
	else if(turno == 1) {
		if((disponible(dq, pos, d1, turno) && d1 != 0) || (disponible(dq, pos, d2, turno) && d2 != 0)) 
			final = 1;
	}
	else {
		if((disponible(dq, pos, d1, turno) && d1 != 0) || (disponible(dq, pos, d2, turno) && d2 != 0))
			final = 1;
	}
	return final;
}

void actualizar(Bicola dq, int fich_mov, int esp_mov, int turno) {
	int new;
	if(turno == 1) {
		new = fich_mov + esp_mov;
		if(fich_mov == 0) {
			EscDI(25, datoDI(25, dq)-1, dq);
			if(datoDI(new, dq) == -1) {
				EscDI(new, 1, dq);
				EscDI(26, datoDI(26, dq)-1, dq);
			}
			else {
				EscDI(new, datoDI(new, dq)+1, dq);
			}	
		}
		else {
			EscDI(fich_mov, datoDI(fich_mov, dq)-1, dq);
			if(new > 24)
				EscDI(27, datoDI(27, dq)+1, dq);
			else if(datoDI(new, dq) == -1) {
				EscDI(new, 1, dq);
				EscDI(26, datoDI(26, dq)-1, dq); //mandar al cementerio un *
			}
			else {
				EscDI(new, datoDI(new, dq)+1, dq);
			}
		} 
	}
	else {
		new = fich_mov-esp_mov;
		if(fich_mov == 25) { //estaba en el cementerio?
			EscDI(26, datoDI(26, dq)+1, dq);
			if(datoDI(new, dq) == 1) { //come?
				EscDI(new, -1, dq);
				EscDI(25, datoDI(25, dq)+1, dq);
			}
			else {
				EscDI(new, datoDI(new, dq)-1, dq);
			}
		}
		else {
			EscDI(fich_mov, datoDI(fich_mov, dq)+1, dq);
			if(new < 1)
				EscDI(28, datoDI(28, dq)+1, dq);
			else if(datoDI(new, dq) == 1) { //come?
				EscDI(new, -1, dq);
				EscDI(25, datoDI(25, dq)+1, dq);
			}
			else {
				EscDI(new, datoDI(new, dq)-1, dq);
			}
		} 
	}
}

void draw(Bicola dq) {
	register int i, j;
	char s; 
	ApNodo cent;
	Bicola aux;

	printf("    13 14 15 16 17 18   26    19 20 21 22 23 24\n");
	printf("   _____________________________________________\n");
	
	for(j=1; j<=5; j++) {
		printf("  |  ");
		for(i=13; i<=18; i++) {
			if(datoDI(i, dq) == 0 || absoluto(datoDI(i, dq)) < j) {
				s = ' ';
			}
			else {
				if(datoDI(i, dq) < 0)
					s = '*';
				else if(datoDI(i, dq) > 0)
					s = '#';
			}
			printf("%c  ", s);
		}

		printf("| ");
		if(absoluto(datoDI(26, dq)) >= j)
			printf("*");
		else
			printf(" ");
		printf(" |  ");

		for(i=19; i<=24; i++) {
			if(datoDI(i, dq) == 0 || absoluto(datoDI(i, dq)) < j) {
				s = ' ';
			}
			else {
				if(datoDI(i, dq) < 0)
					s = '*';
				else if(datoDI(i, dq) > 0)
					s = '#';
			}
			printf("%c  ", s);
		}
		printf("| ");
		if(absoluto(datoDI(27, dq)) >= j)
			printf("#");
		printf("\n");
	}

	printf("  |  ");
	for(i=13; i<=18; i++) {
		if(absoluto(datoDI(i, dq)) > 5)
			printf("%d  ", absoluto(datoDI(i, dq)));
		else
			printf("   ");
	}
	printf("|   |  ");
	for(i=19; i<=24; i++) {
		if(absoluto(datoDI(i, dq)) > 5)
			printf("%d  ", absoluto(datoDI(i, dq)));
		else
			printf("   ");		
	}
	printf("| ");
	if(absoluto(datoDI(27, dq)) > 5)
		printf("%d", absoluto(datoDI(27, dq)));
	printf("\n");
	
	printf("  |  -  -  -  -  -  -  |   |  -  -  -  -  -  -  |\n");

	printf("  |  ");
	for(i=13+4; i<=18+4; i++) {
		if(absoluto(datoID(i, dq)) > 5)
			printf("%d  ", absoluto(datoID(i, dq)));
		else
			printf("   ");
	}
	printf("|   |  ");
	for(i=19+4; i<=24+4; i++) {
		if(absoluto(datoID(i, dq)) > 5)
			printf("%d  ", absoluto(datoID(i, dq)));
		else
			printf("   ");		
	}
	printf("|");

	if(absoluto(datoDI(28, dq)) > 5)
		printf("%d", absoluto(datoDI(28, dq)));
	printf("\n");
	
	for(j=5; j>=1; j--) {
		printf("  |  ");
		for(i=13+4; i<=18+4; i++) {
			if(datoID(i, dq) == 0 || absoluto(datoID(i, dq)) < j) {
				s = ' ';
			}
			else {
				if(datoID(i, dq) < 0)
					s = '*';
				else if(datoID(i, dq) > 0)
					s = '#';
			}
			printf("%c  ", s);
		}

		printf("| ");
		if(datoDI(25, dq) != 0 && absoluto(datoDI(25, dq)) >= j)
			printf("#");
		else
			printf(" ");
		printf(" |  ");

		for(i=19+4; i<=24+4; i++) {
			if(datoID(i, dq) == 0 || absoluto(datoID(i, dq)) < j) {
				s = ' ';
			}
			else {
				if(datoID(i, dq) < 0)
					s = '*';
				else if(datoID(i, dq) > 0)
					s = '#';
			}
			printf("%c  ", s);
		}
		printf("|");
		if(absoluto(datoDI(28, dq)) >= j)
			printf("*");
		printf("\n");
	}

	printf("  _____________________|___|_____________________\n");
	printf("    12 11 10  9  8  7   25    6  5  4  3  2  1  \n");
}
