#include "threads.h"
#include <stdlib.h>
#include <stdio.h>

int* mtx; 

int PHILOSOPHES;

void my_sem_init(int* sem, int n)
{
	*sem = n;
}

void my_sem_wait(int* sem)
{
	asm(
			"1:"
			"movl %0, %%eax;"
			"testl %%eax, %%eax;"    
			"je 1b;"
			"2:"
			"decl %0;"    
			:"=m"(*sem)
			:"m"(*sem)
			:"%eax"			
		); 
}

void my_sem_post(int* sem)
{
	asm(
			"incl %0;"
			:"=m"(*sem)
			:"m"(*sem)
			:
		); 
}


void my_mutex_init(int* mtx)
{
	*mtx = 0;
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
	 for(int i = 0; i < 100;i++)
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





