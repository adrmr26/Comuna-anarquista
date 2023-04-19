//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>

#define MAX_PALABRAS 50

struct Persona {
    char **listaAcciones;
    int cantidad_de_palabras;
};

// Función para agregar los "Trabaja" o "Requiere" a la lista de acciones de cada persona 
void agregar_palabra_listaAcciones(struct Persona *p, char *nueva_palabra) {

    if (p->cantidad_de_palabras >= MAX_PALABRAS) {
        printf("La lista de strings está llena.\n");
        return;
    }
    p->listaAcciones = realloc(p->listaAcciones, (p->cantidad_de_palabras + 1) * sizeof(char*)); 
    p->listaAcciones[p->cantidad_de_palabras] = malloc(strlen(nueva_palabra) + 1);
    strcpy(p->listaAcciones[p->cantidad_de_palabras], nueva_palabra);
    p->cantidad_de_palabras++;
}

//---------------------------------------------------------------------------------------

//++++++++ Ejemplo de como se ejecuta la función y cómo la estaba probando. ++++++++++++++

// Recuerde incluir las librerías necesarias ********

/*
int main() {

    struct Persona p;

    p.listaAcciones = malloc(0); // Se inicializa el espacio de memoria
    p.cantidad_de_palabras = 0; // Se inicializan la cantidad de palabras 

    agregar_palabra_listaAcciones(&p, "Trabaja");
    agregar_palabra_listaAcciones(&p, "Requiere");
    agregar_palabra_listaAcciones(&p, "Trabaja");
    agregar_palabra_listaAcciones(&p, "Requiere");
    agregar_palabra_listaAcciones(&p, "Trabaja");
    agregar_palabra_listaAcciones(&p, "Requiere");
    agregar_palabra_listaAcciones(&p, "Trabaja");
    agregar_palabra_listaAcciones(&p, "Requiere");
    agregar_palabra_listaAcciones(&p, "Trabaja");
    agregar_palabra_listaAcciones(&p, "Requiere");
    agregar_palabra_listaAcciones(&p, "Trabaja");
    agregar_palabra_listaAcciones(&p, "Requiere");
    agregar_palabra_listaAcciones(&p, "Trabaja");
    agregar_palabra_listaAcciones(&p, "Requiere");

    printf("Lista de strings:\n");
    for (int i = 0; i < p.cantidad_de_palabras; i++) {
        printf("%s\n", p.listaAcciones[i]);
    }

    for (int i = 0; i < p.cantidad_de_palabras; i++) {
        free(p.listaAcciones[i]);
    }
    free(p.listaAcciones); // Hay que liberar la memoria

    return 0;
} */ 
