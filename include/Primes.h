#ifndef PRIMES_H
#define PRIMES_H
#include <cstddef>


class Primes
{
public:
    Primes();
    Primes(size_t);

    void fill_array(size_t[], size_t);
    void Eratosthenes();


private:
    size_t m_arraySize;
    bool* m_boolArray;
};

#endif // PRIMES_H
