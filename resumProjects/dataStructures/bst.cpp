//This file is for member function definitions for a BST
#include "bst.hpp"
#include <cmath>
#include <iomanip>
#include <iostream> 

using namespace std; 

Node* BST::addNodeHelper(Node* currNode, int data)
{
    if(currNode == NULL) // this is the base case 
    {
        return createNode(data);
    }
    else if(currNode->key < data)
    {
        currNode -> right = addNodeHelper(currNode -> right, data);
    }
    else if(currNode -> key >= data) // I put the equals in case of repeats, it will just go to the left  
    {
        currNode->left = addNodeHelper(currNode -> left, data);
    }
    return currNode;
}

void BST::addNode(int data) // function to insert a node in the tree.
{
    root = addNodeHelper(root, data);
}

Node* BST::createNode(int data)
{
    Node * newNode = new Node(); //allocate onto the heap 
    newNode -> left = NULL; //set all to null
    newNode -> right = NULL; 
    newNode -> key = data; //set key to data 
    return newNode; 
}

void BST::destroyNode(Node * currNode, int & destroyCount)
{
    
    if (currNode != NULL)
    {
        destroyNode(currNode->left, destroyCount); //recurse left and right 
        destroyNode(currNode->right, destroyCount);
        delete currNode;//delete the node 
        destroyCount++;
        currNode = NULL; // avoid dangling pointer 
    }
}

Node* BST::getRoot()   // Returns the root of the tree;
{
    return root; 
}            

Node* BST::searchKeyHelper(Node * currNode, int data)
{
    if (currNode == NULL) // this is an unsuccesful search 
    {
        return NULL;
    }

    if (currNode->key == data) //this is a succesful search 
    {
        return currNode;
    }

    if (currNode->key > data) // if the current key is greater than the key we want, then we recurse left 
    {
        return searchKeyHelper(currNode->left, data);
    }
    else if (currNode -> key < data) // if the current key is greater than the key we want, then we recurse right 
    {
        return searchKeyHelper (currNode->right, data);
    }
    return NULL; // this should never be reached 
}

bool BST::searchKey(int data) // function to search a data in the tree
{
    Node * temp = searchKeyHelper(root, data);
    if (temp != NULL) //if the return was not null of the helper, then the search was succeful 
    {
        return true;
    }
    //if the return of the helper is NULL, then it was not succesful 
    cout << "Key not present in the tree" << endl;
    return false;
}

void BST::printTreeHelper(Node * currNode) // this is an in order traversal: recurse left i.e. minimum values first, then current, then recurse right, i.e. max values last 
{
    if(currNode)
    {
        printTreeHelper(currNode -> left); 
        cout << " "<< currNode -> key;
        printTreeHelper( currNode -> right);
    }
}

void BST::printTree() //function to print the tree
{
    printTreeHelper(root); // use the helper 
    cout << endl; 
}

BST::BST()// default constructor
{
    root = NULL; 
}

BST::~BST()     //destructor 
{
    int destroyCount = 0;  
    destroyNode(root, destroyCount); // destroying the root destroys all 
    cout << destroyCount << " nodes have been destroyed." << endl;
    root = NULL; // this allows us to reuse the same tree; before, the root was deleted amd the memory space was assigned NULL; now, root is directly assigned NULL 
}      