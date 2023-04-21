#include<stdio.h>

struct Panel {
	int Bateria;
};

struct Requiere {
	char Area[10];
	int Tiempo;
	int Bateria;
};

struct Trabaja{
	int Tiempo;
	int Bateria;
};

struct Persona {
    char **listaAcciones;
    struct Trabaja *trabaja;
    struct Requiere *requiere;
    int cantidad_de_palabras;
    int cantidad_trabaja;
    int cantidad_requiere;
};

struct Nodo {
	struct Persona *persona;
	struct Nodo *siguiente;
};

struct Cola {
	struct Nodo *primero;
	struct Nodo *ultimo;
};

