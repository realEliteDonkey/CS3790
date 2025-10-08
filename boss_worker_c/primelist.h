#ifndef PRIME_LIST_STRUCT_H
#define PRIME_LIST_STRUCT_H


/**
 * @brief Structure to hold dynamic array along with a 
 * counter of prime numbers added to array
 * 
 * @param max_primes 
 * @return PrimeList* 
 */
typedef struct PrimeList {
    unsigned num_primes;
    int primes[];
} PrimeList;


PrimeList* new_prime_list(size_t max_primes);
int get_primes(PrimeList* pl, const char* dir_name);


#endif
