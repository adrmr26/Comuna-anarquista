#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structs.h"

void crear_cola(Cola *cola) {   
     cola -> primero = cola -> ultimo = NULL;
}
void insertar_persona(Cola *cola,struct Persona *persona){    
    Nodo *temporal ;    
    temporal = (Nodo*)malloc(sizeof(Nodo));    
    temporal -> persona = persona;    
    temporal -> siguiente = NULL;    
    if(cola -> primero == NULL)    {       
         cola -> primero = temporal;    
         }    
         else    {        
            cola -> ultimo -> siguiente = temporal;    
            }    
            cola -> ultimo = temporal;
}

int es_vacia (Cola *cola){
    if(cola->primero == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

void eliminar_persona (Cola *cola){
    Nodo * temporal;
    if (!es_vacia(cola)){
        temporal = cola -> primero;
        cola -> primero = cola -> primero -> siguiente;
        free(temporal);
    }
}

/*


struct Persona* consultar_persona (struct Cola* cola ){
    if (cola->primero){
        return cola->primero->persona;
    } else {
        return NULL;
    }
}*/

int main(){
    Cola colaPrincipal;
    Cola colaGym;
    crearCola(&colaPrincipal);
    printf("Cola creada principal\n");
    crearCola(&colaGym);
    printf("Cola creada gym\n");

}