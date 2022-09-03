#include "SearchAlgorithms.h"
#include <random>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <chrono>

SearchAlgorithms::SearchAlgorithms()
{
    //ctor
}

SearchAlgorithms::SearchAlgorithms(size_t numberOfBuckets)
{
    m_hashTableSize = numberOfBuckets;

    m_hashtable = new HashTable(m_hashTableSize);
    m_binarySearchTree = new BinarySearchTree();
}

SearchAlgorithms::~SearchAlgorithms()
{
    delete m_binarySearchTree;
    delete m_hashtable;
}

void SearchAlgorithms::init()
{
    m_hashtable->init_table();
}

std::chrono::duration<double, std::milli> SearchAlgorithms::search_numbers(size_t primesArray[], size_t arraySize, size_t searchValue, AlgorithmType algorithm)
{
    int pos = -1;
    size_t first = 0;
    size_t last = arraySize - 1;

    auto start = std::chrono::high_resolution_clock::now();

    switch(algorithm)
    {
        //linear search
        case AlgorithmType::LINEAR:
        {
            pos = linear_search(primesArray, arraySize, searchValue);
            break;
        }
        //binary search
        case AlgorithmType::BINARY:
        {
            pos = binary_search(primesArray, first, last, searchValue);
            break;
        }

        //binary search tree
        case AlgorithmType::BINARY_SEARCH_TREE:
        {
            pos = binary_search_tree_find(searchValue);
            break;
        }

        //hash table
        case AlgorithmType::HASH_TABLE:
        {
            pos = hash_table_lookup(searchValue);
            break;

        }

        default:
        {
            break;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    return end - start;
}


void SearchAlgorithms::search_and_time(size_t primesArray[], size_t arraySize, size_t oldSize, Results& results, size_t searchRepeats, AlgorithmType algorithm)
{
    size_t searchValue = 0;
    std::random_device randomDevice;
    std::mt19937 rng(randomDevice());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, arraySize-1);

    //vi behöver blanda arrayen med primtal innan de sorteras in i det binära sökträd
    //sorterar arrayen innan timern startas
    if(algorithm == AlgorithmType::BINARY_SEARCH_TREE)
    {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(primesArray, primesArray + arraySize, g);
        add_to_binary_search_tree(primesArray, arraySize);
    }

    if(algorithm == AlgorithmType::HASH_TABLE)
    {
        clock_t timeRequired = clock();
        std::cout << "size of primes array: " << arraySize
                << " Adding to hashtable" << std::endl;
        add_to_hash_table(primesArray, arraySize, oldSize);

        timeRequired = clock() - timeRequired;

        std::cout << "All values have been added to the hash table. It took "
                    << (float)timeRequired / CLOCKS_PER_SEC << std::endl;
    }

  //skapar en variabel för att kunna ta tidtagning
    std::chrono::duration<double, std::milli> timeTaken(0);
    for(size_t index = 0; index < searchRepeats; index++)
    {
        //slumpa fram ett searchValue
        searchValue = primesArray[dist(rng)];
       // std::cout << "The search value is: " << searchValue << std::endl;
        timeTaken = search_numbers(primesArray, arraySize, searchValue, algorithm);
        results.add_measurements(arraySize, timeTaken.count());
    }

    if(algorithm == AlgorithmType::BINARY_SEARCH_TREE)
    {
        delete_binary_search_tree();
    }

}

int SearchAlgorithms::linear_search(size_t arrayToBeSearched[], size_t arraySize, size_t searchValue)
{
    for(size_t index = 0; index < arraySize; index++)
    {
        if(arrayToBeSearched[index] == searchValue)
        {
            return index;
        }
    }
    return -1;
}


int SearchAlgorithms::binary_search(size_t arrayToBeSearched[], size_t first, size_t last, size_t searchValue)
{
    std::cout << "===> First value: " << first << " last value: " << last << " search value: " << searchValue
                << std::endl;
    if (first <= last)
    {
        //deciding middle point
        int mid = (first + last)/2;
        if (arrayToBeSearched[mid] == searchValue)
        {
            //value is found
            return mid;
        }

        if (searchValue  > arrayToBeSearched[mid])
        {
            //anropar samma funktion med den undre halvan av arrayen
            return binary_search(arrayToBeSearched, mid+1, last, searchValue);

        }

        if(searchValue < arrayToBeSearched[mid])
        {
            //anropar samma funktion med den övre halvan av arrayen
            return binary_search(arrayToBeSearched, first, mid-1, searchValue);
        }
    }
    return -1;
}

void SearchAlgorithms::add_to_binary_search_tree(size_t binaryArray[], size_t arraySize)
{
    for(size_t index = 0; index < arraySize; index++)
    {
        m_binarySearchTree->insert(binaryArray[index]);
    }
}

bool SearchAlgorithms::binary_search_tree_find(size_t searchValue)
{
    return m_binarySearchTree->search(searchValue);
}

void SearchAlgorithms::delete_binary_search_tree()
{
    m_binarySearchTree->delete_tree();
}
//
void SearchAlgorithms::add_to_hash_table(size_t primesArray[], size_t arraySize, size_t oldSize)
{
    m_hashtable->add_values(primesArray, arraySize, oldSize);

}


bool SearchAlgorithms::hash_table_lookup(size_t searchValue)
{
   return m_hashtable->retrieve_value(searchValue);
}

void SearchAlgorithms::delete_hash_table()
{
    m_hashtable->delete_table();
}










