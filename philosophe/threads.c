#include "threads.h"
#include <stdlib.h>
#include <stdio.h>

pthread_mutex_t* mtx; 

int PHILOSOPHES;

void init_state(int nb) {
	PHILOSOPHES = nb;
	mtx = malloc(sizeof(pthread_mutex_t) * nb);
	
	if(mtx == NULL)
		exit(1);
	
	for(int i = 0; i < nb;i++)
		if(pthread_mutex_init(&mtx[i],NULL) != 0)
		{
			printf("error mutex init\n");
			exit(1);
		}
}

void destroy_state() {
    free(mtx);
}

void* philo_main(void* arg) {
	 int *id=(int *) arg;
	 int left = *id;
	 int right = (left + 1) % PHILOSOPHES;
	 for(int i = 0; i < 1000000;i++)
	{
		 // philosophe pense
		 if(left<right) {
			pthread_mutex_lock(&mtx[left]);
			pthread_mutex_lock(&mtx[right]);
		 }
		 else {
		 
			 if(left != right)// N > 1
			 {
				pthread_mutex_lock(&mtx[right]);
				pthread_mutex_lock(&mtx[left]);
			 }
			 else // N == 1
				pthread_mutex_lock(&mtx[left]);
		 }
		 
		 //mange
		 
		 //il a plus faim
		 if(left != right)// N > 1
		 {
			pthread_mutex_unlock(&mtx[left]);
			pthread_mutex_unlock(&mtx[right]);
		 }
		 else // N == 1
			pthread_mutex_unlock(&mtx[left]);
	 }
	 
 return NULL;
}


pthread_t start_philo_thread(int arg) {
    pthread_t th;
    pthread_create(&th, NULL, philo_main, &arg);
    return th;
}





