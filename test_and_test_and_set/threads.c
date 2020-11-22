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


void my_mutex_lock(int* mtx)
{
	asm(
			"1:"
			"movl %0, %%eax;"
			"testl %%eax, %%ebx;"    
			"jne 1b;"
			"2:"
			"movl $1, %%eax;"
			"xchgl %%eax, %0;"
			"testl %%eax, %%eax;"    
			"jne 1b;"
			:"=m"(*mtx)
			:"m"(*mtx)
			:"%eax"
		); 
}

void my_mutex_unlock(int* mtx)
{
	asm(
			"movl $0, %0;"
			:"=m"(*mtx)
			:"m"(*mtx)
			:
		);
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






