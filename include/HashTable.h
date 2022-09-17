#ifndef m_hashTableH
#define m_hashTableH
#include <cstddef>
#include <vector>



class HashTable
{
public:
    HashTable();
    HashTable(size_t);
    ~HashTable();

    void rehash_table( size_t );
    void delete_table();
    void delete_bucket(size_t);

    size_t get_table_size();
    void set_table_size( size_t );

    size_t create_hash( size_t );

    void add_values(size_t[], size_t, size_t);
    void add_value(size_t);
    size_t bucket_size(size_t);
    void print();

    void print_index(size_t);
    bool retrieve_value(size_t);
    void remove_value(size_t);


private:

    struct Node
    {
        Node();
        Node(size_t);

        size_t m_value{0};
        Node* m_next{nullptr};
    };

    size_t m_tableSize{0};
    std::vector<Node*> m_hashTable;
};

#endif // m_hashTableH
