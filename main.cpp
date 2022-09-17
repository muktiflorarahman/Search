#include <iostream>
#include "BinarySearchTree.h"
#include "HashTable.h"
#include "Primes.h"
#include "Enums.h"
#include "SearchAlgorithms.h"
#include "Results.h"
#include <vector>

int main()
{
	Primes primes( 100000000 );						// Creates a list of all primes between 2 and it's argument
	Results results_;								// The object to store our measurements in

	size_t amount = 200000;							// The starting amount of primes to search through (goes to 10*amount)
	size_t finalAmount = amount * 10;				// The final amount of primes to search through
	size_t searchRepeats = 50;						// The number of search iterations

	size_t numberOfBuckets = ( finalAmount );		// Used for the hashTable_

	std::vector<AlgorithmType> algorithms =
	{
		AlgorithmType::LINEAR,
		AlgorithmType::BINARY,
		AlgorithmType::BINARY_SEARCH_TREE,
		AlgorithmType::HASH_TABLE
	};

	// The oject that takes care of our sorting
	SearchAlgorithms searchAlgorithms( numberOfBuckets );

	// Create and fill an array with prime numbers
	size_t* primeNumbers = new size_t[ finalAmount ];
	primes.fill_array( primeNumbers, finalAmount );

	// Loop through all of the search algorithms
	// 0 = Linear, 1 = Binary, 2 = BST, 3 = Hash
	for ( auto algorithm : algorithms )
	{
		std::cout << "------------------------------------------------------------\n" << std::endl;
		// Loop through each search 10 times with the amount rising each time
		for ( size_t newAmount = amount; newAmount <= finalAmount; newAmount = newAmount + amount )
		{
			size_t oldAmount = newAmount - amount;

			// Search through it using the selected algorithm
			searchAlgorithms.search_and_time(
				primeNumbers, newAmount, oldAmount,
				results_, searchRepeats, algorithm );
		}

		if ( algorithm == AlgorithmType::HASH_TABLE )
		{
			searchAlgorithms.delete_hash_table();
		}


		// Print out our results_
		results_.print_results( algorithm );
		std::cout << "------------------------------------------------------------\n" << std::endl;
	}

	// Delete the array
	delete[] primeNumbers;

	return 0;
}

