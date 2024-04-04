#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

struct msgbuf{

	long mtype;
	char mensaje[80];
} msg;

int main()
{

	//Crea la cola de mensajes
	key_t key = ftok(".", 'J');
	int msgid = msgget(key, 0666|IPC_CREAT);
	
	char clientepid[20];

	while (1)
	{

		msgrcv(msgid, &msg, sizeof(msg), 1, 0);

		if(strcmp(msg.mensaje,"CERRAR") == 0)break;

		char * dt_ptr;
		time_t t_secs;
		char respuesta[80] = "Fecha y Hora: ";

		//Crea la respuesta para el cliente
		t_secs = time(NULL);
		dt_ptr = ctime(&t_secs);
		strcat(respuesta,dt_ptr);

		printf("Cliente PID: %s", msg.mensaje);
		printf(" %s\n", respuesta);

		msg.mtype = atoi(msg.mensaje);
		strcpy(msg.mensaje, respuesta);

		msgsnd(msgid, &msg, sizeof(msg), 0);	
		
	}

	msgctl(msgid,IPC_RMID, NULL);
	
	return 0;
}
