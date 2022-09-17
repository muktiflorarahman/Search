#ifndef SEARCHALGORITHMS_H
#define SEARCHALGORITHMS_H
#include "HashTable.h"
#include "BinarySearchTree.h"
#include "Results.h"
#include<chrono>


class SearchAlgorithms
{
public:

    SearchAlgorithms();
    SearchAlgorithms(size_t numberOfBuckets);
    ~SearchAlgorithms();

    void search_and_time( size_t[], size_t, size_t, Results&, size_t, AlgorithmType);
    std::chrono::duration<double, std::milli> search_numbers(size_t[], size_t, size_t, AlgorithmType);

    int linear_search(size_t[], size_t, size_t);
    int binary_search(size_t[], size_t, size_t, size_t);

    void add_to_binary_search_tree(size_t[], size_t );
    bool binary_search_tree_find( size_t );
    void delete_binary_search_tree();

    void add_to_hash_table(size_t[], size_t, size_t );
    void rehash( size_t oldSize );
    bool hash_table_lookup( size_t );

    void set_hash_table_size( size_t );
    void delete_hash_table();


private:
    size_t m_hashTableSize {0};

    HashTable* m_hashtable {nullptr};
    BinarySearchTree* m_binarySearchTree {nullptr};

};

#endif // SEARCHALGORITHMS_H
