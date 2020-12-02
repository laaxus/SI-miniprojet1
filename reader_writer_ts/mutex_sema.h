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

//TTS

void my_mutex_init_tts(volatile int* mutex);

void my_mutex_lock_tts(volatile int* mutex);

void my_mutex_unlock_tts(volatile int* mutex);


void my_sem_init_tts(volatile sema* sem, int n);

void my_sem_wait_tts(volatile sema* sem);

void my_sem_post_tts(volatile sema* sem);


//TS

void my_mutex_init_ts(volatile int* mutex);

void my_mutex_lock_ts(volatile int* mutex);

void my_mutex_unlock_ts(volatile int* mutex);


void my_sem_init_ts(volatile sema* sem, int n);

void my_sem_wait_ts(volatile sema* sem);

void my_sem_post_ts(volatile sema* sem);
