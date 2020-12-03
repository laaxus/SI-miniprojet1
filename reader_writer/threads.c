#include "threads.h"

pthread_mutex_t mutex_readcount; // protège readcount
pthread_mutex_t mutex_writecount; // protège writecount
pthread_mutex_t mutex_z;
sem_t sem_read;
sem_t sem_write;

int readcount=0; // nombre de readers
int writecount=0;

int NBWRITING = 12800;
int NBREADING = 51200;

int database = 0;

void init_state() {
	sem_init(&sem_read, 0, 1);
	sem_init(&sem_write, 0, 1);
	pthread_mutex_init(&mutex_readcount,NULL);
	pthread_mutex_init(&mutex_writecount,NULL);
	pthread_mutex_init(&mutex_z,NULL);
}

void* writer_main() {
	for(int i = 0; i < NBWRITING;i++)
	{
		pthread_mutex_lock(&mutex_writecount);
		writecount++;
		if (writecount == 1) {
			sem_wait(&sem_read);
		}
		pthread_mutex_unlock(&mutex_writecount);

		sem_wait(&sem_write);
		 // section critique, un seul writer à la fois
		 
		 // write database
				database++;
				
		sem_post(&sem_write);

		pthread_mutex_lock(&mutex_writecount);
		writecount--;
		if (writecount == 0) {
			sem_post(&sem_read);
		}
		pthread_mutex_unlock(&mutex_writecount);
	}
	return NULL;
}

void* reader_main() {
	for(int i = 0; i < NBREADING;i++)
	{
		pthread_mutex_lock(&mutex_z);
		sem_wait(&sem_read);

		pthread_mutex_lock(&mutex_readcount);
		// section critique
		readcount++;
		if (readcount==1)
		{ // arrivée du premier reader
		sem_wait(&sem_write);
		}
		pthread_mutex_unlock(&mutex_readcount);
		sem_post(&sem_read);
		pthread_mutex_unlock(&mutex_z);

		//read database
		//int foo = database;

		pthread_mutex_lock(&mutex_readcount);
		// section critique
		readcount--;
		if(readcount==0)
		{ // départ du dernier reader
		sem_post(&sem_write);
		}
		pthread_mutex_unlock(&mutex_readcount);
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



