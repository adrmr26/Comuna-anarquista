#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include "structs.h"

#define BUFFER_SIZE 1024

int main() {
    char* path = "C:\\Users\\Adrmr\\Documents\\UNIVERSIDAD\\Operativos\\Tareas de la comuna\\";
    DIR* directory = opendir(path);
    struct dirent* file;

    // Listas para almacenar los datos
    struct Requiere requieres[100];
    int num_requiere = 0;
    struct Trabaja trabajas[100];
    int num_trabaja = 0;

    if (directory != NULL) {
        while ((file = readdir(directory)) != NULL) {
            if (strcmp(file->d_name, ".") != 0 && strcmp(file->d_name, "..") != 0) {
                char filepath[BUFFER_SIZE];
                snprintf(filepath, BUFFER_SIZE, "%s%s", path, file->d_name);

                // Leer el contenido del archivo
                FILE* fp = fopen(filepath, "r");
                char buffer[BUFFER_SIZE];
                while (fgets(buffer, BUFFER_SIZE, fp)) {
                    char* token = strtok(buffer, " ");
                    if (token != NULL) {
                        if (strcmp(token, "Requiere") == 0) {
                            // Extraer los datos y agregar a la lista de requieres
                            struct Requiere req;
                            strcpy(req.Area, strtok(NULL, " "));
                            req.Bateria = atoi(strtok(NULL, " "));
                            req.Tiempo = atoi(strtok(NULL, " "));
                            requieres[num_requiere++] = req;
                        } else if (strcmp(token, "Trabaja") == 0) {
                            // Extraer los datos y agregar a la lista de trabajas
                            struct Trabaja tra;
                            tra.Bateria = atoi(strtok(NULL, " "));
                            tra.Tiempo = atoi(strtok(NULL, " "));
                            trabajas[num_trabaja++] = tra;
                        }
                    }
                }
                fclose(fp);
            }
        }
        closedir(directory);

        // Imprimir los datos
        printf("Requiere:\n");
        for (int i = 0; i < num_requiere; i++) {
            printf("%s %d %d\n", requieres[i].Area, requieres[i].Bateria, requieres[i].Tiempo);
        }
        printf("\nTrabaja:\n");
        for (int i = 0; i < num_trabaja; i++) {
            printf("%d %d\n", trabajas[i].Bateria, trabajas[i].Tiempo);
        }
    } else {
        printf("Error al abrir el directorio\n");
    }

    return 0;
}
