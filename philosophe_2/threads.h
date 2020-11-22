/** \file threads.h
 * The different threads of the program.
 */
#pragma once
#include <pthread.h>
#include <semaphore.h>

/**
 * \brief Array of mutex threads use
 */
extern int* mtx;

/**
 * \brief Number of philosophe/threads
 */
extern int PHILOSOPHES;

/**
 * \brief Initializes \ref mtx, \ref PHILOSOPHES, the state required for the threads to function properly.
 */
void init_state(int thread_count);


/**
 * \brief Starts a philosophe thread.
 * \return The pthread_t object associated with the created thread.
 */
pthread_t start_philo_thread(int arg);

 
