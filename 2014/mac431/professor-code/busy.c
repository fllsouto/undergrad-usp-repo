#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <stdio.h>


typedef struct {
  volatile int x;
  volatile int enter1, enter2, turn;
} SHARED;

/* Esta vari�vel ser� compartilhada entre dois processos */
SHARED *Comp;

int main(int ac, char **av)
{
  int i;
  int smid;
  int sim = ac > 1;

  /* shmget aloca um bloco de mem�ria compartilhada e retorna um 'handle' */
  smid = shmget(42,				/* identificador */
		sizeof(SHARED),			/* tamanho */
		IPC_CREAT | 0600) ;		/* permiss�o de acesso */

  /* shmat retorna um ponteiro para a regi�o compartilhada */
  Comp = (SHARED *)shmat(smid, 0, 0);
  
  /* inicializa��o */
  Comp->x = 0;
  Comp->enter1 = Comp->enter2 = 0;
  Comp->turn = 1;

  /* fork() � uma chamada para o sistema que cria uma c�pia do processo */
  /* corrente. */
  /* Logo ap�s a chamada existem dois processos id�nticos, cada um com */
  /* seu contexto.  No processo "filho", fork() retorna 0. */
	
  if ((fork()) == 0) {
	/* Filho */
	int y, j;

	for (j=0; j<10; j++) {
	  if (sim) {
		printf("I Filho -- E1 : %d -- E2 : %d -- T : %d -- x : %d \n", Comp->enter1,Comp->enter2,Comp->turn,Comp->x);
		Comp->enter1 = 1;
		Comp->turn   = 2;
		while (Comp->enter2 == 1 && Comp->turn == 2) usleep(1);
	  }
	  
	  for (i=0; i< 5000;i++) {
		y = Comp->x;
		y += 2;
		Comp->x = y;
		
	  }
		printf("O Filho -- E1 : %d -- E2 : %d -- T : %d -- x : %d \n", Comp->enter1,Comp->enter2,Comp->turn,Comp->x);
	  Comp->enter1 = 0;
	}
  }
  else {
	/* Pai */
	int y,j;

	for (j=0; j<10; j++) {
	  if (sim) {
		printf("I Pai -- E1 : %d -- E2 : %d -- T : %d -- x : %d \n", Comp->enter1,Comp->enter2,Comp->turn,Comp->x);
		Comp->enter2 = 1;
		Comp->turn   = 1;
		while (Comp->enter1 == 1 && Comp->turn == 1) usleep(1);
	  }
	  for (i=0; i< 5000;i++) {
		y = Comp->x;
		y += 1;
		Comp->x = y;
	  }
		printf("O Pai -- E1 : %d -- E2 : %d -- T : %d -- x : %d \n", Comp->enter1,Comp->enter2,Comp->turn,Comp->x);
	  Comp->enter2 = 0;
	}

	/* espera o filho terminar */
	wait(NULL);

	/* imprime o valor final */
	printf("x = %d\n", Comp->x);

	/* libera a mem�ria */
	shmctl(smid,IPC_RMID, NULL);
  }
  return 0;
}

                                                              
