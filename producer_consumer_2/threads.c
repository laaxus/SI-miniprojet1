#include "threads.h"



typedef struct {
	int count;
	int lock;
}sema;

void my_sem_init( sema* sem, int n)
{
	(*sem).count = n;
	(*sem).lock = 0;
}

void my_sem_wait( sema* sem)
{
	asm volatile(
			"1:"
			"movl %0, %%eax;"
			"testl %%eax, %%eax;"    
			"je 1b;"
			"2:"
			"movl $1, %%eax;"
			"xchgl %%eax, %1;"
			"testl %%eax, %%eax;"    
			"jne 1b;"
			"movl %0, %%eax;"
			"testl %%eax, %%eax;" 
			"jne 3f;"
			"movl $0, %1;"
			"je 1b;"
			"3:"
			"decl %0;"  
			"movl $0, %1;"			
			:"=m"((*sem).count),"=m"((*sem).lock)
			:"m"((*sem).count),"m"((*sem).lock)
			:"%eax","memory"			
		); 
}

void my_sem_post( sema* sem)
{
	asm volatile(
			"1:"
			"movl %1, %%eax;"
			"testl %%eax, %%eax;"    
			"jne 1b;"
			"2:"
			"movl $1, %%eax;"
			"xchgl %%eax, %1;"
			"testl %%eax, %%eax;"    
			"jne 1b;"
			"incl %0;"  
			"movl $0, %1;"			
			:"=m"((*sem).count),"=m"((*sem).lock)
			:"m"((*sem).count),"m"((*sem).lock)
			:"%eax","memory"
		); 
}


void my_mutex_init( int* mtx)
{
	*mtx = 0;
}


void my_mutex_lock( int* mtx)
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

void my_mutex_unlock( int* mtx)
{
	asm volatile(
			"movl $0, %0;"
			:"=m"(*mtx)
			:"m"(*mtx)
			:
		);
}


int N;
int db[8];

//home made mutex and semaphore
int mutex;
sema empty;
sema full;

//number of item produced
int item_produced;

//number of item consumed
int item_consumed;

//MAX
int PRODUCED_MAX = 100;
int CONSUMED_MAX = 100;


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
			my_sem_post(&full);
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
			my_sem_post(&empty);
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



