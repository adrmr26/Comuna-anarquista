#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include "Nodo.c"

#define QUANTUM 80 // Definición  del quantum a 80 unidades de tiempo.

// Inicializacion de las colas de las áreas de la Comuna.
Cola *cola_principal; 
Cola *cola_Gym; 
Cola *cola_Recreacion;
Cola *cola_Taller;
Cola *cola_Farmacia;
Cola *cola_Biblioteca;
Cola *cola_Despensa;
Cola *cola_Huerto;


void agregarPersona_ColaArea(struct Persona *p){

	if(strcmp(p->requiere[0].Area, "Gym") ==0){
		p->requiere[0].cola_area = &cola_Gym;
		printf("PEPEPEE\n");
		insertar_persona(cola_Gym, p);
		printf("+++SALI DE INSERTAR PERSONA\n");
	}
	else if(strcmp(p->requiere[0].Area, "Recreacion") ==0){
		p->requiere[0].cola_area = &cola_Recreacion;
		insertar_persona(cola_Recreacion, p);
	}
	else if(strcmp(p->requiere[0].Area, "Taller") ==0){
		p->requiere[0].cola_area = &cola_Taller;
		insertar_persona(cola_Taller, p);
	}
	else if(strcmp(p->requiere[0].Area, "Farmacia") ==0){
		p->requiere[0].cola_area = &cola_Farmacia;
		insertar_persona(cola_Farmacia, p);	
	}
	else if(strcmp(p->requiere[0].Area, "Biblioteca") ==0){
		p->requiere[0].cola_area = &cola_Biblioteca;
		insertar_persona(cola_Biblioteca, p);
	}
	else if(strcmp(p->requiere[0].Area, "Despensa") ==0){
		p->requiere[0].cola_area = &cola_Despensa;
		insertar_persona(cola_Despensa, p);	
	}
	else if(strcmp(p->requiere[0].Area, "Huerto") ==0){
		p->requiere[0].cola_area = &cola_Huerto;
		insertar_persona(cola_Huerto, p);
	}	

}

