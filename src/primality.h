#ifndef PRIMALITY_H
#define PRIMALITY_H

#include <iostream>
#include <vector>

#include <cmath>
#include <cstddef>
#include <cstdlib>

#include "unsigned.h"

using std::cout;
using std::endl;
using std::exit;
using std::log;
using std::max;
using std::vector;

/* Enums */
typedef enum { NEITHER, COMPOSITE, PRIME } Primality;

/* Functions */
/**
 * Performs a primality test on a number
 * @tparam T Unsigned integer
 * @param number Number to test
 * @return Primality enum of the test outcome
 */
template <typename T>
Primality primality_test(T number) {
    if (number == 1) {
        return NEITHER;
    }
    if ((number == 2) || (number == 3)) {
        return PRIME;
    }
    if ((!(number % 2)) || (!(number % 3))) {
        return COMPOSITE;
    }
    for (size_t divisor = 5; divisor * divisor <= number; divisor += 6) {
        if (!(number % divisor) || (!(number % (divisor + 2)))) {
            return COMPOSITE;
        }
    }
    return PRIME;
}

/**
 * Generates a vector of primes using a Sieve of Eratosthenes
 * @tparam T Unsigned integer
 * @param ceiling Highest number to test for primality
 * @param primes Vector of computed primes
 */
template <typename T>
void sieve_of_eratosthenes(T ceiling, vector<T>& primes) {
    vector<Primality> primality(ceiling + 1, PRIME);
    primality[0] = primality[1] = NEITHER;
    for (T number = 2; number * number <= ceiling; number++) {
        if (primality[number] == PRIME) {
            for (T i = number * number; i <= ceiling; i += number) {
                primality[i] = COMPOSITE;
            }
        }
    }
    for (T number = 2; number <= ceiling; number++) {
        if (primality[number] == PRIME) {
            primes.push_back(number);
        }
    }
}

/**
 * Prints the prime at the given index in the series
 * @tparam T Unsigned integer
 * @param index Index of the prime to print
 */
template <typename T>
void find_nth_term(T index) {
    // Prime number theorem approximation of the Nth prime.
    T ceiling_estimate = index * log(index) + index * log(log(index));

    // Minimum sieve ceiling value (in case the approximation fails)
    T ceiling_min = 15;

    // Effective sieve ceiling
    T ceiling;

    vector<T> primes;
    while (true) {
        // (Re)calculate the effective sieve ceiling
        ceiling = max(ceiling_estimate, ceiling_min);

        // Generate primes
        sieve_of_eratosthenes(ceiling, primes);

        if (index <= primes.size()) {
            cout << "Prime #" << index << " = " << primes[index - 1] << endl;
            return;
        } else {
            // Increase the ceiling if the sieve failed to find the desired prime
            ceiling_min = ceiling * 1.25;
            primes.clear();
        }
    }
}

/**
 * Prints every prime below a given ceiling value
 * @tparam T Unsigned integer
 * @param ceiling Ceiling value
 */
template <typename T>
void list_terms(T ceiling) {
    vector<T> primes;
    sieve_of_eratosthenes(ceiling, primes);
    
    for (size_t i = 0; i < primes.size(); i++) {
        cout << "Prime #" << (i + 1) << " = " << primes[i] << endl;
    }
}

/**
 * Prints the result of a primality test for given candidate number
 * @tparam T Unsigned integer
 * @param candidate Number to test
 */
template <typename T>
void test_candidate(T candidate) {
    if (primality_test(candidate) == PRIME) {
        cout << candidate << " is prime" << endl;
    }
    else if (primality_test(candidate) == COMPOSITE) {
        cout << candidate << " is composite" << endl;
    }
    else {
        cout << candidate << " is neither prime nor composite" << endl;
    }
    exit(EXIT_SUCCESS);
}

#endif // PRIMALITY_H