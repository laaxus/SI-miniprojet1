#include "threads.h"
#include <stdlib.h>
#include <stdio.h>

pthread_mutex_t* mtx; 

int N;
long mutex;

void init_state(int nb) {
	N = nb;
	
	//define lock
	mutex = 0;
      
}

void destroy_state() {
    return;
}

void* tas_main() {
	 int count = 6400 / N;
	 while(count--)
	{
		//entre zone critique
		asm(
			"enter:"
				"movl $1, %eax;"
				"xchgl %eax, mutex;"
				"testl %eax, %eax;"    
				"jnz enter;"			
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
    pthread_create(&th, NULL, tas_main, NULL);
    return th;
}





