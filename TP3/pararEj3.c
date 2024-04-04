#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
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
	msg.mtype = 1;
	strcpy(msg.mensaje,"CERRAR");

	key_t key = ftok(".", 'J');
	int msgid = msgget(key, 0666|IPC_CREAT);

	msgsnd(msgid, &msg, sizeof(msg), 0);
	


	return 0;
}
