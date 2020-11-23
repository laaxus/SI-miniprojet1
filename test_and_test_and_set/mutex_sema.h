/** \file threads.h
 * The thread of the program.
 */
#pragma once

#ifndef STRUCTS
#define STRUCTS

typedef struct {
	int count;
	int lock;
}sema;
#endif

void my_mutex_init(volatile int* mutex);

void my_mutex_lock(volatile int* mutex);

void my_mutex_unlock(volatile int* mutex);


void my_sem_init(volatile sema* sem, int n);

void my_sem_wait(volatile sema* sem);

void my_sem_post(volatile sema* sem);
