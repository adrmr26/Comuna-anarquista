
struct Panel {
	int Bateria;
};

typedef struct Nodo {
	struct Persona *persona;
	struct Nodo *siguiente;
}Nodo;

typedef struct Cola {
	struct Nodo *primero;
	struct Nodo *ultimo;
}Cola;

struct Requiere {
	char Area[10];
	int Tiempo;
	int Bateria;
	Cola *cola_area;
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





