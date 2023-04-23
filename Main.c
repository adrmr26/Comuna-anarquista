#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>
#include <math.h>
#include <string.h>
#include "Nodo.c"

#define QUANTUM 80 // Definición  del quantum a 80 unidades de tiempo.
double promedio_espera = 0.0;
double promedio_bateria = 0.0;
int bateria_comuna = 100;


// Inicializacion de las colas de las áreas de la Comuna.
Cola cola_principal; 
Cola cola_Gym;
Cola cola_Recreacion;
Cola cola_Taller;
Cola cola_Farmacia;
Cola cola_Biblioteca;
Cola cola_Despensa;
Cola cola_Huerto;


void agregarPersona_ColaArea(struct Persona *p){

	if(strcmp(p->requiere[0].Area, "Gym") == 0){
		p->requiere[0].cola_area = &cola_Gym;
		insertar_persona(&cola_Gym, p);
		printf("*** Se insertó la persona en la cola GYM ***\n");
	}
	else if(strcmp(p->requiere[0].Area, "Recreacion") == 0){
		p->requiere[0].cola_area = &cola_Recreacion;
		insertar_persona(&cola_Recreacion, p);
		printf("*** Se insertó la persona en la cola RECREACION ***\n");
	}
	else if(strcmp(p->requiere[0].Area, "Taller") == 0){
		p->requiere[0].cola_area = &cola_Taller;
		insertar_persona(&cola_Taller, p);
		printf("*** Se insertó la persona en la cola TALLER ***\n");
	}
	else if(strcmp(p->requiere[0].Area, "Farmacia") == 0){
		p->requiere[0].cola_area = &cola_Farmacia;
		insertar_persona(&cola_Farmacia, p);
		printf("*** Se insertó la persona en la cola FARMACIA ***\n");	
	}
	else if(strcmp(p->requiere[0].Area, "Biblioteca") == 0){
		p->requiere[0].cola_area = &cola_Biblioteca;
		insertar_persona(&cola_Biblioteca, p);
		printf("*** Se insertó la persona en la cola BIBLIOTECA ***\n");
	}
	else if(strcmp(p->requiere[0].Area, "Despensa") == 0){
		p->requiere[0].cola_area = &cola_Despensa;
		insertar_persona(&cola_Despensa, p);
		printf("*** Se insertó la persona en la cola DESPENSA ***\n");	
	}
	else if(strcmp(p->requiere[0].Area, "Huerto") == 0){
		p->requiere[0].cola_area = &cola_Huerto;
		insertar_persona(&cola_Huerto, p);
		printf("*** Se insertó la persona en la cola HUERTO ***\n");
	}
	else{
		printf("ERROR: El área no se encuentra en la Comuna\n");
	}	
}

