#include "threads.h"

int N;
int db[8];

pthread_mutex_t mutex;
int empty;
int full;

//number of item produced
int item_produced;

//number of item consumed
int item_consumed;

void my_sem_init(int* sem, int n)
{
	*sem = n;
}

void my_sem_wait(int* sem)
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

void my_sem_post(int* sem)
{
	asm(
			"incl (%1);"
			:"=r"(*sem)
			:"r"(sem)
		); 
}

void init_state() {
	N = 8;
	for(int i = 0; i < N; i++)
		db[i] = 0; 
	
	pthread_mutex_init(&mutex,NULL);
	my_sem_init(&empty, N);
	my_sem_init(&full, 0);
	item_produced = 0;
	item_consumed = 0;
}

/*
void* producer_main() {
	while(1)
	{
		//producing item time simulation
		while(rand() > RAND_MAX/10000)
			continue; 

		sem_wait(&empty); // attente d'une place libre
		pthread_mutex_lock(&mutex);
		

		if(item_produced >= 1024)
		{
			pthread_mutex_unlock(&mutex);
			sem_post(&full);
			return NULL; //stop production
		}

		 //insert item
		 for(int i = 0; i < N; i++)
		 {
			 if(db[i] == 0)
			 {
				  db[i] = 1;
				  break;
			 }
		 }
		 item_produced++;
	
		pthread_mutex_unlock(&mutex);
		sem_post(&full); // il y a une place remplie en plus
	}
	return NULL;
}

void* consumer_main() {
	while(1)
	{
		sem_wait(&full); // attente d'une place remplie
		pthread_mutex_lock(&mutex);
	
		if(item_consumed >= 1024)
		{
			pthread_mutex_unlock(&mutex);
			sem_post(&empty);
			return NULL; //stop consumption
		}

		//consume item
		 for(int i = 0; i < N; i++)
		 {
			 if(db[i] == 1)
			 {
				  db[i] = 0;
				  break;
			 }
		 }
			 
		//consuming
		item_consumed++;
		pthread_mutex_unlock(&mutex);
		
		//consuming item time simulation
		while(rand() > RAND_MAX/10000)
			continue;
		sem_post(&empty); // il y a une place libre en plus
	}
	return NULL;
}

pthread_t start_producer_thread() {
    pthread_t th;
    pthread_create(&th, NULL, producer_main, NULL);
    return th;
}

pthread_t start_consumer_thread() {
    pthread_t th;
    pthread_create(&th, NULL, consumer_main, NULL);
    return th;
}

*/

