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
 * \brief Number of philosophe/threads
 */
extern int PHILOSOPHES;

/**
 * \brief Initializes \ref mtx, \ref PHILOSOPHES, the state required for the threads to function properly.
 */
void init_state(int thread_count);

/**
 * \brief Destroys the state that was initialized by \ref init_state.
 */
void destroy_state();

/**
 * \brief Starts a philosophe thread.
 * \return The pthread_t object associated with the created thread.
 */
pthread_t start_philo_thread(void* arg);

 
