#include <stdarg.h>
#include <stdlib.h>
#include <time.h>
#include <CUnit/Basic.h>
#include "factorize.h"
#include "queue.h"

static factorization_func_t FACTORIZATION_FUNCTIONS[2] = {factorize, factorize_slow};

void assert_factorization(unsigned long long number, int expected_factors, ...) {
    //Collects the prime factors of number with the two functions that we implemented, factorize and factorize_slow and compares with the expected ones.
    for(int j = 0; j < 2; ++j) { 
        mpz_t n;
        mpz_init(n);
        // Converts number to GMP number
        mpz_import(n, 1, -1, sizeof number, 0, 0, &number);
        int factors_count;
        mpz_t* factors = FACTORIZATION_FUNCTIONS[j](n, &factors_count);
        mpz_clear(n);
        // There must be enough factors
        CU_ASSERT_EQUAL_FATAL(factors_count, expected_factors);

        mpz_t tmp;
        mpz_init(tmp);
        va_list args;
        va_start(args, expected_factors);

        
        for(int i = 0; i < expected_factors; ++i) {
            // Converts arg to GMP number
            unsigned long long next_arg = va_arg(args, unsigned long long);
            mpz_import(tmp, 1, -1, sizeof next_arg, 0, 0, &next_arg);
            // The factors must be the ones that are expected
            CU_ASSERT(mpz_cmp(factors[i], tmp) == 0);
            // Frees GMP number
            mpz_clear(factors[i]);
        }
        va_end(args);
        mpz_clear(tmp);
        free(factors);
    }
}

//Tests for the factorization

void test_factorize() {
    assert_factorization(16ULL, 1, 2ULL);
    assert_factorization(25ULL, 1, 5ULL);
}

void test_factorize2() {
    assert_factorization(15ULL, 2, 3ULL, 5ULL);
    assert_factorization(20ULL, 2, 2ULL, 5ULL);
    assert_factorization(25ULL, 1, 5ULL);
    assert_factorization(30ULL, 3, 2ULL,3ULL, 5ULL);
    assert_factorization(146ULL, 2, 2ULL, 73ULL);
    assert_factorization(566ULL, 2, 2ULL, 283ULL);
    assert_factorization(17ULL, 0);
    assert_factorization(2ULL, 0);
    assert_factorization(1ULL, 0);
    assert_factorization(2147483647ULL, 0); //int max
    assert_factorization(18446744073709551615ULL,7,3ULL,5ULL,17ULL,257ULL,641ULL,65537ULL,6700417ULL); //ULL_MAX
}

void test_factorize3() {
    assert_factorization(8ULL,1,2ULL);
    assert_factorization(25ULL, 1, 5ULL);
    assert_factorization(30ULL, 3, 2ULL,3ULL, 5ULL);
    assert_factorization(146ULL, 2, 2ULL, 73ULL);
    assert_factorization(566ULL, 2, 2ULL, 283ULL);
    assert_factorization(17ULL, 0);
    assert_factorization(2ULL, 0);
    assert_factorization(1ULL, 0);
    assert_factorization(18ULL,2,2ULL,3ULL);
    assert_factorization(59ULL, 0);
    assert_factorization(64ULL, 1,2ULL);
}

static bounded_queue* test_q;
static int pushed_number = 42;
static int wait_millis = 100;

// sleeps for `ms` milli seconds
void msleep(int ms) {
    clock_t t1 = clock();

    // sadly sleep is broken on jenkins
    while((double)(clock() - t1)/CLOCKS_PER_SEC < ms * 0.001);
}

void* push_later_func(void* data) {
    (void)data; // removes warning
    // waits
    msleep(wait_millis);
    // pushes
    int* element = malloc(sizeof(int));
    *element = pushed_number;
    bounded_queue_push(test_q, element);
    return NULL;
}

void push_later() {
    pthread_t th;
    pthread_create(&th, NULL, push_later_func, NULL);
}

// tests that the queue waits for an element if it's empty
void test_queue_wait_empty() {
    test_q = bounded_queue_init(1);

    push_later();
    clock_t t = clock();
    int* element = bounded_queue_pop(test_q);
    t = clock() - t;

    CU_ASSERT(*element == pushed_number);
    CU_ASSERT((double)t / CLOCKS_PER_SEC >= wait_millis * 0.001 * 0.8);
    free(element);

    bounded_queue_destroy(test_q);
}

void* pop_later_func(void* data) {
    (void)data; // removes warning
    // waits
    msleep(wait_millis);
    // pops
    int* element = bounded_queue_pop(test_q);
    CU_ASSERT(*element == pushed_number);
    free(element);

    return NULL;
}

void pop_later() {
    pthread_t th;
    pthread_create(&th, NULL, pop_later_func, NULL);
}

// tests that the queue waits for a free space if it's full
void test_queue_wait_full() {
    test_q = bounded_queue_init(1);

    int* el1 = malloc(sizeof(int));
    int* el2 = malloc(sizeof(int));
    *el1 = pushed_number;
    *el2 = pushed_number+1;

    // this first push should be very fast
    bounded_queue_push(test_q, el1);

    // the next push should wait for a pop() to happen
    pop_later();
    clock_t t = clock();
    bounded_queue_push(test_q, el2);
    t = clock() - t;

    CU_ASSERT((double)t / CLOCKS_PER_SEC >= wait_millis * 0.001 * 0.8);

    // checks that the second element is still in the queue
    CU_ASSERT_EQUAL(bounded_queue_pop(test_q), el2);
    free(el2);

    bounded_queue_destroy(test_q);
}

int main() {
    CU_pSuite pSuite = NULL;

    if(CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();
    
    pSuite = CU_add_suite("Suite 1", NULL, NULL);
    if(!pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if(NULL == CU_add_test(pSuite, "test of factorize() and factorize_slow()", test_factorize)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if(NULL == CU_add_test(pSuite, "test2 of factorize() and factorize_slow()", test_factorize2)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if(NULL == CU_add_test(pSuite, "test3 of factorize() and factorize_slow()", test_factorize3)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if(NULL == CU_add_test(pSuite, "queue pop waits for elements", test_queue_wait_empty)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if(NULL == CU_add_test(pSuite, "queue push waits for an empty space", test_queue_wait_full)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    int failed_tests =  CU_get_number_of_tests_failed();
    CU_cleanup_registry();
    return failed_tests || CU_get_error();
}
