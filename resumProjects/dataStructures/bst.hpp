//This is the header file for a BST class 
#ifndef BST_HPP
#define BST_HPP

using namespace std;

struct Node
{
    int key; 
    Node * left; 
    Node * right; 
};

class BST
{
    private:
        Node* root; // pointer to the root of the tree 
        Node* createNode(int data); //returns the location of a new node 
        Node* addNodeHelper(Node*, int); //recursively helps add a node 
        void printTreeHelper(Node*); //resursive helper for printing the tree 
        Node* searchKeyHelper(Node*, int); //recursive helper for searching the tree 
        void destroyNode(Node *root, int & destroyCount); // i added destroyCount to see how many elements are being destroyed. 
    public: 
        Node* getRoot();                // Returns the root of the tree;
        void addNode(int);              // function to insert a node in the tree.
        bool searchKey(int);            // function to search a data in the tree
        void printTree();               //function to print the tree
        BST();                          // default constructor
        ~BST();                         // destructor
};
#endif