#include <stdio.h>
#include "structs.h"


struct Nodo * agregar(struct Nodo *cola, struct Persona *valor){
    struct Nodo *temporal = calloc(sizeof(struct Nodo),1);
    struct Nodo *pivote;
    temporal->persona = valor;
    if (cola != NULL){
        pivote = cola;
        while (pivote->siguiente != NULL) { 
            pivote = pivote->siguiente;
        }
        pivote->siguiente = temporal; 
        return cola;
    }
    else{
        return temporal;

    }
};

struct Nodo * eliminar(struct Nodo * cola){
    cola->persona = NULL;
    cola->siguiente = NULL;
    free(cola);
};