#include "threads.h"
#include <stdlib.h>
#include <stdio.h>

//number of thread
int N;

//home made mutex
volatile int mutex;


void my_mutex_init(volatile int* mtx)
{
	*mtx = 0;
}

void my_mutex_lock(volatile int* mtx)
{
	asm volatile(
			"1:"
			"movl $1, %%eax;"
			"xchgl %%eax, %0;"
			"testl %%eax, %%eax;"    
			"jne 1b;"
			:"=m"(*mtx)
			:"m"(*mtx)
			:"%eax"
		); 
}

void my_mutex_unlock(volatile int* mtx)
{
	asm volatile(
			"movl $0, %0;"
			:"=m"(*mtx)
			:"m"(*mtx)
			:
		);
}

void init_state(int nb) {
	N = nb;
	
	//define lock
	my_mutex_init(&mutex); 
}

void* tas_main() {
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
    pthread_create(&th, NULL, tas_main, NULL);
    return th;
}





