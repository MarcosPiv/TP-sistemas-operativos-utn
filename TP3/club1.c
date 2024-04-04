#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h> 
#include <string.h>
#include <linux/shm.h>
#include <linux/ipc.h>
#include <linux/sem.h>

#define SEGSIZE 128

int main(int argc, char *argv[]){

	//Se crea el semáforo propio
	key_t keySem1 = ftok(".", 'J');
	struct sembuf sb1 = {0, -1, 0};
	int semid1;
	semid1=semget(keySem1,1,0666|IPC_CREAT);
	semctl(semid1,0,SETVAL,0);

	//Se crea el semáforo del club2
	key_t keySem2 = ftok(".", 'K');
	struct sembuf sb2 = {0, -1, 0};
	int semid2;
	semid2=semget(keySem2,1,0666|IPC_CREAT);
	semctl(semid2,0,SETVAL,0);

	//Se crea el semáforo MUTEX
	key_t keyMut = ftok(".", 'M');
	struct sembuf sm = {0, -1, 0};
	int mutid;
	mutid=semget(keyMut,1,0666|IPC_CREAT);
	semctl(mutid,0,SETVAL,1);

	//Se crea el segmento de memoria compartida
	key_t keyShm = ftok(".",'E');
	int shmid = shmget(keyShm, SEGSIZE ,IPC_CREAT | 0666);
	char *shmptr = shmat(shmid, 0, 0);

	//------------------------------------------------

	//Reserva la memoria compartida y estampa el color rojo
	semop(mutid, &sm, 1);
	printf("Estampando ROJO\n");
	strcpy(shmptr, "roj-");
	//Libera la memoria compartida
	sm.sem_op = 1;
	semop(mutid, &sm, 1);

	//Libera al club2 (up2)
	sb2.sem_op = 1;
	semop(semid2, &sb2, 1);
	//Se bloquea (down1)
	semop(semid1, &sb1, 1);

	//Reserva la memoria compartida y estampa el color rojo
	semop(mutid, &sm, 1);
	printf("Estampando AMARILLO\n");
	strcat(shmptr, "ama-");
	//Libera la memoria compartida
	sm.sem_op = 1;
	semop(mutid, &sm, 1);

	//Libera al club2 (up2)
	sb2.sem_op = 1;
	semop(semid2, &sb2, 1);
	//Se bloquea (down1)
	semop(semid1, &sb1, 1);

	//Reserva la memoria compartida y estampa el color rojo
	semop(mutid, &sm, 1);
	printf("Estampando AZUL\n");
	strcat(shmptr, "azu-");
	//Libera la memoria compartida
	sm.sem_op = 1;
	semop(mutid, &sm, 1);

	//Libera al club2 (up2)
	sb2.sem_op = 1;
	semop(semid2, &sb2, 1);
	
	//Elimina semáforo club1
	semctl(semid1,0,IPC_RMID,0);
	//Se desliga de la memoria compartida
	shmdt(shmptr);

	return 0;
}
