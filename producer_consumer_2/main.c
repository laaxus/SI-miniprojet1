#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include "threads.h"



const char* help_string =
    "Usage: pc [-P NUMBER_OF_PRODUCER_THREADS] [-C NUMBER_OF_CONSUMER_THREADS] \n"
    "\n"
    " -P NUMBER_OF_PRODUCER_THREADS  Specify how many threads the program should use for producers.\n"
    "                      	         The argument should be a positive integer.\n"
    "                                By default, the program will use 2 threads for producer\n"
	" \n"
    " -C NUMBER_OF_CONSUMER_THREADS  Specify how many threads the program should use for consumers.\n"
    "                                The argument should be a positive integer.\n"
    "                                By default, the program will use 2 threads for consumers\n";

// Prints the help string and exits with an error code.
void print_usage() {
    fputs(help_string, stderr);
    exit(1);
}

// Gets the number of available CPUs on the computer.
int get_available_cpus() {
#ifdef WIN32
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    return sysinfo.dwNumberOfProcessors;
#else
    return sysconf(_SC_NPROCESSORS_ONLN);
#endif
}

int main(int argc, char **argv) {
    /*if(argc < 2) print_usage();

    // Parses options
    int opt;
    int thread_producer_count = 7;
	int thread_consumer_count = 2;
    while((opt = getopt(argc, argv, "P:C:")) != -1) {
        switch(opt) {
            case 'P':
				thread_producer_count = atoi(optarg);
				if(thread_producer_count == 0)
					fprintf(stderr,"Expected a positive integer after the -P option\n");
                break;
			case 'C':
				thread_consumer_count = atoi(optarg);
				if(thread_consumer_count == 0)
					fprintf(stderr,"Expected a positive integer after the -C option\n");
                break;
            default:
                fprintf(stderr,"Unexpected option\n");
                print_usage();
        }
    } 
	
    // If the number of threads was not specified for writers, then uses 1 core
    if(thread_producer_count == 0) {
        thread_producer_count = 2;
    }
	
	// If the number of threads was not specified for readers, then uses all available cores
    if(thread_consumer_count == 0) {
        thread_consumer_count = 2;
    }
	
	//init semaphore
	init_state();
   
    // Starts the processing
    pthread_t* threads_producer = malloc(sizeof(pthread_t) * thread_producer_count);
	pthread_t* threads_consumer = malloc(sizeof(pthread_t) * thread_consumer_count);
    if (threads_producer == NULL || threads_consumer == NULL){
        exit(1);
    }

   
    // Processing writer threads 
    for(int i = 0; i < thread_producer_count; i++) {
        threads_producer[i] = start_producer_thread();
    }
	
	 // Processing writer threads 
    for(int i = 0; i < thread_consumer_count; i++) {
        threads_consumer[i] = start_consumer_thread();
    }

    
    // Waits until all writer threads are done
    for(int i = 0; i < thread_producer_count; i++) {
        if(pthread_join(threads_producer[i], NULL) != 0){
            fprintf(stderr,"join failed error for thread %d\n", i);
            exit(1);
        }
    }
	
	// Waits until all reader threads are done
    for(int i = 0; i < thread_consumer_count; i++) {
        if(pthread_join(threads_consumer[i], NULL) != 0){
            fprintf(stderr,"join failed error for thread %d\n", i);
            exit(1);
        }
    }

    // Frees resources
    free(threads_producer);
	free(threads_consumer);
	
	*/
	int test = 0;
	
	my_sem_post(&test);
	
	printf("%d\n",test);
	
    return 0; 
}
