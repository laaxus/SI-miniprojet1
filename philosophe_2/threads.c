#include "threads.h"
#include <stdlib.h>
#include <stdio.h>

int* mtx; 

int PHILOSOPHES;

//nb de fois qu'il mange et pense
int PM_MAX = 10000;



void my_mutex_init(int* mtx)
{
	*mtx = 0;
}


void my_mutex_lock(int* mtx)
{
	asm volatile(
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
	asm volatile(
			"movl $0, %0;"
			:"=m"(*mtx)
			:"m"(*mtx)
			:
		);
}

void init_state(int nb) {
	PHILOSOPHES = nb;
	mtx = (int *) malloc(sizeof(int) * nb);
	
	if(mtx == NULL)
		exit(1);
	
	for(int i = 0; i < nb;i++)
		my_mutex_init(&mtx[i]);
		
}



void* philo_main(void* arg) {
	 int *id = (int *) arg;
	 int left = *id;
	 int right = (left + 1) % PHILOSOPHES;
	 for(int i = 0; i < PM_MAX;i++)
	{
		 // philosophe pense
		 if(left<right) {
		 my_mutex_lock(&mtx[left]);
		 my_mutex_lock(&mtx[right]);
		 }
		 else {
		 my_mutex_lock(&mtx[right]);
		 my_mutex_lock(&mtx[left]);
		 }
		 
		 //mange
		 
		 //il a plus faim
		 my_mutex_unlock(&mtx[left]);
		 my_mutex_unlock(&mtx[right]);
	 }
 return NULL;
}


pthread_t start_philo_thread(int arg) {
    pthread_t th;
    pthread_create(&th, NULL, philo_main, &arg);
    return th;
}





