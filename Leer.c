#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *archivo;
	char carater;

	archivo =fopen("Mantener huerto.txt","r");
	if (archivo==NULL){
		printf("Error en la apertura del archivo\n");
	}else{
		printf("Si sirvio\n\n");
		while(feof(archivo)==0){
			carater=fgetc(archivo);
			printf("%c",carater);

		}
	}

	fclose(archivo);
	getch();
	return 0;
}
