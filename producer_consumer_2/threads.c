#include "threads.h"
#include "mutex_sema.h"

int N;
int db[8];

//home made mutex and semaphore
volatile int mutex;
volatile sema empty;
volatile sema full;

//number of item produced
int item_produced;

//number of item consumed
int item_consumed;

//MAX
int PRODUCED_MAX = 1024;
int CONSUMED_MAX = 1024;


void init_state() {
	N = 8;
	for(int i = 0; i < N; i++)
		db[i] = 0; 

	my_mutex_init(&mutex);
	my_sem_init(&empty, N);
	my_sem_init(&full, 0);
	item_produced = 0;
	item_consumed = 0;
}


void* producer_main() {
	while(1)
	{
		//producing item time simulation
		while(rand() > RAND_MAX/10000)
			continue; 

		my_sem_wait(&empty); // attente d'une place libre
		my_mutex_lock(&mutex);
		
		if(item_produced >= PRODUCED_MAX)
		{

			my_mutex_unlock(&mutex);
			
			//nécéssaire sinon les autres threads ne pouront pas entrer dans la sémaphore pour terminer
			my_sem_post(&empty);
			return NULL; //stop production
		}
		
		 //insert item
		 db[item_produced % 8] = 1;
		 item_produced++;
		 
		 if(item_produced >= PRODUCED_MAX)
		{

			my_mutex_unlock(&mutex);
			my_sem_post(&full);
			
			//nécéssaire sinon les autres threads ne pouront pas entrer dans la sémaphore pour terminer
			my_sem_post(&empty);
			return NULL; //stop production
		}
		 
		my_mutex_unlock(&mutex);
		my_sem_post(&full); // il y a une place remplie en plus
	}
	return NULL;
}

void* consumer_main() {
	while(1)
	{
		my_sem_wait(&full); // attente d'une place remplie
		my_mutex_lock(&mutex);

		if(item_consumed >= CONSUMED_MAX)
		{
			my_mutex_unlock(&mutex);
			
			//nécéssaire sinon les autres threads ne pouront pas entrer dans la sémaphore pour terminer
			my_sem_post(&full);
			return NULL; //stop consumption
		}
		
		//consume item
		db[item_consumed % 8] = 0;
		//consuming
		item_consumed++;
		
		 if(item_consumed >= CONSUMED_MAX)
		{
			my_mutex_unlock(&mutex);
			my_sem_post(&empty);
			
			//nécéssaire sinon les autres threads ne pouront pas entrer dans la sémaphore pour terminer
			my_sem_post(&full);
			return NULL; //stop consumption
		}
			 
		my_mutex_unlock(&mutex);

		//consuming item time simulation
		while(rand() > RAND_MAX/10000)
			continue;
		
		my_sem_post(&empty); // il y a une place libre en plus
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