// Algoritmo de planificación Round-Robin.
void round_robin(Cola *cola_principal, int bateria_comuna) {
	printf("Entré a la función\n");
    int tiempo_total = 0; // Para la métrica de tiempo promedio
	int tiempo_de_espera = 0; // Para la métrica de tiempo promedio
	int cantidad_tareas = 0; // Para la métrica de tiempo promedio
	int metrica_bateria = 0; // Para la métrica de uso de batería promedio.
	int bateria_gastada = 0; // Para la métrica de uso de batería promedio.
    int i = 0; // índice de las listas

    // Ejecutamos mientras haya personas en la cola principal. 
    while (cola_principal->primero != NULL) {
		struct Persona *p = cola_principal->primero->persona; 
		//Si lo primero en la lista de acciones de la persona es un Trabaja.
        if (strcmp(p->listaAcciones[i], "Trabaja" ) == 0) {
			printf("Estoy ejecutando un trabaja\n");
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
				printf("Ahora el tiempo total es de: %d\n", tiempo_total);
				printf("Ahora el tiempo de espera es de: %d\n", tiempo_de_espera);
				bateria_gastada = (floor((QUANTUM * (p->trabaja[i].Bateria))/p->trabaja[i].Tiempo));
				p->trabaja[i].Bateria -= bateria_gastada;
				metrica_bateria += bateria_gastada;
				bateria_comuna -= bateria_gastada;
				p->trabaja[i].Tiempo -= QUANTUM;
				// Si el primero NO es el único nodo en la cola principal entonces coloquelo al final. 
				if(cola_principal->primero->siguiente != NULL){
					printf("*****Entro en pasar al último de la cola principal\n");
					colocar_al_final(cola_principal, p);
					printf("++++++Ahora el primero de la cola tiene un tiempo de: %d\n", cola_principal->primero->persona->trabaja[i].Tiempo);
					printf("--------Ahora el ultimo de la cola tiene un tiempo de: %d\n", cola_principal->ultimo->persona->trabaja[i].Tiempo);
				}
			}
			// Si el tiempo es menor o igual al QUANTUM.
			else{
				printf("tiempo menor que el Quantum\n");
				tiempo_total += p->trabaja[i].Tiempo;
				printf("Ahora el tiempo de la tarea es de %d\n", p->trabaja[i].Tiempo);
				tiempo_de_espera += tiempo_total;
				cantidad_tareas += 1;
				printf("Ahora el tiempo total es de: %d\n",tiempo_total);
				printf("Ahora el tiempo de espera es de: %d\n", tiempo_de_espera);
				bateria_comuna -= p->trabaja[i].Bateria;
				metrica_bateria += p->trabaja[i].Bateria;
				printf("Ahora la batería total es de: %d\n",bateria_comuna);
				eliminarPalabra_listaAcciones(p,i);
				eliminar_trabaja(p,i);
				if(i > p->cantidad_de_palabras){
					eliminar_persona(cola_principal);
				}
			}

		}
		//Si lo primero en la lista de acciones de la persona es un Requiere.
		else{
			printf("Estoy ejecutando un Requiere\n");
			if(p->requiere[i].Bateria > bateria_comuna){
				sleep(3);
				bateria_comuna = 100;
			}
			// Si el tiempo es mayor al QUANTUM.
			if(p->requiere[i].Tiempo > QUANTUM){
				printf("*********Estoy en Requiere tiempo mayor al Quantum\n");
				if(p->requiere[i].cola_area == NULL){
					agregarPersona_ColaArea(p);
				}
				tiempo_total += QUANTUM;
				tiempo_de_espera += tiempo_total;
				cantidad_tareas += 1;
				bateria_gastada = (floor((QUANTUM * (p->requiere[i].Bateria))/p->requiere[i].Tiempo));
				p->requiere[i].Bateria -= bateria_gastada;
				metrica_bateria += bateria_gastada;
				bateria_comuna -= bateria_gastada;
				p->requiere[i].Tiempo -= QUANTUM;
				// Si el primero NO es el único nodo en la cola principal entonces coloquelo al final. 
				if(cola_principal->primero->siguiente != NULL){
					printf("*****Entro en pasar al último de la cola principal\n");
					colocar_al_final(cola_principal, p);
					printf("++++++Ahora el primero de la cola tiene un tiempo de: %d\n", cola_principal->primero->persona->trabaja[i].Tiempo);
					printf("--------Ahora el ultimo de la cola tiene un tiempo de: %d\n", cola_principal->ultimo->persona->trabaja[i].Tiempo);
				}
			}
			// Si el tiempo es menor o igual al QUANTUM.
			else{
				tiempo_total += p->requiere[i].Tiempo;
				tiempo_de_espera += tiempo_total;
				cantidad_tareas += 1;
				bateria_comuna -= p->requiere[i].Bateria;
				metrica_bateria += p->requiere[i].Bateria;
				eliminar_persona(p->requiere[i].cola_area);
				p->requiere[i].cola_area = NULL;
				eliminarPalabra_listaAcciones(p,i);
				eliminar_requiere(p,i);
				if(i > p->cantidad_de_palabras){
					eliminar_persona(cola_principal);
				}
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




int main(void){
	
	//Creacion de las colas de las areas de la comuna 
	crear_cola(&cola_principal);
	crear_cola(&cola_Gym);
	crear_cola(&cola_Recreacion);
	crear_cola(&cola_Taller);
	crear_cola(&cola_Farmacia);
	crear_cola(&cola_Biblioteca);
	crear_cola(&cola_Despensa);
	crear_cola(&cola_Huerto);


	struct Persona p;
	struct Persona p2;
	struct Persona p3;
	//int bateria_comuna = 100;

    p.listaAcciones = malloc(0); // Se inicializa el espacio de memoria
	p2.listaAcciones = malloc(0);
	p3.listaAcciones = malloc(0);
    
    p.trabaja = malloc(0);
	p.requiere = malloc(0);

	p2.trabaja = malloc(0);

	p3.trabaja = malloc(0);
	p3.requiere = malloc(0);
    //p.requiere = malloc(0);
    p.cantidad_de_palabras = 0; // Se inicializan la cantidad de palabras 
	p2.cantidad_de_palabras = 0; 
	p3.cantidad_de_palabras = 0; 

	p.cantidad_trabaja = 0; //Se incializan la cantidad de trabjas 
	p2.cantidad_trabaja = 0;
	p3.cantidad_trabaja = 0;

    p.cantidad_requiere = 0; // Se incializa la cantidad de Requiere
	
	agregar_trabaja(&p, 80, 10);
	agregar_palabra_listaAcciones(&p, "Trabaja");
    agregar_trabaja(&p, 90, 20);
	agregar_palabra_listaAcciones(&p, "Trabaja");
	agregar_requiere(&p, "Gym", 100, 10);
	agregar_palabra_listaAcciones(&p, "Requiere");

/*   // Persona 2
	agregar_trabaja(&p2, 100, 10);
	agregar_palabra_listaAcciones(&p2, "Trabaja");
	agregar_trabaja(&p2, 120, 20);
	agregar_palabra_listaAcciones(&p2, "Trabaja");

	//Persona 3
	agregar_trabaja(&p3, 90, 10);
	agregar_palabra_listaAcciones(&p3, "Trabaja");*/

	struct Persona *persona = &p;
	//struct Persona *persona2 =&p2;
	//struct Persona *persona3 =&p3;

	insertar_persona(&cola_principal, persona);
	//insertar_persona(&cola_principal, persona2);
	//insertar_persona(&cola_principal, persona3);

	round_robin(&cola_principal, 100);

	return 0;
}

