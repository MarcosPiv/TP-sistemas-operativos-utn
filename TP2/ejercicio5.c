#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

void iterar(){
	int i;
	for(i=0; i<=100000; i++){
		if(i%1000==0 && i!=0){
			printf("Iteracion %d \n", i);
		}
		usleep(1);
	}
}
int main(int argc, char *argv[])	{
	signal(SIGINT,SIG_IGN);
	printf("Iteracion INICIADA. Presionar Ctrl-C NO tiene efecto.... \n");
	iterar();
	printf("Computation is done. \n");
	printf("\n");
	printf("REINICIO de la Iteracion. Presionar Ctrl-C AHORA tiene efecto... \n");
	signal(SIGINT,SIG_DFL);
	iterar();
	printf("Computation is done. \n");
	
	return(0);
}
