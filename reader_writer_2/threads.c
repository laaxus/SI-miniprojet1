#include "threads.h"

int mutex_readcount; 
int mutex_writecount; 
int mutex_z;
int sem_read;
int sem_write;

int readcount=0; // nombre de readers
int writecount=0;

int NBWRITING=30720;
int NBREADING=122880;

int database = 0;

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

void init_state() {
	my_sem_init(&sem_read, 1);
	my_sem_init(&sem_write, 1);
	my_mutex_init(&mutex_readcount);
	my_mutex_init(&mutex_writecount);
	my_mutex_init(&mutex_z);
}

void* writer_main() {
	for(int i = 0; i < NBWRITING;i++)
	{
		my_mutex_lock(&mutex_writecount);
		writecount++;
		if (writecount == 1) {
			my_sem_wait(&sem_read);
		}
		my_mutex_unlock(&mutex_writecount);

		my_sem_wait(&sem_write);
		 // section critique, un seul writer à la fois
		 
		 // write database
				database++;
				
		my_sem_post(&sem_write);

		my_mutex_lock(&mutex_writecount);
		writecount--;
		if (writecount == 0) {
			my_sem_post(&sem_read);
		}
		my_mutex_unlock(&mutex_writecount);
	}
	return NULL;
}

void* reader_main() {
	for(int i = 0; i < NBREADING;i++)
	{
		my_mutex_lock(&mutex_z);
		my_sem_wait(&sem_read);

		my_mutex_lock(&mutex_readcount);
		// section critique
		readcount++;
		if (readcount==1)
		{ // arrivée du premier reader
		my_sem_wait(&sem_write);
		}
		my_mutex_unlock(&mutex_readcount);
		my_sem_post(&sem_read);
		my_mutex_unlock(&mutex_z);

		//read database
		int foo = database;

		my_mutex_lock(&mutex_readcount);
		// section critique
		readcount--;
		if(readcount==0)
		{ // départ du dernier reader
		my_sem_post(&sem_write);
		}
		my_mutex_unlock(&mutex_readcount);
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



