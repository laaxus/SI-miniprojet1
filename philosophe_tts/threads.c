#include "threads.h"
#include "mutex_sema.h"
#include <stdlib.h>
#include <stdio.h>

volatile int* mtx; 

int PHILOSOPHES;

//nb de fois qu'il mange et pense
int PM_MAX = 1000000;

void init_state(int nb) {
	PHILOSOPHES = nb;
	mtx = (int *) malloc(sizeof(int) * nb);
	
	if(mtx == NULL)
		exit(1);
	
	for(int i = 0; i < nb;i++)
		my_mutex_init_tts(&mtx[i]);
		
}



void* philo_main(void* arg) {
	 int left = *((int*)arg);
	 int right = (left + 1) % PHILOSOPHES;
	 
	 for(int i = 0; i < PM_MAX;i++)
	{
	 // philosophe pense
		 if(left<right) {
			my_mutex_lock_tts(&mtx[left]);
			my_mutex_lock_tts(&mtx[right]);
		 }
		 else {
		 
			 if(left != right)// N > 1
			 {
				my_mutex_lock_tts(&mtx[right]);
				my_mutex_lock_tts(&mtx[left]);
			 }
			 else // N == 1
				my_mutex_lock_tts(&mtx[left]);
		 }
		 
		 //mange
		 
		 //il a plus faim
		 if(left != right)// N > 1
		 {
			my_mutex_unlock_tts(&mtx[left]);
			my_mutex_unlock_tts(&mtx[right]);
		 }
		 else // N == 1
			my_mutex_unlock_tts(&mtx[left]);
	 }
 return NULL;
}


pthread_t start_philo_thread(void* arg) {
    pthread_t th;
    pthread_create(&th, NULL, philo_main, arg);
    return th;
}





