#include <stdio.h>
#include <string.h>
#include <omp.h>

int main() {
    char frase[] = "tres tristes tigres trigaban trigo por culpa del bolivar";
    int len = strlen(frase);
    
    // Variables para almacenar las dos frases divididas
    char frase1[len];
    char frase2[len];
    
    // Inicializar las frases resultantes como cadenas vacías
    frase1[0] = '\0';
    frase2[0] = '\0';
    
    // Index para cada palabra
    int index = 0;
    
    // Dividir la frase usando OpenMP
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < len; i++) {
        // Detectar el inicio de una palabra
        if ((i == 0 || frase[i-1] == ' ') && frase[i] != ' ') {
            // Usar 'index' para determinar si la palabra es par o impar
            if (index % 2 == 0) {
                #pragma omp critical
                {
                    strcat(frase1, frase1[0] != '\0' ? " " : "");
                    // Agregar la palabra a frase1
                    while (i < len && frase[i] != ' ') {
                        strncat(frase1, &frase[i], 1);
                        i++;
                    }
                }
            } else {
                #pragma omp critical
                {
                    strcat(frase2, frase2[0] != '\0' ? " " : "");
                    // Agregar la palabra a frase2
                    while (i < len && frase[i] != ' ') {
                        strncat(frase2, &frase[i], 1);
                        i++;
                    }
                }
            }
            index++;
        }
    }

    printf("Frase 1: %s\n", frase1);
    printf("Frase 2: %s\n", frase2);
    
    return 0;
}
