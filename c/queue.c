#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "alloc.h"
#include "queue.h"

#ifndef DOXYGEN_SHOULD_SKIP_THIS
struct bounded_queue {
    void** volatile elements; // elements in the queue
    volatile int capacity; // capacity
    volatile int front, back; // front = next place to pop from, back = next place to push
    pthread_mutex_t mutex; // a mutex  to ensure safe multi-threaded access to the queue
    sem_t empty, full; // empty = number of elements in the queue, full = slots left in the queue
};
#endif

// Creates a queue with the given capacity

bounded_queue* bounded_queue_init(int capacity) {
    assert(capacity >= 1);
    // creates queue
    bounded_queue* queue = malloc_exit(sizeof(bounded_queue));
    // inits elements
    queue->elements = malloc_exit(capacity * sizeof(void*));
    queue->capacity = capacity;
    queue->front = 0;
    queue->back = 0;
    if(pthread_mutex_init(&queue->mutex, NULL) != 0){
        fprintf(stderr,"error mutex init\n");
        exit(1);
    }
    if(sem_init(&queue->empty, 0, 0) != 0){
        fprintf(stderr,"error sem_empty init\n");
        exit(1);
    }
    if(sem_init(&queue->full, 0, capacity) != 0){
        fprintf(stderr,"error sem_full init\n");
        exit(1);
    }
    return queue;
}

//Destroys a queue 

void bounded_queue_destroy(bounded_queue* queue) {
    if(sem_destroy(&queue->full)!= 0){
        fprintf(stderr,"error destroy sem_ful\n");
        exit(1);
    }
    if(sem_destroy(&queue->empty) != 0){
        fprintf(stderr,"error destroy sem_empty\n");
        exit(1);
    }
    if(pthread_mutex_destroy(&queue->mutex) != 0){
        fprintf(stderr,"error destroy mutex\n");
        exit(1);
    }
    free(queue->elements);
    free(queue);
}

//Push the given element in the queue

void bounded_queue_push(bounded_queue* queue, void* element) {
    sem_wait(&queue->full); // waits if the queue is full

    if(pthread_mutex_lock(&queue->mutex)!= 0){
        fprintf(stderr,"error muthex_lock\n");
        exit(1);
    }
    // critical section
    queue->elements[queue->back++] = element;
    if(queue->back == queue->capacity) queue->back = 0;
    // end of critical section
    if(pthread_mutex_unlock(&queue->mutex) != 0){
        fprintf(stderr,"error muthex_unlock\n");
        exit(1);
    }
    sem_post(&queue->empty); // adds one element to the buffer
}

void* bounded_queue_pop(bounded_queue* queue) {
    void* ret;

    sem_wait(&queue->empty); // waits if the queue is empty

    if(pthread_mutex_lock(&queue->mutex)!= 0){
        fprintf(stderr,"error muthex_lock\n");
        exit(1);
    }
    // critical section
    ret = queue->elements[queue->front++];
    if(queue->front == queue->capacity) queue->front = 0;
    // end of critical section
    if(pthread_mutex_unlock(&queue->mutex) != 0){
        fprintf(stderr,"error muthex_unlock\n");
        exit(1);
    }

    sem_post(&queue->full); // removes one element from the buffer
    return ret;
}
