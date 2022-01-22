//This is the a file for the member function definitions for a singly linked list 
#include "sll.hpp"
#include <iostream>
#include <string> 

using namespace std; 


LL::LL()
{
    head = NULL; // instantiate the class 
}

bool LL::isEmpty()
{
    if (head == NULL) // if head is still null, it is empty 
    {
        return true; 
    }
    return false; 
}

void LL::insertNode(int key)
{
    Node * newNode = NULL; 
    newNode = new Node(); //allocate memory on the heap 

    newNode -> key = key; 
    newNode -> next = NULL; 

    if (head == NULL) //if we are inserting at the head 
    {
        head = newNode; 
    }
    else // find the tail 
    {
        Node * temp = head; 
        while(temp -> next != NULL) // when this exits, the temp is now the tail 
        {
            temp = temp -> next; 
        }
        temp -> next = newNode; //tail -> next = newNode 
    }
}

Node * LL::searchList(int key)
{
    Node * temp = head; 
    while (temp != NULL) // while it has not been found and we havent reached the end of the LL 
    {
        if (temp -> key == key)
        {
            return temp; //exits when we have found it 
        }
        temp = temp -> next; 
    }
    return NULL; //unsuccesful 
}

void LL::deleteEntireNetwork()
{
    Node * temp = head; //start at the head 
    bool entered = false; 

    int i = 0; //keep track of how many elements we are deleting 
    while (head != NULL) // while not empty 
    {
        entered = true; 
        temp = head -> next; //delete head and set head to the node after the first head. repeat until empty. 
        delete head; 
        head = temp; 
        i++; 
    }
    delete temp; 
    if (isEmpty() && entered == true) // if there were elements to begin with and it is not empty any longer 
    {
        cout << "deleted " << i << " network elements." << endl; //show how many elements were deleted 
    }
} 

void LL::printPath()
{
    Node * current = head; //start at head 
    int i = 0; 
    while (current != NULL)
    {
        cout << current -> key << " (" << i+1 << ")" << " -> "; //show the current's key 
        current = current -> next; //increment to the next element in the linked list 
        i++;
    }
    cout << "NULL" << endl; //the end is NULL 
}