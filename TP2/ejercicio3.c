#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    printf("Id proceso que invoca: %d\n", getpid());

    if (argc != 2) {
        printf("Error. Usar %s [numero]\n", argv[0]);
        printf("Id de Prg-Factorial: %d\n", getpid());
        return 1;
    }

    int number = atoi(argv[1]);
    if (number < 1 || number > 10) {

        printf("Numero fuera de rango: %d\n", number);
        printf("Id de Prg-Factorial: %d\n", getpid());
        return 1;
    }

    char numberStr[12];
    snprintf(numberStr, sizeof(numberStr), "%d", number);

    char *programName = "./ejercicio3_factorial";
    char *programArgs[] = {programName, numberStr, NULL};

    if (fork() == 0) {
        // Child process
        execv(programName, programArgs);
    } else {
        wait(NULL);
    }

    return 0;
}

