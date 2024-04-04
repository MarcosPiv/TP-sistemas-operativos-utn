#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{

	key_t key;
	int semid;
	struct sembuf sb = {0, -1, 0};
	key = ftok(".", 'J');
	semid = semget(key, 1, 0);
	
	int fifo;
	
	// FIFO file path
	char clientefifo[50] = "/tmp/";

	int pid = getpid();
	char strpid[10];

	sprintf(strpid, "%d", pid);

	strcat(clientefifo, strpid);
	strcat(clientefifo, ".fifo");
	
	// Crea la FIFO del cliente
	mkfifo(clientefifo, 0666);
	
	// serverFIFO file path
	char * serverfifo = "/tmp/datetime.fifo";
	
	// Genera la FIFO del server
	mkfifo(serverfifo, 0666);

	//Reserva el FIFO del server
	semop(semid, &sb, 1);
	
	//Abre la FIFO del server, envía el pedido y cierra

	fifo = open(serverfifo,O_WRONLY);

	write(fifo, strpid, strlen(strpid)+1);
	close(fifo);

	//Libera el FIFO del server
	sb.sem_op = 1;
	semop(semid, &sb, 1);

	//Abre la FIFO del cliente y lee la respuesta

	fifo = open(clientefifo,O_RDONLY);

	char array[80];

	read(fifo, array, sizeof(array));

	//Muestra la respuesta, cierra la serverFIFO, y borra su FIFO

	puts(array);

	close(fifo);

	unlink(clientefifo);

	return 0;
}
