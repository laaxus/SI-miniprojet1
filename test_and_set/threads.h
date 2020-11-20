/** \file threads.h
 * The different threads of the program.
 */
#pragma once
#include <pthread.h>
#include <semaphore.h>

/**
 * \brief Array of mutex threads use
 */
extern pthread_mutex_t* mtx;

/**
 * \brief Number of threads
 */
extern int N;

/**
 * \brief Initializes  the lock, \ref N,the state required for the threads to function properly.
 */
void init_state(int thread_count);

/**
 * \brief Destroys the state that was initialized by \ref init_state.
 */
void destroy_state();

pthread_t start_thread();
/**
 * \brief Starts a  thread.
 * \return The pthread_t object associated with the created thread.
 */
 
