/** \file threads.h
 * The thread of the program.
 */
#pragma once
#include <pthread.h>
#include <semaphore.h>


/**
 * \brief Number of threads
 */
extern int N;

/**
 * \brief Initializes the lock, \ref N, the state required for the threads to function properly.
 */
void init_state(int thread_count);


/**
 * \brief Starts a thread.
 * \return The pthread_t object associated with the created thread.
 */
pthread_t start_thread();

void my_mutex_init(volatile int* mutex);

void my_mutex_lock(volatile int* mutex);

void my_mutex_unlock(volatile int* mutex);

 
