#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024

struct Requiere {
    char area[BUFFER_SIZE];
    int bateria;
    int tiempo;
};

struct Trabaja {
    int bateria;
    int tiempo;
};

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
                            strcpy(req.area, strtok(NULL, " "));
                            req.bateria = atoi(strtok(NULL, " "));
                            req.tiempo = atoi(strtok(NULL, " "));
                            requieres[num_requiere++] = req;
                        } else if (strcmp(token, "Trabaja") == 0) {
                            // Extraer los datos y agregar a la lista de trabajas
                            struct Trabaja tra;
                            tra.bateria = atoi(strtok(NULL, " "));
                            tra.tiempo = atoi(strtok(NULL, " "));
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
            printf("%s %d %d\n", requieres[i].area, requieres[i].bateria, requieres[i].tiempo);
        }
        printf("\nTrabaja:\n");
        for (int i = 0; i < num_trabaja; i++) {
            printf("%d %d\n", trabajas[i].bateria, trabajas[i].tiempo);
        }
    } else {
        printf("Error al abrir el directorio\n");
    }

    return 0;
}
