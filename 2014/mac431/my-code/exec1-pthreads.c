#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define N 10000


void sum(void *ptr);
void init(int *);
void show(int *);

typedef struct data{
	long unsigned int i;
} fdata;

fdata data_array[N];

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

long unsigned int x;
int vec[N];


int main(){
	long unsigned int k;
	pthread_t id[N];
	x = 0;
	init(vec);

	for(k = 0; k < N; k++){
		data_array[k].i = k;
		// printf("v = %d\n", args.i);
		pthread_create(&id[k], NULL, (void *) &sum, (void *) &data_array[k]);
	}
	for(k = 0; k < N; k++){
		pthread_join(id[k], NULL);
	}

	printf("SUM : %d\n", x);
	return 0;
}

void sum(void *ptr){
	pthread_mutex_lock(&mut);
	fdata *n ;
	n = (fdata *)ptr;
	// printf("x = %d\n\n", x);
	x += vec[n->i];
	pthread_mutex_unlock(&mut);
	pthread_exit(0);
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