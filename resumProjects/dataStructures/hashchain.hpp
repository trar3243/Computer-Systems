//this is the header file for a hash chain implementation 
#ifndef HASH_HPP
#define HASH_HPP

#include <string>


using namespace std;

struct node
{
    int key;
    struct node* next; // this will be used in hash chaining 
};

class HashTable
{
    int tableSize;  // No. of buckets (linked lists)
    node * * table; // Pointer to an array containing buckets
    int numOfcolision = 0;
    node * createNode(int key, node * next);
public:
    HashTable(int bsize);  // Constructor
    bool insertItem(int key);// inserts a key into hash table
    unsigned int hashFunction(int key);// hash function to map values to key
    void printTable(); // will print the table; this prints the buckets' associated chains 
    int getNumOfCollision(); // returns the number of collisions at any time 
    node * searchItem(int key); // search function 
};

#endif
