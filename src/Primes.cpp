#include "Primes.h"
#include <memory>
#include <array>

Primes::Primes()
{
    m_arraySize = 10000;
    Eratosthenes();
}


Primes::Primes(size_t arraySize)
    : m_arraySize(arraySize)
{
    Eratosthenes();
}

void Primes::fillArray(size_t arrayToBeFilled[], size_t numberOfPrimes)
{
    size_t pos = 0;

	for ( size_t i = 0; i < m_arraySize; i++ )
	{
		if ( m_boolArray[ i ] )
		{
			arrayToBeFilled[ pos ] = i;
			pos++;

			if ( pos >= numberOfPrimes )
			{
				break;
			}
		}
	}
}
void Primes::Eratosthenes()
{
    m_boolArray = new bool[m_arraySize] {false };

	for( size_t i = 2; i < m_arraySize; i++ )
	{
		m_boolArray[ i ] = true;
	}

	// Based on example from: https://www.geeksforgeeks.org/c-program-for-sieve-of-eratosthenes/
	for ( size_t prime = 2; prime * prime < m_arraySize; prime++ )
	{
		// If boolArray_[prime] is not changed, then it is a prime
		if ( m_boolArray[ prime ] )
		{
			// Update all multiples of prime
            for ( size_t i = prime * 2; i < m_arraySize; i += prime )
            {
                m_boolArray[ i ] = false;
            }
		}
	}
	// End of example code ----------------------------------------------------------------------

}
