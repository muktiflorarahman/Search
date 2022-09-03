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
    //instans av primes
    //Creates a list of all primes between 2 and it's argument
    Primes primes(50000000);
    //Primes primes(1000);

    //The starting amount of primes to search through (goes to 10*amount)
    size_t amount = 200000;
   // size_t amount = 200;

    // The number of search iterations
    size_t searchRepeats = 50;
   // size_t searchRepeats = 1;
    // Used for the hashTable_
    size_t numberOfBuckets = (amount);
    //The object to store our measurements in
    Results results;


    std::vector<AlgorithmType> algorithms =
    {
        AlgorithmType::LINEAR,
        //AlgorithmType::BINARY
        AlgorithmType::BINARY_SEARCH_TREE,
        AlgorithmType::HASH_TABLE
    };

    SearchAlgorithms searchAlgorithms(numberOfBuckets);
    searchAlgorithms.init();

    //går igenom algorithms vektorn
    for(AlgorithmType algorithm : algorithms)
    {
        //går igenom hur stor sökmängd man behöver söka, storleken på "höstack"
        for(size_t newAmount = amount; newAmount <= amount * 10; newAmount = newAmount + amount)
        {
            //std::cout << "The algorithm is: " << algorithm << std::endl;
            //std::cout << "The new amount is: " << newAmount << std::endl;

            size_t oldAmount  = newAmount - amount;

            //skapar en array som ska innehålla primtal
            //skapar på heapen för att värdet ändras
            size_t* primeNumbers = new size_t[newAmount];
            primes.fillArray(primeNumbers, newAmount);

            //söker igenom arrayen med den valda algoritmen
            searchAlgorithms.search_and_time(primeNumbers, newAmount, oldAmount, results, searchRepeats, algorithm);



            //tar bort primenumbers arrayen för att skapa en större array vid nästa körning
            delete[] primeNumbers;
        }
        results.print_results(algorithm);
    }


}

/*
size_t TreeKeys[16] = {50, 76, 21, 4, 64, 15, 52, 14, 100, 83, 2, 3, 70, 87, 80};
size_t TableNums[16] = {50, 76, 21, 4, 64, 15, 52, 14, 100, 83, 2, 3, 70, 87, 80};
*/

/*
HashTable hash(5);
hash.init_table();
*/

//hash.add_values(TableNums, 16, 0);

//hash.print();

    /*
    BinarySearchTree myTree;
    int input = 0;

    cout << "Printing the tree in order\nBefore adding numbers\n";

    myTree.display();

    for(int i = 0; i < 16; i++)
    {
        myTree.insert(TreeKeys[i]);
    }

    cout << "Printing the tree in order\nAfter adding numbers\n";

    myTree.display();

    cout << endl;


   // cout << "The smallet value in the tree is: " << myTree.FindSmallest() << endl;

    cout << "Enter a key value to delete. Enter -1 to stop the process\n";

    while(input != -1)
    {
        cout << "Delete Node: ";
        cin >> input;
        {
            if(input !=-1)
            {
                cout << endl;
                myTree.remove(input);
                myTree.display();
                cout << endl;

            }
        }
    }
    */
