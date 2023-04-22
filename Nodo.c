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

/*Nodo * eliminar_persona(Nodo * cola){
    cola->persona = NULL;
    cola->siguiente = NULL;
    free(cola);
};



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