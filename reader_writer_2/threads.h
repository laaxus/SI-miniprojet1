/** \file threads.h
 * The different threads of the program. \ref init_state  must be called before using any functionality provided by this header.
#pragma once
#include <pthread.h>
#include <semaphore.h>

/**
 * \brief Initializes the semaphores required for the threads to function properly.
 */
void init_state();

/**
 * \brief Starts a writer thread.
 * \return The pthread_t object associated with the created thread.
 */
pthread_t start_writer_thread();

/**
 * \brief Starts a reader thread.
 * \return The pthread_t object associated with the created thread.
 */
pthread_t start_reader_thread();
