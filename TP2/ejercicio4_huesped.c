#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc,char* argv[]){

int tostadora,cont;

tostadora=atoi(argv[1]);

for(cont=1;cont<31;cont++){

	if(cont%5==0){

		printf("Pedido de Pan Negro. Huesped: %d\n",cont);
		kill(tostadora,SIGUSR2);
		sleep(1);

		}
	else
	{
		printf("Pedido de Pan Blanco. Huesped: %d\n",cont);
		kill(tostadora,SIGUSR1);
		sleep(2);
		}
	}
	return 0;
}
