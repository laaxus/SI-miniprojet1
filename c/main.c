#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include "alloc.h"
#include "factorize.h"
#include "threads.h"

const char* help_string =
    "Usage: fact [-N NUMBER_OF_THREADS] [other options] INPUT_FILE OUTPUT_FILE\n"
    "\n"
    " -N NUMBER_OF_THREADS  Specify how many threads the program should use.\n"
    "                       The argument should be a positive integer.\n"
    "                       By default, the program will use all available\n"
    "                       cores on the machine.\n"
    " -f  Use the fast algorithm.\n"
    " -s  Use the slow algorithm. This is enabled by default.\n"
    " INPUT_FILE  A file containing arbitrarily-long positive integers to\n"
    "             be processed by the program.\n"
    " OUTPUT_FILE  The output file. For every integer in INPUT_FILE, a line\n"
    "              will be written in OUTPUT_FILE. This line will contain,\n"
    "              space-separated:\n"
    "              - the integer that was factored,\n"
    "              - its prime factors, in increasing order, excluding\n"
    "                the number itself.\n"
    "              The ordering of the lines in the output may not match\n"
    "              the ordering of the numbers in the input.\n";

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
    if(argc < 3) print_usage();

    // Parses options
    
    int opt;
    int thread_count = 0;
    int fast_algorithm = 0;
    while((opt = getopt(argc, argv, "N:fs")) != -1) {
        switch(opt) {
            case 'N':
                if(sscanf(optarg, "%d", &thread_count) != 1 || thread_count <= 0) {
                    fprintf(stderr, "Expected a positive integer after the -N option\n");
                    print_usage();
                }
                break;
            case 'f':
                fast_algorithm = 1;
                break;
            case 's':
                fast_algorithm = 0;
                break;
            default:
                fprintf(stderr, "Unexpected option\n");
                print_usage();
        }
    }

    // Parses arguments
    if(argc != optind+2) {
        fprintf(stderr, "Expected exactly two arguments after the options\n");
        print_usage();
    }

    // Opens files
    FILE* input_file = fopen(argv[optind], "r");
    if(!input_file) {
        fprintf(stderr, "Could not open input file %s\n", argv[1]);
        print_usage();
    }
    FILE* output_file = fopen(argv[optind+1], "w");
    if(!output_file) {
        fprintf(stderr, "Could not open output file %s\n", argv[2]);
        print_usage();
    }

    // If the number of threads was not specified, then uses all available cores
    if(thread_count == 0) {
        thread_count = get_available_cpus();
    }

    // Starts the processing

    init_state(thread_count);

    pthread_t* threads = malloc(sizeof(pthread_t) * (thread_count+2));
    if (threads == NULL){
        exit(1);
    }

    // File input thread
    threads[0] = start_file_input_thread(input_file);
    // Output thread
    threads[1] = start_output_thread(output_file);
    // Processing threads
    for(int i = 0; i < thread_count; i++) {
        threads[i+2] = start_factorization_thread(fast_algorithm ? factorize : factorize_slow);
    }

    // Wait until the input is exhausted
    if(pthread_join(threads[0], NULL) != 0) {
        fprintf(stderr,"join failed error for thread %d\n", 0);
        exit(1);
    }

    // Sends termination messages to processing threads
    for(int i = 0; i < thread_count; i++) {
        bounded_queue_push(tasks_queue, NULL);
    }
    // Waits until all factorization threads are done
    for(int i = 0; i < thread_count; i++) {
        if(pthread_join(threads[i+2], NULL) != 0){
            fprintf(stderr,"join failed error for thread %d\n", i+2);
            exit(1);
        }
    }

    // Sends termination message to the output thread
    bounded_queue_push(results_queue, NULL);
    if(pthread_join(threads[1], NULL) != 0){
        fprintf(stderr,"join failed error for thread %d\n", 1);
        exit(1);
    }

    // Frees resources
    free(threads);
    destroy_state();

    return 0;
}
