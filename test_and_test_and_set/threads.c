#include "threads.h"
#include <stdlib.h>
#include <stdio.h>

//number of thread
int N;

//home made mutex
long mutex;

void init_state(int nb) {
	N = nb;
	
	//define lock
	mutex = 0; 
}


void* tatas_main() {
	 int count = 6400 / N;
	 while(count--)
	{
		//entre zone critique
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

		while(rand() > RAND_MAX/10000)
			continue;
		
		//sort zone critique
		asm(
			"leave:"					
				"movl $0, %eax;"		
				"xchgl %eax, mutex;"				
		);
	}
 return NULL;
}


pthread_t start_thread() {
    pthread_t th;
    pthread_create(&th, NULL, tatas_main, NULL);
    return th;
}





