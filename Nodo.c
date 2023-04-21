#include <stdio.h>
#include "Persona.c"


Nodo * agregar_persona(Nodo *cola, struct Persona *valor){
    Nodo *temporal = calloc(sizeof(struct Nodo),1);
    Nodo *pivote;
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

Nodo * eliminar_persona(Nodo * cola){
    cola->persona = NULL;
    cola->siguiente = NULL;
    free(cola);
};

Cola * crear_colas() {
    Cola * cola = (Cola *) malloc(sizeof(Cola));
    cola -> primero = cola->ultimo = NULL;
    return cola;
};

struct Persona* consultar_persona (struct Cola* cola ){
    if (cola->primero){
        return cola->primero->persona;
    } else {
        return NULL;
    }
}

/*
int main() {
  
    //Cola cola; 
    crear_colas();
    printf("Cola creada");
   
    return 0;
}*/