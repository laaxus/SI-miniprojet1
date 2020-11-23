/** \file threads.h
 * The thread of the program.
 */
#pragma once
#include <pthread.h>



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



 
