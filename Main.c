#include <stdio.h>
#include <unistd.h>
#include <math.h>
//#include "structs.h"
#include "Nodo.c"

#define QUANTUM 80 // Definición  del quantum a 80 unidades de tiempo.

// Creación de las colas de las áreas de la Comuna.
struct Cola *cola_Gym; 
struct cola *cola_Recreacion;
struct cola *cola_Taller;
struct cola *cola_Farmacia;
struct cola *cola_Biblioteca;
struct cola *cola_Despensa;
struct cola *cola_Huerto;

// Algoritmo de planificación Round-Robin.
void round_robin(struct Cola *cola_principal, int bateria_comuna) {
	printf("Entré a la función)");
    int tiempo_total = 0; // Para la métrica de tiempo promedio
	int tiempo_de_espera = 0; // Para la métrica de tiempo promedio
	int cantidad_tareas = 0; // Para la métrica de tiempo promedio
	int metrica_bateria = 0; // Para la métrica de uso de batería promedio.
    int i = 0; 

    // Ejecutamos mientras haya personas en la cola principal. 
    while (cola_principal->primero != NULL) {
		struct Persona *p = cola_principal->primero->persona; 
		//Si lo primero en la lista de acciones de la persona es un Trabaja.
        if (strcmp(p->listaAcciones[i], "Trabaja") == 0) {
			if(p->trabaja[i].Bateria > bateria_comuna){ // La batería de un trabajo no puede pasar de 100
				sleep(3);
				bateria_comuna = 100; 
			}
			// Si el tiempo es mayor al QUANTUM.
			if(p->trabaja[i].Tiempo > QUANTUM){
				printf("tiempo mayor que el quantum\n");
				tiempo_total += QUANTUM;
				tiempo_de_espera += tiempo_total;
				cantidad_tareas += 1;
				printf("Ahora el tiempo total es de: %d\n",tiempo_total);
				p->trabaja[i].Tiempo -= QUANTUM;
				i = 0;
				cola_principal->ultimo = cola_principal->primero;
				cola_principal->primero = cola_principal->primero->siguiente;
			}
			// Si el tiempo es menor o igual al QUANTUM.
			else{
				printf("tiempo menor que el Quantum \n");
				tiempo_total += p->trabaja[i].Tiempo;
				tiempo_de_espera += tiempo_total;
				cantidad_tareas += 1;
				printf("Ahora el tiempo total es de: %d\n",tiempo_total);
				bateria_comuna -= p->trabaja[i].Bateria;
				metrica_bateria += p->trabaja[i].Bateria;
				printf("Ahora la batería total es de: %d\n",bateria_comuna);
				eliminarPalabra_listaAcciones(p,i);
				eliminar_trabaja(p,i);
				eliminar_persona(cola_principal->primero);
				i++;
			}

		}
		//Si lo primero en la lista de acciones de la persona es un Requiere.
		else{
			printf("Me salí del Trabaja\n");
			if(p->requiere[i].Bateria > bateria_comuna){
				sleep(3);
				bateria_comuna = 100;
			}
			// Si el tiempo es mayor al QUANTUM.
			if(p->requiere[i].Tiempo > QUANTUM){
				agregarPersona_ColaArea(p, p->requiere[i]);
				tiempo_total += QUANTUM;
				tiempo_de_espera += tiempo_total;
				cantidad_tareas += 1;
				p->requiere[i].Tiempo -= QUANTUM;
				i = 0;
				cola_principal->ultimo = cola_principal->primero;
				cola_principal->primero = cola_principal->primero->siguiente;
			}
			// Si el tiempo es menor o igual al QUANTUM.
			else{
				tiempo_total += p->requiere[i].Tiempo;
				tiempo_de_espera += tiempo_total;
				cantidad_tareas += 1;
				bateria_comuna -= p->requiere[i].Bateria;
				metrica_bateria += p->requiere[i].Bateria;
				eliminar_persona_colaArea(p->requiere[i].cola_area, p);
				eliminarPalabra_listaAcciones(p,i);
				eliminar_requiere(p,i);
				eliminar_persona(cola_principal->primero);
				i++;
			}
					
		}

	}
	 // Cálculo de métrica de tiempo de espera promedio.
	int tiempoEspera_promedio = round(tiempo_de_espera/cantidad_tareas);
	printf("Tiempo de espera promedio = %d\n", tiempoEspera_promedio);
	// Cálculo de métrica de uso de batería proemdio.
	int usoDeBateria_promedio = round(metrica_bateria / cantidad_tareas);
	printf("Uso de Bateria promedio = %d\n", usoDeBateria_promedio);
}

