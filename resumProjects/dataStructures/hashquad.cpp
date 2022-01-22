//this is the member defintions of the hash quadratic class
#include "hashquad.hpp"
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath> 

using namespace std; 

node * HashTable::createNode(int key) //private
{
    node * newNode = new node(); 
    newNode -> key = key; 
    return newNode; //return the location of the new node 
}

HashTable::HashTable(int bsize)  // Constructor
{
    tableSize = bsize; 
    table = new node * [bsize]; //allocate memory on the heap 
    for (int i = 0; i < tableSize; i++)
    {
        table[i] = NULL;//set all indices to null 
    }
}

bool HashTable::insertItem(int key)// inserts a key into hash table: why is this bool? 
{
    if (table[hashFunction(key)] == NULL) //if we can simply insert into the array at the index from the function 
    {
        table[hashFunction(key)] = createNode(key);
        return true;
    }
    else //we have a collision 
    {
        numOfcolision++;// this happens outside of the while loop because the book defines a collision as: h(k1) = h(k2), k1 != k2
        int hashVal = hashFunction(key); 
        int indx = 0; 
        bool found = false; 
        int count = 0; // this will keep track of how many times we are probing 
        while (found == false && count <= tableSize)
        {
            count++;
            indx = hashVal + pow(count, 2); // index = h(x) + i^2 
            if (indx >= tableSize) // we need to do the remainder of the index and table size 
            {
                indx = indx % tableSize; //therefore, i.e. with M = 10 and indx = 12, the index is now 2 
            }
            if (table[indx] == NULL)//if the current index is empty, we can insert 
            {
                found = true; 
                table[indx] = createNode(key);//set the index to contain the location of the new node 
            }
        }
        if (found == false) // this would mean that the reason we exited the while loop is because we probed too many times
        {
             return false;
        }
    }
    return true; 
}

unsigned int HashTable::hashFunction(int key)// hash function to map values to key
{
    return (key % tableSize); //this is the hash function 
}

void HashTable::printTable() //displays all elements 
{
    for (int i = 0; i < tableSize; i++)
    {
        if(table[i] != NULL) //if index is not empty 
        {
            cout << "table index at " << i << " is " << table[i] -> key << endl; //display the associated key 
        }
        
    }
}

int HashTable::getNumOfCollision()//returns the number of collisions 
{
    return numOfcolision; 
}

node * HashTable::searchItem(int key) //searches for a key 
{
    if (table[hashFunction(key)] -> key == key) //no probes required 
    {
        return table[hashFunction(key)]; 
    }
    else //there has been a collision 
    {
        numOfcolision++;// this happens outside of the while loop because the book defines a collision as: h(k1) = h(k2), k1 != k2
        int hashVal = hashFunction(key); 
        int indx = 0; 
        bool found = false; 
        int count = 0; // this will keep track of how many times we are probing 
        while (found == false && count <= tableSize)
        {
            count++;
            indx = hashVal + pow(count, 2); // index = h(x) + i^2 
            if (indx >= tableSize) // we need to do the remainder of the index and table size to avoid accessing anything out of the array 
            {
                indx = indx % tableSize; //therefore, i.e. with M = 10 and indx = 12, the index is now 2 
            }
            if (table[indx] -> key == key) //when we find it, this will enter 
            {
                found = true; 
                return table[indx]; //return the pointer to the element 
            }
        }
        if (found == false) // this would mean that the reason we exited the while loop is because we probed more times than the number of elements in the table 
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