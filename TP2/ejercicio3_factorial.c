#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

int factorial(int n) {
    if (n <= 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

int main(int argc, char *argv[]) {
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

    printf("Factorial de %d = %d\n", number, factorial(number));
    printf("Id de Prg-Factorial: %d\n", getpid());

    return 0;
}
