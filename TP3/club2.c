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

	//Se abre el semáforo propio
	//Si no está creado, se finaliza el programa
	key_t keySem2 = ftok(".", 'K');
	struct sembuf sb2 = {0, -1, 0};
	int semid2;
	if((semid2=semget(keySem2,1,0666)) == -1){
		return(-1);
	}
	
	//Se abre el semáforo del club1
	key_t keySem1 = ftok(".", 'J');
	struct sembuf sb1 = {0, -1, 0};
	int semid1;
	semid1=semget(keySem1,1,0666);

	//Se abre el semáforo MUTEX
	key_t keyMut = ftok(".", 'M');
	struct sembuf sm = {0, -1, 0};
	int mutid;
	mutid=semget(keyMut,1,0666);

	//Se abre el segmento de memoria compartida
	key_t keyShm = ftok(".",'E');
	int shmid = shmget(keyShm, SEGSIZE , 0666);
	char *shmptr = shmat(shmid, 0, 0);

	//------------------------------------------------

	//Se bloquea (down2)
	semop(semid2, &sb2, 1);

	//Reserva la memoria compartida y estampa el color naranja
	semop(mutid, &sm, 1);
	printf("Estampando NARANJA\n");
	strcat(shmptr, "nar-");
	//Libera la memoria compartida
	sm.sem_op = 1;
	semop(mutid, &sm, 1);

	//Libera al club1 (up1)
	sb1.sem_op = 1;
	semop(semid1, &sb1, 1);
	//Se bloquea (down2)
	semop(semid2, &sb2, 1);

	//Reserva la memoria compartida y estampa el color verde
	semop(mutid, &sm, 1);
	printf("Estampando VERDE\n");
	strcat(shmptr, "ver-");
	//Libera la memoria compartida
	sm.sem_op = 1;
	semop(mutid, &sm, 1);

	//Libera al club1 (up1)
	sb1.sem_op = 1;
	semop(semid1, &sb1, 1);
	//Se bloquea (down2)
	semop(semid2, &sb2, 1);

	//Reserva la memoria compartida y estampa el color violeta
	semop(mutid, &sm, 1);
	printf("Estampando VIOLETA\n");
	strcat(shmptr, "vio");
	//Libera la memoria compartida
	sm.sem_op = 1;
	semop(mutid, &sm, 1);

	//Muestra el resultado final de la bandera
	printf("Bandera: %s\n", shmptr);
	
	//Elimina semáforo club2
	semctl(semid2,0,IPC_RMID,0);
	//Elimina semáforo MUTEX
	semctl(semid2,0,IPC_RMID,0);
	//Se desliga de la memoria compartida
	shmdt(shmptr);

	return 0;
}
