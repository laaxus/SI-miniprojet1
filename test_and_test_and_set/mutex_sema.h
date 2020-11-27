/** \file mutex_sema.h
 * Home made semaphore and mutex
 */
#pragma once

#ifndef STRUCTS
#define STRUCTS

/**
 * \brief Home made sémaphore struct
 */
typedef struct {
	int count;
	int lock;
}sema;
#endif

/**
 * \brief Home made mutex_init. Initialise mutex to 0.
 */
void my_mutex_init(volatile int* mutex);

/**
 * \brief Home made mutex_lock. If it's already locked,  retry. If not, lock the mutex by setting it to 1.
 */
void my_mutex_lock(volatile int* mutex);

/**
 * \brief Home made mutex_unlock. Unlock the mutex by setting it to 0.
 */
void my_mutex_unlock(volatile int* mutex);

/**
 * \brief Home made sémaphore_init. Initialise sem.count to n and sem.lock to 0.
 */
void my_sem_init(volatile sema* sem, int n);

/**
 * \brief Home made semaphore_wait. First (Step 1, in the cache), it check if the semaphore.count > 0 and if the semaphore is not locked, like a mutex. If it's already locked, or sem.count == 0, retry. When it finally get locked , check (Step 2, in the bus) if sem.count > 0, if so, decrement it then unlock the semaphore, else, get back to (Step 1).
 */
void my_sem_wait(volatile sema* sem);

/**
 * \brief Home made semaphore_post. First (in the cache), it check if the semaphore is not locked, like a mutex. If it's already locked, retry. When it finally get locked, increment sem.count, then unlock the semaphore.
 */
void my_sem_post(volatile sema* sem);
