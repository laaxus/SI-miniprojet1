/** \file threads.h
 * The different threads of the program.
 */
#pragma once
#include <pthread.h>
#include <semaphore.h>

pthread_t start_writer_thread();
/**
 * \brief Starts a writer thread.
 * \return The pthread_t object associated with the created thread.
 */
 
 pthread_t start_reader_thread();
/**
 * \brief Starts a reader thread.
 * \return The pthread_t object associated with the created thread.
 */