// Algoritmo de planificación Round-Robin.
void round_robin(Cola *cola_principal, int bateria_comuna) {
	printf("Entré a la función Round Robin\n");
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
			printf("Estoy ejecutando un Trabaja\n");
			if(p->trabaja[i].Bateria > bateria_comuna){ // La batería de un trabajo no puede pasar de 100
				printf("+++ Haciendo espera de 3 segundos para recargar la batería +++\n");
				sleep(3);
				bateria_comuna = 100; 
			}
			// Si el tiempo es mayor al QUANTUM.
			if(p->trabaja[i].Tiempo > QUANTUM){
				printf("TRABAJA: tiempo mayor que el Quantum\n");
				tiempo_total += QUANTUM;
				tiempo_de_espera += tiempo_total;
				cantidad_tareas += 1;
				printf("Ahora el tiempo total es de: %d\n", tiempo_total);
				printf("Ahora el tiempo de espera es de: %d\n", tiempo_de_espera);
				bateria_gastada = (floor((QUANTUM * (p->trabaja[i].Bateria))/p->trabaja[i].Tiempo));
				p->trabaja[i].Bateria -= bateria_gastada;
				metrica_bateria += bateria_gastada;
				bateria_comuna -= bateria_gastada;
				printf("Ahora la batería de la comuna es de: %d\n",bateria_comuna);
				p->trabaja[i].Tiempo -= QUANTUM;
				// Si el primero NO es el único nodo en la cola principal entonces coloquelo al final. 
				if(cola_principal->primero->siguiente != NULL){
					printf("*****Entro en pasar al último de la cola principal\n");
					colocar_al_final(cola_principal, p);
				}
			}
			// Si el tiempo es menor o igual al QUANTUM.
			else{
				printf("TRABAJA: tiempo menor que el Quantum\n");
				tiempo_total += p->trabaja[i].Tiempo;
				tiempo_de_espera += tiempo_total;
				cantidad_tareas += 1;
				printf("Ahora el tiempo total es de: %d\n",tiempo_total);
				printf("Ahora el tiempo de espera es de: %d\n", tiempo_de_espera);
				bateria_comuna -= p->trabaja[i].Bateria;
				metrica_bateria += p->trabaja[i].Bateria;
				printf("Ahora la batería de la comuna es de: %d\n",bateria_comuna);
				eliminarPalabra_listaAcciones(p,i);
				eliminar_trabaja(p,i);
				if(i == p->cantidad_de_palabras){
					eliminar_persona(cola_principal);
				}
			}

		}
		//Si lo primero en la lista de acciones de la persona es un Requiere.
		else{
			printf("Estoy ejecutando un Requiere\n");
			if(p->requiere[i].Bateria > bateria_comuna){
				printf("+++ Haciendo espera de 3 segundos para recargar la batería +++\n");
				sleep(3);
				bateria_comuna = 100;
			}
			// Si el tiempo es mayor al QUANTUM.
			if(p->requiere[i].Tiempo > QUANTUM){
				printf("REQUIERE: tiempo mayor que el Quantum\n");
				if(p->requiere[i].cola_area == NULL){
					agregarPersona_ColaArea(p);
				}
				tiempo_total += QUANTUM;
				tiempo_de_espera += tiempo_total;
				cantidad_tareas += 1;
				printf("Ahora el tiempo total es de: %d\n",tiempo_total);
				printf("Ahora el tiempo de espera es de: %d\n", tiempo_de_espera);
				bateria_gastada = (floor((QUANTUM * (p->requiere[i].Bateria))/p->requiere[i].Tiempo));
				p->requiere[i].Bateria -= bateria_gastada;
				metrica_bateria += bateria_gastada;
				bateria_comuna -= bateria_gastada;
				printf("Ahora la batería de la comuna es de: %d\n",bateria_comuna);
				p->requiere[i].Tiempo -= QUANTUM;
				// Si el primero NO es el único nodo en la cola principal entonces coloquelo al final. 
				if(cola_principal->primero->siguiente != NULL){
					printf("*****Entro en pasar al último de la cola principal\n");
					colocar_al_final(cola_principal, p);
				}
			}
			// Si el tiempo es menor o igual al QUANTUM.
			else{
				printf("REQUIERE: Tiempo menor al Quantum\n");
				tiempo_total += p->requiere[i].Tiempo;
				tiempo_de_espera += tiempo_total;
				cantidad_tareas += 1;
				printf("Ahora el tiempo total es de: %d\n",tiempo_total);
				printf("Ahora el tiempo de espera es de: %d\n", tiempo_de_espera);
				bateria_comuna -= p->requiere[i].Bateria;
				metrica_bateria += p->requiere[i].Bateria;
				printf("Ahora la batería de la comuna es de: %d\n",bateria_comuna);
				eliminar_persona(p->requiere[i].cola_area);
				eliminarPalabra_listaAcciones(p,i);
				eliminar_requiere(p,i);
				if(i == p->cantidad_de_palabras){
					eliminar_persona(cola_principal);
				}
			}
					
		}

	}
	printf("\n");
	printf("El tiempo total es = %d\n", tiempo_total);
	printf("El uso de batería total es de: %d\n", metrica_bateria);
	printf("Cantidad de tareas = %d\n", cantidad_tareas);
	// Cálculo de métrica de tiempo de espera promedio.
	int tiempoEspera_promedio = round(tiempo_de_espera/cantidad_tareas);
	printf("Tiempo de espera promedio = %d\n", tiempoEspera_promedio);
	// Cálculo de métrica de uso de batería proemdio.
	int usoDeBateria_promedio = round(metrica_bateria / cantidad_tareas);
	printf("Uso de Bateria promedio = %d\n", usoDeBateria_promedio);
}


//
void Trabajo_corto_Requiere(struct Requiere* requerimientos, int num_requerimientos) {
    int tiempo_transcurrido = 0;
    int i, j;
    for (i = 0; i < num_requerimientos; i++) {
        // Encontrar el requerimiento con el menor tiempo de ejecucion
        int min_tiempo = requerimientos[i].Tiempo;
        int min_index = i;
        for (j = i+1; j < num_requerimientos; j++) {
            if (requerimientos[j].Tiempo < min_tiempo) {
                min_tiempo = requerimientos[j].Tiempo;
                min_index = j;
            }
        }
        // Intercambiar los requerimientos en el array
        struct Requiere temp = requerimientos[i];
        requerimientos[i] = requerimientos[min_index];
        requerimientos[min_index] = temp;

        // Ejecutar el requerimiento y actualizar la bateria en la comuna 
        promedio_espera += tiempo_transcurrido;
        promedio_bateria += bateria_comuna;
        bateria_comuna -= requerimientos[i].Bateria;
        tiempo_transcurrido += requerimientos[i].Tiempo;
    }
}
//
void Trabajo_corto_trabaja(struct Trabaja* trabajos, int num_trabajos) {
    int tiempo_transcurrido = 0;
    int i, j;
    for (i = 0; i < num_trabajos; i++) {
        // Encontrar el trabajo con el menor tiempo de ejecucion
        int min_tiempo = trabajos[i].Tiempo;
        int min_index = i;
        for (j = i+1; j < num_trabajos; j++) {
            if (trabajos[j].Tiempo < min_tiempo) {
                min_tiempo = trabajos[j].Tiempo;
                min_index = j;
            }
        }
        // Intercambiar los trabajos en el array
        struct Trabaja temp = trabajos[i];
        trabajos[i] = trabajos[min_index];
        trabajos[min_index] = temp;

        // Ejecutar el trabajo y actualizar la bateria comuna 
        promedio_bateria += bateria_comuna;
        bateria_comuna -= trabajos[i].Bateria;
        tiempo_transcurrido += trabajos[i].Tiempo;
        promedio_espera += tiempo_transcurrido;
    }
}
void Correr_Trabajo_corto(){
	    // Definir requerimientos y trabajos
    struct Requiere requerimientos[] = {{'A', 10, 20}, {'B', 5, 10}, {'C', 8, 15}};
    struct Trabaja trabajos[] = {{5, 12}, {3, 7}, {7, 12}, {2, 5}};

    // Ordenar requerimientos y actualizar bateria comuna 
    int num_requerimientos = sizeof(requerimientos) / sizeof(requerimientos[0]);
    Trabajo_corto_Requiere(requerimientos, num_requerimientos);
    bateria_comuna -= promedio_bateria / num_requerimientos;

    // Ordenar trabajos y actualizar bateria comuna 
    int num_trabajos = sizeof(trabajos) / sizeof(trabajos[0]);
    Trabajo_corto_trabaja(trabajos, num_trabajos);
    bateria_comuna -= promedio_bateria / num_trabajos;

    // Imprimir resultados
    printf("Promedio de espera: %f\n", promedio_espera / (num_requerimientos + num_trabajos));
    printf("Uso de bateria promedio: %f\n", (promedio_bateria) / (num_requerimientos + num_trabajos));
}

    


