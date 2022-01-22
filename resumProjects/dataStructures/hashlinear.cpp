//this is the member function definitions for a hash linear implementation 
#include "hashlinear.hpp"
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath> 

using namespace std; 

node * HashTable::createNode(int key) //private
{
    node * newNode = new node(); 
    newNode -> key = key; 
    return newNode; 
}

HashTable::HashTable(int bsize)  // Constructor
{
    tableSize = bsize; 
    table = new node * [bsize]; //allocate space on the heap 
    for (int i = 0; i < tableSize; i++)
    {
        table[i] = NULL; // set all indices to null 
    }
}

bool HashTable::insertItem(int key)// inserts a key into hash table
{
    if (table[hashFunction(key)] == NULL) // if there is no collision 
    {
        table[hashFunction(key)] = createNode(key); //set it to the location of a new node
        return true;
    }
    else //collision 
    {
        numOfcolision++; // this happens outside of the while loop because the book defines a collision as: h(k1) = h(k2), k1 != k2
        int indx = hashFunction(key); //current index is set to the index from the hash function 
        bool found = false; 
        int count = 0; // this will keep track of how many times we are probing 
        while (found == false && count <= tableSize) // while we have not found an empty index and we have not checked all indices 
        {
            count++; //keeps track of the number of probes 
            indx = (hashFunction(key) + count) % tableSize; //index = (original hash + iteration) %  tableSize
            if (table[indx] == NULL) //if we can insert because the current index is empty 
            {
                found = true; 
                table[indx] = createNode(key); //set that array location to the address of the new node 
            }
        }
        if (found == false) // this would mean that the reason we exited the while loop is because we ran out of places to look for a NULL
        {
            cout << "the number of elements exceeded the table size. Item " << key << " was not added." << endl; 
             return false;
        }
    }
    return true; 
}

unsigned int HashTable::hashFunction(int key)// hash function to map values to key
{
    return (key % tableSize); //this is the hash function 
}

void HashTable::printTable() //prints the table 
{
    for (int i = 0; i < tableSize; i++) //for each array index 
    {
        if(table[i] != NULL) // if the index is not empty 
        {
            cout << "table index at " << i << " is " << table[i] -> key << endl; //display the value stored there 
        }
        
    }
}

int HashTable::getNumOfCollision() //returns the current number of collisions 
{
    return numOfcolision; 
}

node * HashTable::searchItem(int key)//searches for a key 
{
    if (table[hashFunction(key)] -> key == key) //if we do not need to probe 
    {
        return table[hashFunction(key)]; 
    }
    else 
    {
        numOfcolision++;// this happens outside of the while loop because the book defines a collision as: h(k1) = h(k2), k1 != k2
        int indx;
        bool found = false; 
        int count = 0; //keeps track of how many times we are searching through the table
        while (found == false && count <= tableSize) // while we have not found the key and havent searched all elements
        {
            count++; //keeps track of the number of probes 
            indx = (hashFunction(key) + count) % tableSize; //index = (original hash + iteration) %  tableSize to avoid accessing anything outside the bounds 
            if (table[indx] -> key == key) //if we can insert because the current index is empty 
            {
                found = true; 
                return table[indx]; //return the location of the node 
            }
        }
        if (found == false) // the reason for exiting the while loop is due to not finding the value 
        {
            cout << "key value " << key << " is not present in the hash table." << endl; 
        }
    }
    return NULL;
}

HashTable::~HashTable()
{
    delete[] table; 
    cout << "table was deleted" << endl;
}