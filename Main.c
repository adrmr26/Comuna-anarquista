#include <stdio.h>
#include "structs.h"

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
