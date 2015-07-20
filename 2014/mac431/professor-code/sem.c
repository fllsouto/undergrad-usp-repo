#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdio.h>
union semun { //Essa estrutura é necessária para chamar o semctl por default
  int val;                    /* value for SETVAL */
  struct semid_ds *buf;       /* buffer for IPC_STAT, IPC_SET */
  unsigned short int *array;  /* array for GETALL, SETALL */
  struct seminfo *__buf;      /* buffer for IPC_INFO */
};
typedef int * SHARED;

SHARED x;

struct sembuf smb;
union semun arg;

#define SEM_CALL semop(semid, &smb, 1)
#define SEM_SET(x) arg.val = x ; semctl(semid, 0, SETVAL, arg)
#define SEM_P() smb.sem_op = -1 ;  SEM_CALL
#define SEM_V() smb.sem_op =  1 ;  SEM_CALL

void main(int ac)
{
  int i,j;
  int smid, semid;
  int sim;
  int pidf;

  sim = ac > 1; //vai entrar no if dentro do for
  smid = shmget(42, sizeof(int), IPC_CREAT | 0600) ;
  x = (SHARED)shmat(smid, 0, 0); //segmento de memoria compartilhada do tamanho de um inteiro

  semid = semget(43, 1, IPC_CREAT | 0600) ;
  smb.sem_num = 0;
  smb.sem_flg = 0;

  SEM_SET(1);
  
  *x = 0;

  if ((pidf = (fork())) == 0) {
		int y;
		// printf("Pid do filho : %d\n",getpid()); //Mostra o PID do filho
		// printf("Pid do pai : %d\n",getppid()); //Mostra o PID do pai
		for (i=0; i< 5;i++) {
		  if (sim) { // se o argumento for passado na linha de comando ele vai habilitar a proteção da região crítica
				SEM_P();
		  }
		  printf("\n--------------------------\nFilho\n");
		  printf("PID: %d \n", getpid());
		  
		  for (j=0;j<1000000;j++) {
				y = *x;
				y += 1;
				*x = y;
	    }
			
			printf("x = %d\n", *x);
		  puts("\n--------------------------");	
		 
		  SEM_V();
		}
  }
  else {
	int y;

	for (i=0; i< 5;i++) {
	  if (sim) {
		SEM_P();
	  }
	  printf("\n--------------------------\nPai\n");
	  printf("PID: %d \n", getpid());
	  
	  for (j=0;j<1000000;j++) {
		y = *x;
		y += 1;
		*x = y;
	  }
	  
	  printf("x = %d\n", *x);
	  puts("\n--------------------------");
	  
	  SEM_V();
	}
	wait(NULL);
	printf("x = %d\n", *x);

	/* libera a memória */
	shmctl(smid,IPC_RMID, NULL);
  }
}

