#include <stdio.h>
#include <unistd.h>
#include "structs.h"

#define QUANTUM 80 // Definición  del quantum a 2 unidades de tiempo.

int main(){
	struct Panel P = {100};
	struct Requiere s1 ={"Gym",12,11};
	struct Nodo *colaPrincipal = NULL;
	struct Nodo *colaGym = NULL;
	struct Nodo *colaCulto = NULL;
	struct Nodo *colaRecreacion = NULL;
	struct Nodo *colaBiblioteca = NULL;
	struct Nodo *colaTaller = NULL;
	struct Nodo *colaFarmacia = NULL;
	struct Nodo *colaDespensa = NULL;
	struct Nodo *colaHuerto = NULL;
	
	printf("%s %d %d", s1.Area, s1.Bateria, s1.Tiempo);
	return 0;
}


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


// Función principal del programa
int main() {
    // Creamos una cola de actividades de ejemplo
    struct actividad *cola = NULL;
    int tam = 0;
    agregar_actividad(&cola, 0, 5, &tam);
    agregar_actividad(&cola, 1, 3, &tam);
    agregar_actividad(&cola, 2, 4, &tam);
    agregar_actividad(&cola, 4, 2, &tam);
    agregar_actividad(&cola, 6, 1, &tam);

    // Ejecutamos la calendarización Round-Robin en la cola de actividades
    round_robin(cola, tam);

    // Liberamos la memoria de la cola de actividades
    free(cola);

    return 0;
}

