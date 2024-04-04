#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void crearSemaforo(){

	key_t key = ftok(".", 'J');

	int semid;
	semid=semget(key,1,0666|IPC_CREAT);
	semctl(semid,0,SETVAL,1);
}

void eliminarSemaforo(){

	key_t key= ftok(".", 'J');

	int semid;
	semid=semget(key,1,0);
	semctl(semid,0,IPC_RMID,0);
}

void responderSolicitud(char pid[20]){

	int fifo;
	char * dt_ptr;
	time_t t_secs;
	char respuesta[80] = "Fecha y Hora: ";

	//Crea la respuesta para el cliente
	t_secs = time(NULL);
	dt_ptr = ctime(&t_secs);
	strcat(respuesta,dt_ptr);

	printf("Cliente PID: %s", pid);
	printf(" %s\n", respuesta);

	//Genera el file path de la FIFO del cliente
	char clientefifo[50] = "/tmp/";

	strcat(clientefifo, pid);
	strcat(clientefifo, ".fifo");

	// Abre la FIFO del cliente
	mkfifo(clientefifo, 0666);

	// Abre la FIFO del cliente, escribe la respuesta y cierra
	fifo = open(clientefifo,O_WRONLY);
	write(fifo, respuesta, strlen(respuesta)+1);
	close(fifo);


}

int main()
{

	//Crea el semáforo que utilizará para su FIFO
	crearSemaforo();

	int fifo, ret;
	
	// serverFIFO file path
	char * serverfifo = "/tmp/datetime.fifo";
	
	// Crea la serverFIFO
	ret = mkfifo(serverfifo, 0666);
	
	char clientepid[20];

	while (1)
	{

		// Abre la FIFO del server, lee y cierra
		fifo = open(serverfifo,O_RDONLY);
		read(fifo, clientepid, sizeof(clientepid));

		if(strcmp(clientepid,"CERRAR") == 0)break;

		close(fifo);

		responderSolicitud(clientepid);	
		
	}

	unlink("/tmp/datetime.fifo");

	eliminarSemaforo();
	
	return 0;
}
