#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "alloc.h"
#include "factorize.h"

// Sets rout to (x*x + c) % n. WARNING : rout must be initialized.
static void pollard_rho_f(mpz_t rout, const mpz_t x, const mpz_t n, int c) {
    // rout = x*x
    mpz_mul(rout, x, x);
    // rout += x
    mpz_add_ui(rout, rout, c);
    // rout %= n
    mpz_fdiv_r(rout, rout, n);
}

// Finds a non-trivial factor of n and sets d to it. WARNING : d must be initialized.
static void find_factor(mpz_t d, const mpz_t n, int c) {
    // Tests for multiples of 2
    // Divides n by 2, stores the result in d and returns the remainder
    if(mpz_fdiv_q_ui(d, n, 2) == 0) {
        return;
    }

    mpz_t a, b;
    mpz_inits(a, b, NULL);
    // initial values are a=2 and b=2
    mpz_set_ui(a, 2);
    mpz_set_ui(b, 2);
    mpz_set_ui(d, 1);

    // while(d == 1)
    while(mpz_cmp_ui(d, 1) == 0) {
        // a = f(a)
        pollard_rho_f(a, a, n, c);
        // b = f(f(b))
        pollard_rho_f(b, b, n, c);
        pollard_rho_f(b, b, n, c);

        // d = gcd(a-b, n)
        mpz_sub(d, a, b);
        mpz_gcd(d, d, n);
    }

    // clears a and b
    mpz_clears(a, b, NULL);

    // if d < n, all good
    // if d == n, run again with different c 
    if(mpz_cmp(d, n) == 0) {
        find_factor(d, n, c+1);
    }
}

// Compares two GMP integers.
static int mpz_compar(const void* mpz1, const void* mpz2) {
    const mpz_t* n1 = mpz1;
    const mpz_t* n2 = mpz2;
    return mpz_cmp(*n1, *n2);
}

//First function that we have implemanted with the Pollard's Rho algorithm

mpz_t* factorize(const mpz_t n, int* factors_length) {
    // Don't waste time on numbers <= 1 or on prime numbers 
    if(mpz_cmp_ui(n, 1) <= 0 || mpz_probab_prime_p(n, 25)) {
        *factors_length = 0;
        return malloc_exit(0);
    }
    int max_factors = mpz_sizeinbase(n, 2); // the number of bits is by far the maximum amount of factors
    mpz_t* factors = malloc_exit(sizeof(mpz_t) * max_factors);
    if(factors == NULL){
        exit(1);
    }
    int factor_count = 1;

    // Starts with n
    mpz_init_set(factors[0], n);

    for(int i = 0; i < factor_count; ++i) {
        // Keeps breaking down the i-th number until it's a prime
        while(!mpz_probab_prime_p(factors[i], 25)) {
            mpz_t tmp;
            mpz_init(tmp);
            factors[factor_count][0] = tmp[0];
            // Finds a non-trivial factor of the i-th number
            find_factor(factors[factor_count], factors[i], 1);
            // Divides the i-th number by its factor
            mpz_fdiv_q(factors[i], factors[i], factors[factor_count]);
            ++factor_count;
        }
    }
    
    // Sorts the numbers
    qsort(factors, factor_count, sizeof(mpz_t), mpz_compar);
    // Removes duplicates
    int i = 0, j = 0;
    while(j < factor_count) {
        ++j;
        while(j < factor_count && mpz_cmp(factors[i], factors[j]) == 0) {
            mpz_clear(factors[j]);
            ++j;
        }
        ++i;
        if(j < factor_count) {
            memcpy(factors[i], factors[j], sizeof(mpz_t));
        }
    }
    *factors_length = i;

    return factors;
}

//Second function that we have implemanted, it is slower than the previous one

mpz_t* factorize_slow(const mpz_t n, int* factors_length) {
    int max_factors = mpz_sizeinbase(n, 2); // the number of bits is by far the maximum amount of factors
    mpz_t* factors = malloc_exit(sizeof(mpz_t) * max_factors);
    if(factors == NULL){
        exit(1);
    }
    int factor_count = 0;

    mpz_t i; // int i = 2
    mpz_init_set_ui(i, 2);
    mpz_t m; // int m = n
    mpz_init_set(m, n);

    mpz_t isq, mmi; // i squared, m%i (m mod i)
    mpz_inits(isq, mmi, 0);

    // for(; i*i <= n && m > 1; ++i) {
    for(; mpz_mul(isq, i, i), mpz_cmp(isq, m) <= 0 && mpz_cmp_ui(m, 1) > 0; mpz_add_ui(i, i, 1)) {
        mpz_fdiv_r(mmi, m, i);
        // if(m%i == 0)
        if(mpz_sgn(mmi) == 0) {
            // adds factor
            mpz_init_set(factors[factor_count++], i);
            // removes it from m
            do {
                // m /= i
                mpz_fdiv_q(m, m, i);
                mpz_fdiv_r(mmi, m, i);
                // while(m%i == 0)
            } while(mpz_sgn(mmi) == 0);
        }
    }

    // if(m > 1) and m != n then adds number
    if(mpz_cmp_ui(m, 1) > 0 && mpz_cmp(m, n) != 0) {
        mpz_init_set(factors[factor_count++], m);
    }

    mpz_clears(isq, mmi, i, m, 0);

    *factors_length = factor_count;
    return factors;
}
