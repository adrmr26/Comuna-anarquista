#include <stdio.h>
#include "structs.h"


struct Nodo * agregar(struct Nodo *cola, /*valor persona*/){
    struct Nodo *temporal = calloc(sizeof(struct Nodo),1);
    struct Nodo *pivote;
    temporal->/*el objeto persona*/ = valor;
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