int main(void){
	 int opcion;

   do {
   	system("cls"); 
      printf("Menu:\n");
      printf("1. Opcion Round Robin\n");
      printf("2. Opcion Trabajo mas corto\n");
      printf("3. Opcion 3\n");
      printf("Seleccione una opcion (1-3): ");
      scanf("%d", &opcion);

      switch(opcion) {
         case 1:
            printf("Selecciono la opcion 1\n");
            break;
         case 2:
            printf("Selecciono la opcion 2\n");
            system("cls"); 
            Correr_Trabajo_corto();
            system ("pause");
            break;
         case 3:
            printf("Selecciono la opcion 3\n");
            break;
         default:
            printf("Opcion invalida\n");
      }
   } while(opcion != 3);
	
	Cola cola_gimnasio;
	cola_Gym = cola_gimnasio;
	Cola tall_cola;
	cola_Taller = tall_cola;
	Cola biblio_cola;
	cola_Biblioteca = biblio_cola;
	Cola huerto_cola;
	cola_Huerto = huerto_cola;
	Cola farmacia_cola;
	cola_Farmacia = farmacia_cola;
	Cola recrea_cola;
	cola_Recreacion = recrea_cola;

	Cola cola_general;
	cola_principal = cola_general;

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
	p2.requiere = malloc(0);
	
	p3.trabaja = malloc(0);
	p3.requiere = malloc(0);

    p.cantidad_de_palabras = 0; // Se inicializan la cantidad de palabras 
	p2.cantidad_de_palabras = 0; 
	p3.cantidad_de_palabras = 0; 

	p.cantidad_trabaja = 0; //Se incializan la cantidad de trabjas 
	p2.cantidad_trabaja = 0;
	p3.cantidad_trabaja = 0;

    p.cantidad_requiere = 0; // Se incializa la cantidad de Requiere
	p2.cantidad_requiere = 0; // Se incializa la cantidad de Requiere
	p3.cantidad_requiere = 0; // Se incializa la cantidad de Requiere
	
	// Persona 1
	agregar_trabaja(&p, 80, 10);
	agregar_palabra_listaAcciones(&p, "Trabaja");
    agregar_trabaja(&p, 90, 20);
	agregar_palabra_listaAcciones(&p, "Trabaja");
	agregar_requiere(&p, "Gym", 100, 10);
	agregar_palabra_listaAcciones(&p, "Requiere");

	// Persona 2
	agregar_trabaja(&p2, 80, 10);
	agregar_palabra_listaAcciones(&p2, "Trabaja");
    agregar_trabaja(&p2, 90, 20);
	agregar_palabra_listaAcciones(&p2, "Trabaja");
	agregar_requiere(&p2, "Taller", 100, 10);
	agregar_palabra_listaAcciones(&p2, "Requiere");

	//Persona 3

	agregar_trabaja(&p3, 80, 10);
	agregar_palabra_listaAcciones(&p3, "Trabaja");
    agregar_trabaja(&p3, 90, 20);
	agregar_palabra_listaAcciones(&p3, "Trabaja");
	agregar_requiere(&p3, "Recreacion", 100, 10);
	agregar_palabra_listaAcciones(&p3, "Requiere");

	struct Persona *persona = &p;
	struct Persona *persona2 = &p2;
	struct Persona *persona3 = &p3;

	insertar_persona(&cola_principal, persona);
	insertar_persona(&cola_principal, persona2);
	insertar_persona(&cola_principal, persona3);

	round_robin(&cola_principal, 100);

	return 0;
}