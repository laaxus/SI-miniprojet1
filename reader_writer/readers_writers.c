pthread_mutex_t mutex_readcount; // protège readcount
pthread_mutex_t mutex_writecount; // protège writecount
pthread_mutex_t mutex_z;
sem_t sem_read;
sem_t sem_write;
int readcount=0; // nombre de readers
int writecount=0;

sem_init(&sem_read, NULL, 1);
sem_init(&sem_write, NULL, 1);

  
void writer(void)
{
 while(true)
 {
   prepare_data();
   
   pthread_mutex_lock(&mutex_writecount);
   writecount++;
   if (writecount == 1) {
   		sem_wait(&sem_read);
   }
   pthread_mutex_unlock(&mutex_writecount);
   
   sem_wait(&sem_write);
     // section critique, un seul writer à la fois
   write_database();
   sem_post(&sem_write);
   
   pthread_mutex_lock(&mutex_writecount);
   writecount--;
   if (writecount == 0) {
   		sem_post(&sem_read);
   }
   pthread_mutex_unlock(&mutex_writecount);
   
   }
 }
}

void reader(void)
{
 while(true)
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
   
   read_database();
   
   pthread_mutex_lock(&mutex_readcount);
     // section critique
     readcount--;
     if(readcount==0)
     { // départ du dernier reader
       sem_post(&sem_write);
     }
   pthread_mutex_unlock(&mutex_readcount);
   process_data();
 }
}