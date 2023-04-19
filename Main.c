#include <stdio.h>
#include "structs.h"

int main(){
	struct Panel P = {100};
	struct Requiere s1 ={"Gym",12,11};
	struct Nodo *colaGym = NULL;

	
	printf("%s %d %d", s1.Area, s1.Bateria, s1.Tiempo);
	return 0;
}
