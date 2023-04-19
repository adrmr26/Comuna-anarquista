#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

#define MAX_PALABRAS 45
#define MAX_TRABAJA 20
#define MAX_REQUIERE 25

// Función para agregar los "Trabaja" o "Requiere" a la lista de acciones de cada persona 
void agregar_palabra_listaAcciones(struct Persona *p, char *nueva_palabra) {

    if (p->cantidad_de_palabras >= MAX_PALABRAS) {
        printf("La lista de acciones está llena.\n");
        return;
    }
    p->listaAcciones = realloc(p->listaAcciones, (p->cantidad_de_palabras + 1) * sizeof(char*)); 
    p->listaAcciones[p->cantidad_de_palabras] = malloc(strlen(nueva_palabra) + 1);
    strcpy(p->listaAcciones[p->cantidad_de_palabras], nueva_palabra);
    p->cantidad_de_palabras++;
}

// Función para agregar nuevos structs Trabaja a la lista de Trabajas de la Persona.
void agregar_trabaja(struct Persona *p, int tiempo, int bateria){

    if (p->cantidad_trabaja >= MAX_TRABAJA) {
        printf("La lista de Trabajas está llena.\n");
        return;
    }
    p->trabaja = realloc(p->trabaja, (p->cantidad_trabaja + 1) * sizeof(struct Trabaja));
    p->trabaja[p->cantidad_trabaja].Bateria = bateria;
    p->trabaja[p->cantidad_trabaja].Tiempo = tiempo;
    p->cantidad_trabaja++;
}

// Función para agregar nuevos structs Requiere a la lista de Requieres de la Persona.
void agregar_requiere(struct Persona *p, char *area, int tiempo, int bateria){

    if (p->cantidad_requiere >= MAX_REQUIERE) {
        printf("La lista de Requieres está llena.\n");
        return;
    }
    p->requiere = realloc(p->requiere, (p->cantidad_requiere + 1) * sizeof(struct Requiere));
    strcpy(p->requiere[p->cantidad_requiere].Area, area);
    p->requiere[p->cantidad_requiere].Bateria = bateria;
    p->requiere[p->cantidad_requiere].Tiempo = tiempo;
    p->cantidad_requiere++;

}


//---------------------------------------------------------------------------------------

//++++++++ Ejemplo de como se ejecuta la función y cómo la estaba probando. ++++++++++++++

// Recuerde incluir las librerías necesarias  

int main() {

    struct Persona p;

    p.listaAcciones = malloc(0); /* Se inicializa el espacio de memoria*/
    p.trabaja = malloc(0);
    p.requiere = malloc(0);
    p.cantidad_de_palabras = 0; /* Se inicializan la cantidad de palabras */
    p.cantidad_trabaja = 0; /* Se inicializan la cantidad de Requiere */
    p.cantidad_requiere = 0; /* Se incializa la cantidad de Trabaja */ 

    /*Para llenar la lista de acciones*/ 
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

    printf("Lista de acciones:\n");
    for (int i = 0; i < p.cantidad_de_palabras; i++) {
        printf("%s\n", p.listaAcciones[i]);
    }

    for (int i = 0; i < p.cantidad_de_palabras; i++) {
        free(p.listaAcciones[i]);
    }
    free(p.listaAcciones); /*Hay que liberar la memoria */
    printf("\n");

    /*Para llenar la lista de Trabajas de la Persona */

    agregar_trabaja(&p, 80, 10);
    agregar_trabaja(&p, 90, 20);

    printf("Lista de trabajos:\n");
    for (int i = 0; i < p.cantidad_trabaja; i++) {
        printf("Trabaja %d - Tiempo: %d, Bateria: %d\n", i+1, p.trabaja[i].Tiempo, p.trabaja[i].Bateria);
    }
    free(p.trabaja);
    printf("\n");

    /*Para llenar la lista de Requiere de la Persona */

    agregar_requiere(&p, "Huerto", 10, 50);
    agregar_requiere(&p, "Taller", 20, 70);

    printf("Lista de Requieres:\n");
    for (int i = 0; i < p.cantidad_requiere; i++) {
        printf("Requiere %d - Área: %s, Tiempo: %d, Batería: %d\n", i+1, p.requiere[i].Area, p.requiere[i].Tiempo, p.requiere[i].Bateria);
    }

    free(p.requiere);
   

    return 0;
} 