#include "threads.h"
#include "mutex_sema.h"
#include "stdio.h"


volatile int mutex_readcount; 
volatile int mutex_writecount; 
volatile int mutex_z;
volatile sema sem_read;
volatile sema sem_write;

int readcount=0; // nombre de readers
int writecount=0;

int NBWRITING=61440;
int NBREADING=245760;

int database = 0;


void init_state() {
	my_sem_init_ts(&sem_read, 1);
	my_sem_init_ts(&sem_write, 1);
	my_mutex_init_ts(&mutex_readcount);
	my_mutex_init_ts(&mutex_writecount);
	my_mutex_init_ts(&mutex_z);
}

void* writer_main() {
	for(int i = 0; i < NBWRITING;i++)
	{
		//prepare database
		
		my_mutex_lock_ts(&mutex_writecount);

		writecount++;
		
		if (writecount == 1) {
			my_sem_wait_ts(&sem_read);
		}

		my_mutex_unlock_ts(&mutex_writecount);
		my_sem_wait_ts(&sem_write);
		// section critique, un seul writer à la fois
		 
		//----------- write database --------
				database++;
		//------------------------------------
		
		my_sem_post_ts(&sem_write);
		
		my_mutex_lock_ts(&mutex_writecount);
		
		writecount--;
		if (writecount == 0) {
			my_sem_post_ts(&sem_read);
		}

		my_mutex_unlock_ts(&mutex_writecount);
	}
	return NULL;
}

void* reader_main() {
	for(int i = 0; i < NBREADING;i++)
	{
		my_mutex_lock_ts(&mutex_z);
		my_sem_wait_ts(&sem_read);
		my_mutex_lock_ts(&mutex_readcount);
	
		// section critique
		readcount++;
		
		if (readcount==1)
		{ // arrivée du premier reader
			my_sem_wait_ts(&sem_write);
		}
		
		my_mutex_unlock_ts(&mutex_readcount);
		my_sem_post_ts(&sem_read);
		my_mutex_unlock_ts(&mutex_z);

		//--------- read database ----------
		// int foo = database //produit un warning
		//-----------------------------------
		
		my_mutex_lock_ts(&mutex_readcount);
	
		// section critique
		readcount--;
		
		if(readcount==0)
		{ // départ du dernier reader
			my_sem_post_ts(&sem_write);
		}

		my_mutex_unlock_ts(&mutex_readcount);
	}
	return NULL;
}

pthread_t start_writer_thread() {
    pthread_t th;
    pthread_create(&th, NULL, writer_main, NULL);
    return th;
}

pthread_t start_reader_thread() {
    pthread_t th;
    pthread_create(&th, NULL, reader_main, NULL);
    return th;
}



