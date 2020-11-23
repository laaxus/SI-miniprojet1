#include "threads.h"
#include "mutex_sema.h"
#include <stdlib.h>
#include <stdio.h>

//number of thread
int N;

//home made mutex
volatile int mutex;

void init_state(int nb) {
	N = nb;
	
	//define lock
	my_mutex_init(&mutex); 
}

void* tatas_main() {
	 int count = 6400 / N;
	 while(count--)
	{

		//entre zone critique
		my_mutex_lock(&mutex);
		

		while(rand() > RAND_MAX/10000)
			continue;
		
		//sort zone critique
		my_mutex_unlock(&mutex);

	}
 return NULL;
}


pthread_t start_thread() {
    pthread_t th;
    pthread_create(&th, NULL, tatas_main, NULL);
    return th;
}






