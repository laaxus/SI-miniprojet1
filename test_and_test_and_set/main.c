#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include "threads.h"



const char* help_string =
    "Usage: ph [-N NUMBER_OF_THREADS]  \n"
    "\n"
    " -N NUMBER_OF_THREADS             Specify how many threads the program should use.\n"
    "                      		       The argument should be a positive integer.\n"
    "                                  By default, the program will use all available\n"
    "                     		       cores on the machine.\n";
   

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
    if(argc < 2) print_usage();

    // Parses options
    
    int opt;
    int thread_count = 0;
    while((opt = getopt(argc, argv, "N:")) != -1) {
        switch(opt) {
            case 'N':
                thread_count = atoi(optarg);
				if(thread_count == 0)
					fprintf(stderr,"Expected a positive integer after the -N option\n");
                break;
			
            default:
                fprintf(stderr, "Unexpected option\n");
                print_usage();
        }
    }


	
    // If the number of threads was not specified for writers, then uses 1 core
    if(thread_count == 0) {
        thread_count = get_available_cpus();
    }
	
	
	//init semaphore
	init_state(thread_count);

	
    // Starts the processing
    pthread_t* threads= malloc(sizeof(pthread_t) * thread_count);
    if (threads == NULL){
        exit(1);
    }

    // Processing threads 
    for(int i = 0; i < thread_count; i++) {
        threads[i] = start_thread();
    }
    
    // Waits until all threads are done
    for(int i = 0; i < thread_count; i++) {
        if(pthread_join(threads[i], NULL) != 0){
            fprintf(stderr,"join failed error for thread %d\n", i);
            exit(1);
        }
    }
	

    // Frees resources
    free(threads);
	destroy_state();
	
	
    return 0;
}
