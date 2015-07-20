#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <stdio.h>

//Esse codigo só ilustra a corrida que acontece dentro da variavel compartilhada

typedef struct {
  volatile int x;
} SHARED;

/* Esta variável será compartilhada entre dois processos */
SHARED *Comp;

int main(int ac, char **av)
{
  int i;
  int smid;

  /* shmget aloca um bloco de memória compartilhada e retorna um 'handle' */
  smid = shmget(42,				/* identificador */
		sizeof(SHARED),			/* tamanho */
		IPC_CREAT | 0600) ;		/* permissão de acesso */

  /* shmat retorna um ponteiro para a região compartilhada */
  Comp = (SHARED *)shmat(smid, 0, 0);
  
  /* inicialização */
  Comp->x = 0;

  /* fork() é uma chamada para o sistema que cria uma cópia do processo */
  /* corrente. */
  /* Logo após a chamada existem dois processos idênticos, cada um com */
  /* seu contexto.  No processo "filho", fork() retorna 0. */
	
  if ((fork()) == 0) {
	/* Filho */
	int y;

	for (i=0; i< 5000000;i++) {
	  y = Comp->x;
	  y += 2;
	  Comp->x = y;
	  
	}
  }
  else {
	/* Pai */
	int y;

	for (i=0; i< 5000000;i++) {
	  y = Comp->x;
	  y += 1;
	  Comp->x = y;
	}

	/* espera o filho terminar */
	wait(NULL);

	/* libera a memória */
	shmctl(smid,IPC_RMID, NULL);

	/* imprime o valor final */
	printf("x = %d\n", Comp->x);
  }
  return 0;
}

