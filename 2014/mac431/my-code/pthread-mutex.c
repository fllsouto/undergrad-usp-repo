#include <stdio.h>
#include <pthread.h>

int x;

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

void loop(){
	int y;
	int i;
	for (i = 0; i < 10; ++i){
		pthread_mutex_lock(&mut);
		y = x;
		y += 1;
		x = y;
		pthread_mutex_unlock(&mut);
	}
		printf("My pid : %d\n", getpid());
}

int main(int ac){

	pthread_t id[3];
	x = 0;

	for(int k = 0; k < 3; k++)
		pthread_create(&id[k], NULL, loop, NULL);
	
	pthread_create(&id2, NULL, loop, NULL);
	while(x < 200){
		pthread_join(id[k], NULL);
	}

	printf("Valod de X : %d\n",x);
}