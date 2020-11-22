#include "threads.h"
#include <stdlib.h>
#include <stdio.h>

//number of thread
int N;

//home made mutex
int mutex;

void init_state(int nb) {
	N = nb;
	
	//define lock
	mutex = 0; 
}

void my_mutex_lock(int* mutex)
{
	asm(
			"retry:"
			"movl mutex, %eax;"
			"testl %eax, %eax;"    
			"jnz retry;"
			"enter:"
			"movl $1, %eax;"
			"xchgl %eax, mutex;"
			"testl %eax, %eax;"    
			"jnz retry;"			
		); 
}

void my_mutex_unlock(int* mutex)
{
	asm(
			"movl $0, %eax;"		
			"xchgl %eax, %1;"
			:"r"(*mutex)
		);
}

/*
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

*/




