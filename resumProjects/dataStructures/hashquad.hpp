//this is the header file for a hash quadratic implementation 
#ifndef HASH_HPP
#define HASH_HPP

#include <string>

using namespace std;

struct node
{
    int key; // only key needed 
};

class HashTable
{
    int tableSize;  // No. of indices
    node * * table; // Pointer to an array containing node pointers
    int numOfcolision = 0;
    node * createNode(int key);
public:
    HashTable(int bsize);  // Constructor
    bool insertItem(int key);// inserts a key into hash table
    unsigned int hashFunction(int key);// hash function to map values to key
    void printTable(); //prints the table 
    int getNumOfCollision();//returns the number of collisions 
    node * searchItem(int key);//returns the location of a searched for item 
    ~HashTable(); //destructor
};

#endif