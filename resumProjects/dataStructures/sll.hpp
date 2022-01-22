//this is the header file for a singly linked list 
#include <iostream>
#include <string> 

using namespace std; 

struct Node //this is the given struct 
{
    int key; 
    Node * next; 
};

class LL
{
    private: 
        Node * head; // a head pointer 
    public:
        LL(); // default constructor 
        bool isEmpty(); //returns true if empty, false otherwise 
        void insertNode(int key); // will insert at the tail 
        Node * searchList(int key); //will return a pointer to the node with that key 
        void deleteEntireNetwork(); //will delete the heap memory 
        void printPath(); //will print the path of the LL 
};
