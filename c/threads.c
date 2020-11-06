#include "alloc.h"
#include "factorize.h"
#include "threads.h"

bounded_queue* tasks_queue;
bounded_queue* results_queue;

void init_state(int thread_count) {
    tasks_queue = bounded_queue_init(thread_count * 2);
    results_queue = bounded_queue_init(thread_count * 2);
}

void destroy_state() {
    bounded_queue_destroy(tasks_queue);
    bounded_queue_destroy(results_queue);
}

void* factorization_main(void* data) {
    factorization_func_t factorization_func = data;

    while(1) {
        // Receives the next number
        void* element = bounded_queue_pop(tasks_queue);
        // If there is no message, the thread is done
        if(element == NULL) {
            return NULL;
        }
        // Otherwise, it factorizes the number
        task_message* task = element;
        int factor_count;
        mpz_t* factors = factorization_func(task->number, &factor_count);

        // Builds the result message
        result_message* result = malloc_exit(sizeof(result_message));
        mpz_swap(result->number, task->number); // can't use = with mpz_t
        result->source_id = task->source_id;
        result->factor_count = factor_count;
        result->factors = factors;

        // Frees the received message
        free(task);

        // Sends the result message to output
        bounded_queue_push(results_queue, result);
    }
}

pthread_t start_factorization_thread(factorization_func_t factorization_func) {
    pthread_t th;
    pthread_create(&th, NULL, factorization_main, factorization_func);
    return th;
}

void* file_input_main(void* data) {
    FILE* file = (FILE*)data; // the data is the file identifier

    while(1) {
        // Reads number
        mpz_t input_number;
        mpz_init(input_number);
        if(gmp_fscanf(file, "%Zd", input_number) != 1) {
            // If couldn't read for some reason stops here
            mpz_clear(input_number);
            break;
        }

        // Allocates task message
        task_message* task = malloc_exit(sizeof(task_message));
        mpz_swap(task->number, input_number); // can't use = with mpz_t
        task->source_id = 0;

        // Sends it
        bounded_queue_push(tasks_queue, task);
    }

    // Closes the file pointer
    fclose(file);

    return NULL;
}

// Creates the thread that will read the input_file

pthread_t start_file_input_thread(FILE* file) {
    pthread_t th;
    if(pthread_create(&th, NULL, file_input_main, file) != 0) {
        fprintf(stderr, "couldn't create thread\n");
        exit(1);
    }
    return th;
}

void* output_main(void* data) {
    FILE* output_file = data; // the data is the file identifier

    void* message;
    // Processes incoming messages, stops if the message is NULL
    while((message = bounded_queue_pop(results_queue)) != NULL) {
        result_message* result = message;

        if(result->source_id == 0) {
            // Writes to the file
            gmp_fprintf(output_file, "%Zd", result->number);
            mpz_clear(result->number);
            for(int i = 0; i < result->factor_count; ++i) {
                gmp_fprintf(output_file, " %Zd", result->factors[i]);
                mpz_clear(result->factors[i]);
            }
            free(result->factors);
            fprintf(output_file, "\n");
        }

        // Frees the received message
        free(result);
    }

    // Closes the file pointer
    fclose(output_file);

    return NULL;
}

// Creates the thread that will write the results in the output file
pthread_t start_output_thread(FILE* output_file) {
    pthread_t th;
    if(pthread_create(&th, NULL, output_main, output_file) != 0) {
        fprintf(stderr, "couldn't create thread\n");
        exit(1);
    }
    return th;
}
