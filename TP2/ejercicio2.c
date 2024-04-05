#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void imprimir_valor(char *nombre_nodo, int valor, int id_proceso, int id_padre, char *nombre_padre) {
    printf("%s - VALOR = %d\n", nombre_nodo, valor);
    printf("ID %s: %d - ID padre %s(%s): %d\n", nombre_nodo, id_proceso, nombre_nodo, nombre_padre, id_padre);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <VALOR>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int valor = atoi(argv[1]);

    printf("NODO R - VALOR = %d\n", valor);
    printf("ID proceso raiz: %d\n", getpid());

    // Nodo 1
    pid_t pid_nodo_1 = fork();

    if (pid_nodo_1 == 0) {
        // Proceso hijo Nodo 1
        valor += 100;
        imprimir_valor("NODO 1", valor, getpid(), getppid(), "NODO R");

        // Nodo 1.1
        pid_t pid_nodo_1_1 = fork();

        if (pid_nodo_1_1 == 0) {
            // Proceso hijo Nodo 1.1
            valor *= 2;
            imprimir_valor("NODO 1.1", valor, getpid(), getppid(), "NODO 1");
            exit(EXIT_SUCCESS);
        } else {
            // Proceso padre Nodo 1
            wait(NULL);
        }

        // Nodo 1.2
        pid_t pid_nodo_1_2 = fork();

        if (pid_nodo_1_2 == 0) {
            // Proceso hijo Nodo 1.2
            valor /= 2;
            imprimir_valor("NODO 1.2", valor, getpid(), getppid(), "NODO 1");
            exit(EXIT_SUCCESS);
        } else {
            // Proceso padre Nodo 1
            wait(NULL);
            exit(EXIT_SUCCESS);
        }
    } else {
        // Proceso padre Nodo R
        wait(NULL);

        // Nodo 2
        pid_t pid_nodo_2 = fork();

        if (pid_nodo_2 == 0) {
            // Proceso hijo Nodo 2
            valor -= 100;
            imprimir_valor("NODO 2", valor, getpid(), getppid(), "NODO R");
            exit(EXIT_SUCCESS);
        } else {
            // Proceso padre Nodo R
            wait(NULL);
            exit(EXIT_SUCCESS);
        }
    }

    return 0;
}
