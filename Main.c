#include <stdio.h>
#include <unistd.h>
#include "structs.h"

#define QUANTUM 80 // Definición  del quantum a 2 unidades de tiempo.


// Algoritmo de planificación Round-Robin.
void round_robin(struct Cola *cola_principal, int *bateria_comuna) {
    int tiempo_total = 0;
    int i = 0;
	int j = 0; 

    // Ejecutamos mientras haya personas en la cola principal. 
    while (cola_principal->primero != NULL) {
		struct Persona *p = cola_principal->primero->persona; 
		//Si lo primero en la lista de acciones de la persona es un Trabaja.
        if (strcmp(p->listaAcciones[i], "Trabaja") == 0) {
			if(p->trabaja[i].Bateria > bateria_comuna){
				sleep(3);
				bateria_comuna = 100;
			}
			// Si el tiempo es mayor al QUANTUM.
			if(p->trabaja[i].Tiempo > QUANTUM){
				tiempo_total += QUANTUM;
				p->trabaja[i].Tiempo -= QUANTUM;
				i = 0;
				cola_principal->ultimo = cola_principal->primero;
				cola_principal->primero = cola_principal->primero->siguiente;
			}
			// Si el tiempo es menor o igual al QUANTUM.
			else{
				tiempo_total += p->trabaja[i].Tiempo;
				eliminarPalabra_listaAcciones(p,i);
				eliminar_trabaja(p,i);
				eliminar_persona(cola_principal->primero);
				i++;
			}

		}
		//Si lo primero en la lista de acciones de la persona es un Requiere.
		else{
			round_robin_auxRequiere();
		}

	}
}

void round_robin_auxRequiere(){
	/*FALTA*/
}

int main(){
	struct Panel P = {100};
	struct Requiere s1 ={"Gym",12,11};
	
	
	printf("%s %d %d", s1.Area, s1.Bateria, s1.Tiempo);
	return 0;
}
