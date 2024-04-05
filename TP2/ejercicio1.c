#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
	int val, activate = 0;
	while((val = getopt (argc, argv, "cls:")) != -1) {
		switch(val){
		case 'c': {
			printf("Cantidad de argumentos: %d", argc);
			printf("\n");
		} break;
		case 'l': {
			int i;
			for(i = 0; i < argc; i++) {
				printf("Argumento: %d- %s\n", i, argv[i]);
			}
		} break;
		case '?':
			if (optopt == 's') printf(argv[0], ": option requires an argument -- s");
			break;
		case 's': {
			char *nombreArchivo = optarg;
			FILE *arch = fopen(nombreArchivo, "w");
			if(arch == NULL) {
				printf("El archivo no se creo\n");
				exit(1);
			}
			int i;
			for(i = 0; i < argc; i++) {
				fputs(argv[i], arch);
				fputs("\n", arch);
			}
			fclose(arch);
		}
		}
		activate = 1;
	}
	if(activate == 0)
		printf("Uso: %s [-cl] [-s nombre_archivo]\n", argv[0]);
	return 0;
}
