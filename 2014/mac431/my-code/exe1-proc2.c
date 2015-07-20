#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#define N 10000

typedef struct shmemory{
	int x;
} sharedmem;

sharedmem *mem;

void show(int *);
int sum(int *,int ,int );
void init(int *);

int x;

int main(){
	int i;
	int y;
	int a[N];
	int smid;

  smid = shmget(42,				/* identificador */
	sizeof(sharedmem),			/* tamanho */
	IPC_CREAT | 0600) ;

  mem = shmat(smid, 0, 0);
  mem->x = 0;

	init(a);
	
	// show(a);

	if((fork()) == 0){
		x = 0;
		int i = 0;
		for(;i < N/2; i++)
			x = x + a[i];

		mem->x += x;
		// x = sum(a,0,N/2);
	}
	else{
		y = 0;
		int k = N/2;
		for(;k < N; k++)
			y = y + a[k];

		// y = sum(a,N/2,N);
		mem->x += y;
		wait(NULL);
		printf("Var : %d\n", mem->x);
		shmctl(smid, IPC_RMID, NULL);
	}

	
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