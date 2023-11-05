#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    // Inicializar el entorno MPI
    MPI_Init(NULL, NULL);

    // Obtener el número de procesos
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Obtener el rango del proceso
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // La frase a dividir
    char frase[] = "tres tristes tigres tragaban trigo en un trigal";
    int len = strlen(frase);

    // Se asume que el número de palabras en la frase es divisible por el número de procesos
    // y que tenemos al menos 4 procesos como lo has pedido.
    
    // Calcular la longitud máxima de una palabra
    int max_word_length = 0;
    int word_count = 0;
    for(int i = 0; i < len; ++i) {
        int word_len = 0;
        while(i < len && frase[i] != ' ') {
            i++;
            word_len++;
        }
        max_word_length = (word_len > max_word_length) ? word_len : max_word_length;
        word_count++;
    }

    // Buffer para las palabras que se enviarán a cada proceso
    char (*words)[max_word_length + 1] = malloc(word_count * (max_word_length + 1));
    int k = 0; // Índice para las palabras
    for(int i = 0; i < len;) {
        int j = 0;
        while(i < len && frase[i] != ' ') {
            words[k][j++] = frase[i++];
        }
        words[k][j] = '\0'; // Null-terminate la palabra
        if(frase[i] == ' ') {
            i++; // Saltar el espacio
        }
        k++; // Siguiente palabra
    }

    // Dividir las palabras entre los procesos
    int words_per_proc = word_count / world_size;
    char (*subwords)[max_word_length + 1] = malloc(words_per_proc * (max_word_length + 1));

    MPI_Scatter(words, words_per_proc * (max_word_length + 1), MPI_CHAR,
                subwords, words_per_proc * (max_word_length + 1), MPI_CHAR,
                0, MPI_COMM_WORLD);

    // Cada proceso ahora tiene su subconjunto de palabras
    // Procesar las palabras en cada proceso
    for(int i = 0; i < words_per_proc; ++i) {
        printf("Process %d has word: %s\n", world_rank, subwords[i]);
    }

    // Liberar recursos
    free(words);
    free(subwords);

    // Finalizar el entorno MPI
    MPI_Finalize();
    return 0;
}
