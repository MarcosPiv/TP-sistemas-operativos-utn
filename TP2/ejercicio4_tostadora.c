#include <stdio.h>
#include<signal.h>
#include <unistd.h>
int tostadas=0;
void tostar_negro(){
	tostadas++;
	printf("Deseo tostadas de pan negro.\n");
	printf("Tostadas de pan negro. (%d",tostadas);
	printf(").\n");
	printf("Tostadas listas.\n");
	printf("Tostadora libre,esperando pan.\n");
}

void tostar_blanco(){
	tostadas++;
	printf("Deseo tostadas de pan blanco.\n");
	printf("Tostadas de pan blanco. (%d",tostadas);
	printf(").\n");
	printf("Tostadas listas.\n");
	printf("Tostadora libre,esperando pan.\n");
}

int main(int argc,char* argv[]){

signal(SIGUSR1,&tostar_blanco);
signal(SIGUSR2,&tostar_negro);
while(tostadas!=30);

return 0;


}
