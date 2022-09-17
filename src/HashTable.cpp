#include "HashTable.h"
#include <iostream>

HashTable::Node::Node()
{

}

HashTable::Node::Node(size_t value)
    : m_value(value)
{

}

HashTable::HashTable()
{
    //ctor
}

HashTable::HashTable(size_t size)
    : m_tableSize(size)
{
    //ctor
}

HashTable::~HashTable()
{
    //dtor
}

void HashTable::rehash_table( size_t oldSize )
{
	m_hashTable.resize( m_tableSize );

	for ( size_t index = oldSize; index < m_tableSize; index++ )
	{
		Node* n = new Node();
		m_hashTable[ index ] = n;
	}
}

void HashTable::delete_table()
{
	for ( size_t i = 0; i < m_hashTable.size(); ++i )
	{
		Node* entry = m_hashTable[ i ];

		while ( entry != nullptr )
		{
			Node* prev = entry;
			entry = entry->m_next;
			delete prev;
		}
	}
	
	m_hashTable.clear();
}
void HashTable::delete_bucket(size_t index)
{
    Node* temp = m_hashTable[index];
    Node* next = m_hashTable[index];

    while(temp->m_next != nullptr)
    {
        next = temp->m_next;
        delete temp;
        temp = next;
    }

    delete temp;
    temp = nullptr;
    next = nullptr;
}

size_t HashTable::get_table_size()
{
	return m_tableSize;
}

void HashTable::set_table_size( size_t size_ )
{
	m_tableSize = size_;
}

size_t HashTable::create_hash(size_t number)
{
    size_t index = number % m_tableSize;

    return index;
}
//oldSize är antalet primtal i körningen innan
void HashTable::add_values(size_t primesArray[], size_t arraySize, size_t oldSize)
{
    for(size_t i = oldSize; i < arraySize; i++)
    {
        add_value(primesArray[i]);
    }
}

void HashTable::add_value(size_t value)
{
    size_t index = create_hash(value);

    if(m_hashTable[index]->m_value == 0 && m_hashTable[index]->m_next == nullptr)
    {
        m_hashTable[index]->m_value = value;
    }
    else
    {
        Node* temp = m_hashTable[index];
        Node* n = new Node(value);

        while(temp->m_next != nullptr)
        {
            temp = temp->m_next;
        }
        temp->m_next = n;
    }
}
size_t HashTable::bucket_size(size_t index)
{
    size_t count = 0;

	// Case 1 - empty Node
	if ( m_hashTable[index]->m_value == 0 )
	{
		return count;
	}

	// Case 2 - one value only
	if ( m_hashTable[ index ]->m_value != 0 && m_hashTable[index]->m_next == nullptr )
	{
		return ++count;
	}

	// Case 3 - many values
	if ( m_hashTable[ index ]->m_value != 0 && m_hashTable[ index ]->m_next != nullptr )
	{
		count++;
		Node* temp = m_hashTable[ index ];

		while ( temp->m_next != nullptr )
		{
			count++;
			temp = temp->m_next;
		}
	}
	return count;

}
void HashTable::print()
{
    size_t number;
	for ( size_t el = 0; el < m_tableSize; el++ )
	{
		number = bucket_size( el );

		std::cout << "----------------------" << std::endl;
		std::cout << "Bucket = " << el << std::endl;
		std::cout << m_hashTable.at( el )->m_value << std::endl;
		std::cout << "# of Nodes = " << number << std::endl;
		std::cout << "----------------------" << std::endl;
	}
}

void HashTable::print_index(size_t index)
{
    Node* temp = m_hashTable[index];

	if ( temp->m_next == nullptr )
	{
		std::cout << "Bucket " << index << " is empty.\n";
	}
else
	{
		std::cout << "Bucket " << index << " contains following:\n";

		while ( temp != nullptr )
		{
			std::cout << "----------------------" << std::endl;
			std::cout << temp->m_value << std::endl;
			std::cout << "----------------------" << std::endl;

			temp = temp->m_next;
		}
	}
}
bool HashTable::retrieve_value(size_t value)
{
    size_t index = create_hash( value );
	bool foundValue = false;

	Node* temp = m_hashTable[ index ];

	while ( temp != nullptr )
	{
		if ( temp->m_value == value )
		{
			foundValue = true;
			break;
		}

		temp = temp->m_next;
	}

	return foundValue;
}
void HashTable::remove_value(size_t value)
{
    size_t index = create_hash( value );
	Node* delPtr;
	Node* p1;
	Node* p2;

	// Case 0 - bucket is empty
	if ( m_hashTable[ index ]->m_value == 0 && m_hashTable[ index ]->m_next == nullptr )
	{
		std::cout << value << " was not found." << std::endl;
	}
// Case 1 - only 1 Node contained in bucket and has matching name
	else if ( m_hashTable[ index ]->m_value == value && m_hashTable[ index ]->m_next == nullptr )
	{
		m_hashTable[ index ]->m_next = nullptr;

		std::cout << value << " was removed from the hash table." << std::endl;
	}
// Case 2 - match is located in the first Node in the bucket, but
	// 			there are more Nodes in the bucket
	else if ( m_hashTable[ index ]->m_value == value )
	{
		delPtr = m_hashTable[ index ];
		m_hashTable[ index ] = m_hashTable[ index ]->m_next;
		delete delPtr;

		std::cout << value << " was removed from the hash table." << std::endl;
	}
	// Case 3 - bucket contains Nodes but first Node is not a match
	else
	{
		p1 = m_hashTable[ index ]->m_next;
		p2 = m_hashTable[ index ];

		while ( p1 != nullptr && p1->m_value != value )
		{
			p2 = p1;
			p1 = p1->m_next;
		}
// Case 3.a - no match
		if ( p1 == nullptr )
		{
			std::cout << value << " was not found in the hash table." << std::endl;
		}

		// Case 3.b - match is found
		else
		{
			delPtr = p1;
			p1 = p1->m_next;
			p2->m_next = p1;

			delete delPtr;
			std::cout << value << " was removed from the hash table." << std::endl;
		}
	}
}
