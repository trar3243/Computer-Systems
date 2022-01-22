//this is the driver file for a bst 
#include "bst.hpp"
#include <string>
#include <iostream> 
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cmath> 
#include <chrono>

void exportData(float insertArr[100], float searchArr[100], string fileName) // the purpose of this function is to take the arrays that have the runtimes and export them to a csv file to create the graphs 
{
    ofstream out_file; 
    out_file.open(fileName); 
    if(out_file.fail())
    {
        cout << "failed to open the output file" << endl;
        return;
    }
    out_file << "Iteration" << ',' << "Insert" << ',' << "Search" << ',' << "Unit: ns" << endl;
    for (int i = 0; i < 100; i++)
    {
        out_file << i << ',' << insertArr[i] << ',' << searchArr[i] << "\n"; 
    }
}

int processFile(string fileName, int intArr[], int size) // the purpose of this function is to take a csv file and store the values in it into the intArray 
{
    ifstream in_file; 
    in_file.open(fileName); 
    if (in_file.fail()) // this return value will automatically terminate the entire program 
    {
        cout << "Input file name not in directory." << endl;
        return -1;
    }
    string value; 
    int i = 0; 
    while (getline(in_file, value, ',') && i < size) // while retrieving values and less than 10001 values have been added 
    {
        intArr[i] = stoi(value); //store the values in the int arr 
        i++;
    }
    return 0;
}

void searchFunction(float search[100], BST & tree, int size, int intArr[], int range, int indx) // indx is being passed as j, range as i; i is the current number of elements in the BST, j is that number /100 
{
    int randArr[100];
    for (int i = 0; i < 100; i++)//populate the rand index array 
    {
        randArr[i] = rand() % (range + 1);// range = 0,99 the first time, 199 the second time, etc: the range variable being passed in is equal to the element of the int array that was just inserted in the insert function
    }
    auto start = chrono::steady_clock::now();
    for (int i = 0; i < 100; i++) // search for 100 values within the range 
    {
        tree.searchKey(intArr[randArr[i]]); 
    }
    auto end = chrono::steady_clock::now(); // end clock after 100 searches 
    search[indx] = chrono::duration_cast<chrono::nanoseconds>(end - start).count() / (100 * 1.0);
}

void insertFunction(float insert[100], float search[100], BST & tree, int size, int intArr[])
{
    auto insertStart = chrono::steady_clock::now();
    for (int i = 0, j = 0; i < size; i++)
    {
        tree.addNode(intArr[i]); 
        if ((i + 1) % 100 == 0 && i != 1)// we have reached the one hundreth node 
        {
            auto insertEnd = chrono::steady_clock::now(); // end before inserting 
            insert[j] = chrono::duration_cast<chrono::nanoseconds>(insertEnd - insertStart).count() / (100 * 1.0); // divide by 100 because we are looking at the time of addition of 100 inserts 
            searchFunction(search, tree, size, intArr, i, j); // now we search through all present elements of the LL 
            j++;
            insertStart = chrono::steady_clock::now();
        }
    }
    
}

int main()
{
    string dataSetA = "A.csv";//Rather than command line, we can put file names here
    string dataSetB = "B.csv";
    int size = 10000; //number of elements we want to store 
    int intArr[size]; //to store the values from the csv 
    float insert[100]; // create the storage arrays for the runtimes 
    float search[100]; 

    if (processFile(dataSetB, intArr, size) == -1) // this returns an int: -1 if not succesful 
    {
        return 0;
    } 
    
    BST tree = BST(); //instantiate 
    insertFunction(insert, search, tree, size, intArr); // this will call the search after every 100 inserts 
    exportData(insert, search, "BSTGraphB.csv"); //this exports the data to a csv 

    for (int i = 0; i < 100; i++)
    {
        search[i] = 0;
        insert[i] = 0; 
    }
    tree.~BST(); // delete all present nodes for a fresh start 
    if (processFile(dataSetA, intArr, size) == -1)
    {
        return 0;
    } 
    insertFunction(insert, search, tree, size, intArr); // calls search every 100 inserts 

    exportData(insert, search, "BSTGraphA.csv");
    //tree.printTree(); //this will print all elements of the tree in order 

    return 0; 
}