/** \file threads.h
 * The different threads of the program. 
 */
#pragma once
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * \brief Initializes the semaphores and mutex required for the threads to function properly.
 */
void init_state();



pthread_t start_producer_thread();
/**
 * \brief Starts a producer thread.
 * \return The pthread_t object associated with the created thread.
 */
 
 pthread_t start_consumer_thread();
/**
 * \brief Starts a consumer thread.
 * \return The pthread_t object associated with the created thread.
 */