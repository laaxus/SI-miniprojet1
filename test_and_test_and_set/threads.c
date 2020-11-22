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

/*
			"1:"
			"movl %0, %%eax;"
			"movl $0, %%ebx;"
			"cmpl %%eax, %%ebx;"    
			"jne 1b;"

			
			*/

void my_mutex_lock(int* mtx)
{
	asm(
			"1:"
			"movl $1, %%eax;"
			"xchgl %%eax, %0;"
			"movl $0, %%ebx;"
			"cmpl %%eax, %%ebx;"    
			"jne 1b;"
			:"=r"(*mtx)
			:"r"(*mtx)
			:"%eax","%ebx"
		); 
}

void my_mutex_unlock(int* mtx)
{
	asm(
			"movl $0, %%eax;"
			"xchgl %%eax, %0;"
			:"=r"(*mtx)
			:"r"(*mtx)
			:"%eax"
		);
}


void* tatas_main() {
	 int count = 6 / N;
	 while(count--)
	{
		printf("A\n");
		fflush(stdout);
		//entre zone critique
		my_mutex_lock(&mutex);
		
		printf("%d\n",count);
		fflush(stdout);
		while(rand() > RAND_MAX/10000)
			continue;
		
		//sort zone critique
		my_mutex_unlock(&mutex);
		printf("B\n");
		fflush(stdout);
	}
 return NULL;
}


pthread_t start_thread() {
    pthread_t th;
    pthread_create(&th, NULL, tatas_main, NULL);
    return th;
}






