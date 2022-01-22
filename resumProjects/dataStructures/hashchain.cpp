//this is the file for hash chain member function definitions 
#include "hashchain.hpp"
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath> 

using namespace std; 

node * HashTable::createNode(int key, node* next) //private: returns the location of a new node 
{
    node * newNode = new node(); 
    newNode -> key = key; //set key to the input key 
    newNode -> next = next; //sets next to the input next; this will always be null 
    return newNode; 
}

HashTable::HashTable(int bsize)  // Constructor
{
    tableSize = bsize; 
    table = new node * [bsize]; //allocate enough memory on the heap 
    for (int i = 0; i < tableSize; i++)
    {
        table[i] = NULL; // set all to null 
    }
}

bool HashTable::insertItem(int key)// inserts a key into hash table: why is this bool? 
{
    if (table[hashFunction(key)] == NULL) // if current bucket is empty 
    {
        table[hashFunction(key)] = createNode(key, NULL); //set it to the pointer to a new node with the associated key 
        return true;
    }
    else //this is when we have a collision
    {
        numOfcolision++; // this happens outside of the while loop because the book defines a collision as: h(k1) = h(k2), k1 != k2 
        node * current = table[hashFunction(key)]; //set current to the head of the bucket 
        while (current -> next != NULL) // while we havent found the tail of the LL of the current bucket, increment 
        {
            current = current -> next; 
        }
        current -> next = createNode(key, NULL); // the next of the tail of the bucket is the new node 
    }
    return true; 
}

unsigned int HashTable::hashFunction(int key)// hash function to map values to key
{
    return (key % tableSize); //this is the hash function 
}

void HashTable::printTable()
{
    node * current = NULL; //set current to null 
    for (int i = 0; i < tableSize; i++) // for each bucket in the table 
    {
        if(table[i] != NULL) // if the bucket is not empty 
        {
            cout << "index " << i << ": "; //show the index 
            cout << table[i] -> key;
            current = table[i]; //set current to the head of the LL of the bucket 
            while(current -> next != NULL) // while we have not gotten to the end of the LL of the bucket: if there is only one element, this is not entered 
            {
                current = current -> next; //go to the next in the chain 
                cout << "->" << current -> key; // show the current key 
            }
            cout << endl;
        }
        
    }
}

int HashTable::getNumOfCollision()//returns the current number of collisions 
{
    return numOfcolision; 
}

node * HashTable::searchItem(int key) // will search for an item 
{
    if (table[hashFunction(key)] -> key == key) // if the bucket only has one element, merely return that pointer 
    {
        return table[hashFunction(key)]; 
    }
    else //bucket has more than one element: there is a collision
    {
        node * current = table[hashFunction(key)]; //set current to the head of the LL of the bucket 
        numOfcolision++; // this happens outside of the while loop because the book defines a collision as: h(k1) = h(k2), k1 != k2
        while (current -> next != NULL && current -> key != key) //this will only enter if we havent found the key in the head of the bucket 
        {
            current = current -> next; //increment until we found the key in the LL of the bucket 
        }
        if (current -> key == key)
        {
            return current; //this will return the pointer to the key that was found 
        }
    }
    return NULL; // if done correctly, should never return NULL 
}
