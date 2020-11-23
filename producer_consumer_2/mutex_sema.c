#include "mutex_sema.h"

void my_mutex_init(volatile int* mtx)
{
	*mtx = 0;
}

void my_mutex_lock(volatile int* mtx)
{
	int done = 0;
	
	while(done == 0)
	{
		//Check in cache.
		while(*mtx == 1)
			continue;
		
		asm volatile(
				"movl $1, %%eax;"
				"xchgl %%eax, %0;"
				"testl %%eax, %%eax;"    
				"jne 1f;"
				"movl $1, %1;"
				"1:"
				:"=m"(*mtx),"=m"(done)
				:"m"(*mtx),"m"(done)
				:"%eax"
			); 
	}
}

void my_mutex_unlock(volatile int* mtx)
{
	asm volatile( 
			"movl $0, %0;"
			:"=m"(*mtx)
			:"m"(*mtx)
			:
		);
}

//------------- Semaphores -------------------------



void my_sem_init(volatile sema* sem, int n)
{
	(*sem).count = n;
	(*sem).lock = 0;
}

void my_sem_wait(volatile sema* sem)
{
	int done = 0;
	while(done == 0)
	{
		while((*sem).count == 0 || (*sem).lock == 1 )
			continue;
		
		asm volatile(
			
			"movl $1, %%eax;"
			"xchgl %%eax, %1;"
			"testl %%eax, %%eax;"    
			"jne 1f;"
			"movl %0, %%eax;"
			"testl %%eax, %%eax;" 
			"jne 3f;"
			"movl $0, %1;"
			"je 1f;"
			"3:"
			"decl %0;"  
			"movl $0, %1;"
			"movl $1, %2;"
			"1:"
			:"=m"((*sem).count),"=m"((*sem).lock),"=m"(done)
			:"m"((*sem).count),"m"((*sem).lock),"m"(done)
			:"%eax","memory"			
		); 
	}
}

void my_sem_post(volatile sema* sem)
{
	int done = 0;
	while(done == 0)
	{
		while((*sem).lock == 1 )
			continue;
		
		asm volatile(
				"movl $1, %%eax;"
				"xchgl %%eax, %1;"
				"testl %%eax, %%eax;"    
				"jne 1f;"
				"incl %0;"  
				"movl $0, %1;"	
				"movl $1, %2;"
				"1:"
				:"=m"((*sem).count),"=m"((*sem).lock),"=m"(done)
				:"m"((*sem).count),"m"((*sem).lock),"m"(done)
				:"%eax","memory"
		); 
	}
}