void agregarPersona_ColaArea(struct Persona *p, struct Requiere requiere){
	if(strcmp(requiere.Area, "Gym") ==0){
		requiere.cola_area = &cola_Gym;
		// Si la persona ya está en la cola entonces no haga nada
		// Si no está, entonces agregue la persona a la cola con la función de agregar_persona de Nodo.c
	}
	else if(strcmp(requiere.Area, "Recreacion") ==0){
		requiere.cola_area = &cola_Recreacion;
		// Si la persona ya está en la cola entonces no haga nada
		// Si no está, entonces agregue la persona a la cola con la función de agregar_persona de Nodo.c

	}
	else if(strcmp(requiere.Area, "Taller") ==0){
		requiere.cola_area = &cola_Taller;
		// Si la persona ya está en la cola entonces no haga nada
		// Si no está, entonces agregue la persona a la cola con la función de agregar_persona de Nodo.c

	}
	else if(strcmp(requiere.Area, "Farmacia") ==0){
		requiere.cola_area = &cola_Farmacia;
		// Si la persona ya está en la cola entonces no haga nada
		// Si no está, entonces agregue la persona a la cola con la función de agregar_persona de Nodo.c

	}
	else if(strcmp(requiere.Area, "Biblioteca") ==0){
		requiere.cola_area = &cola_Biblioteca;
		// Si la persona ya está en la cola entonces no haga nada
		// Si no está, entonces agregue la persona a la cola con la función de agregar_persona de Nodo.c

	}
	else if(strcmp(requiere.Area, "Despensa") ==0){
		requiere.cola_area = &cola_Despensa;
		// Si la persona ya está en la cola entonces no haga nada
		// Si no está, entonces agregue la persona a la cola con la función de agregar_persona de Nodo.c
	}
	else if(strcmp(requiere.Area, "Huerto") ==0){
		requiere.cola_area = &cola_Huerto;
		// Si la persona ya está en la cola entonces no haga nada
		// Si no está, entonces agregue la persona a la cola con la función de agregar_persona de Nodo.c
	}

}

void eliminar_persona_colaArea(struct Cola *area, struct Persona *p){
	// se elimina la persona de la cola del área
}


int main(){
	
	//Inicialización de las colas de las áreas de la comuna. 
	cola_Gym = crear_colas();
	cola_Recreacion = crear_colas();;
	cola_Taller = crear_colas();
	cola_Farmacia = crear_colas();
	cola_Biblioteca = crear_colas();
	cola_Despensa = crear_colas();
	cola_Huerto = crear_colas();

	struct Persona p;
	struct Nodo *nodo;
	//int bateria_comuna = 100;

    p.listaAcciones = malloc(0); // Se inicializa el espacio de memoria
    
    p.trabaja = malloc(0);
    //p.requiere = malloc(0);
    p.cantidad_de_palabras = 0; // Se inicializan la cantidad de palabras 
    p.cantidad_trabaja = 0; // Se inicializan la cantidad de Requiere
    //p.cantidad_requiere = 0; // Se incializa la cantidad de Trabaja 
	
	agregar_palabra_listaAcciones(&p, "Trabaja");
	agregar_trabaja(&p, 80, 10);
	agregar_palabra_listaAcciones(&p, "Trabaja");
    agregar_trabaja(&p, 90, 20);

	printf("Todo bien hasta acá\n");

	//agregar_persona(&nodo, &p);

	struct Cola *cola_general = crear_colas();
	cola_general->primero = nodo;


	round_robin(cola_general, 100);

	return 0;
}
