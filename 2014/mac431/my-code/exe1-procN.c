#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <stdlib.h>

#define N 10000

typedef struct shmemory{
	int x;
} sharedmem;

sharedmem *mem;

void show(int *);
int sum(int *,int ,int );
void init(int *);


int main(){
	int i;
	int x;
	int a[N];
	int smid;

  smid = shmget(42,				/* identificador */
	sizeof(sharedmem)*N,			/* tamanho */
	IPC_CREAT | 0600) ;

  mem = shmat(smid, 0, 0);
  mem->x = 0;

	init(a);
	
	// show(a);

	for(i = 0; i < N; i++){
		if((fork()) == 0){
			// printf("Filho : %d\n", i + 1);
			mem->x += a[i];
			exit(EXIT_SUCCESS);
		}
	}

	for(i = 0; i < N; i++)
		wait(NULL);

	printf("Val : %d\n", mem->x);
	shmctl(smid, IPC_RMID, NULL);
	return 0;
}

void init(int a[N]){
	int i;
	for(i = 0; i < N; i++){
		a[i] = i;
	}
}

void show(int a[N]){
	int i;
	for(i = 0; i < N; i++){
		printf("#%d = %d\n", i, a[i]);
	}
}

int sum(int vec[N], int a, int b){
	int i = a;
	int x = 0;
	if (a < b){
		for(; i < b; i++){
			printf("#%d == %d\n",i,vec[i] );
			x = x + vec[i];
			// usleep(100000); //Usar com microsegundos.. 1 000 000 us = 1 s
		}	
	}
	return x;
}