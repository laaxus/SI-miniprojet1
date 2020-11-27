#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include "threads.h"



const char* help_string =
    "Usage: rw [-W NUMBER_OF_WRITER_THREADS] [-R NUMBER_OF_READER_THREADS] \n"
    "\n"
    " -W NUMBER_OF_WRITER_THREADS  Specify how many threads the program should use for writers.\n"
    "                      		   The argument should be a positive integer.\n"
    "                              By default, the program will use 1 thread for writers\n"
	"\n"
    " -R NUMBER_OF_READER_THREADS  Specify how many threads the program should use for readers.\n"
    "                      		   The argument should be a positive integer.\n"
    "                              By default, the program will use 1 thread for readers\n";

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
    int thread_writer_count = 0;
	int thread_reader_count = 0;
    while((opt = getopt(argc, argv, "R:W:")) != -1) {
        switch(opt) {
            case 'W':
                thread_writer_count = atoi(optarg);
				if(thread_writer_count == 0)
					fprintf(stderr,"Expected a positive integer after the -W option\n");
                break;
			case 'R':
                thread_reader_count = atoi(optarg);
				if(thread_reader_count == 0)
					fprintf(stderr,"Expected a positive integer after the -R option\n");
                break;
            default:
                fprintf(stderr, "Unexpected option\n");
                print_usage();
        }
    }

   

    // If the number of threads was not specified for writers, then uses 1 thread.
    if(thread_writer_count == 0) {
        thread_writer_count = 1;
    }
	
	// If the number of threads was not specified for readers, then uses 1 thread.
    if(thread_reader_count == 0) {
        thread_reader_count = 1;
    }
	
	//init semaphore
	init_state();
	
	
    // Starts the processing
    pthread_t* threads_writer = malloc(sizeof(pthread_t) * thread_writer_count);
	pthread_t* threads_reader = malloc(sizeof(pthread_t) * thread_reader_count);
    if (threads_writer == NULL || threads_reader == NULL){
        exit(1);
    }

   
    // Processing writer threads 
    for(int i = 0; i < thread_writer_count; i++) {
        threads_writer[i] = start_writer_thread();
    }
	
	 // Processing writer threads 
    for(int i = 0; i < thread_reader_count; i++) {
        threads_reader[i] = start_reader_thread();
    }

    
    // Waits until all writer threads are done
    for(int i = 0; i < thread_writer_count; i++) {
        if(pthread_join(threads_writer[i], NULL) != 0){
            fprintf(stderr,"join failed error for thread %d\n", i);
            exit(1);
        }
    }
	
	// Waits until all reader threads are done
    for(int i = 0; i < thread_reader_count; i++) {
        if(pthread_join(threads_reader[i], NULL) != 0){
            fprintf(stderr,"join failed error for thread %d\n", i);
            exit(1);
        }
    }

    // Frees resources
    free(threads_writer);
	free(threads_reader);

    return 0;
}
