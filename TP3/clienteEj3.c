#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

struct msgbuf{

	long mtype;
	char mensaje[80];
} msg;

int main()
{

	key_t key = ftok(".", 'J');
	int msgid = msgget(key, 0666|IPC_CREAT);

	int pid = getpid();
	char strpid[10];

	sprintf(strpid, "%d", pid);
	
	//Prepara la solicitud
	msg.mtype = 1;
	strcpy(msg.mensaje, strpid);

	//Envia mensaje al server
	msgsnd(msgid, &msg, sizeof(msg), 0);

	//Recibe respuesta del server
	msgrcv(msgid, &msg, sizeof(msg), atoi(strpid),0);

	//Muestra la respuesta
	printf("%s\n", msg.mensaje);	

	return 0;
}
