//this is the driver for a singly linked list 
#include "sll.hpp" // include this header file 
#include <string>
#include <iostream> 
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cmath> 
#include <chrono>

using namespace std; 

void exportData(float insertArr[100], float searchArr[100], string fileName) // the purpose of this function is to take the arrays that have the runtimes and export them to a csv file to create the graphs 
{
    ofstream out_file; 
    out_file.open(fileName); 
    if(out_file.fail()) // if there was a failure in opening the output file 
    {
        cout << "failed to open the output file "<< fileName << endl;
        return; 
    }
    out_file << "Iteration" << ',' << "Insert" << ',' << "Search" << ',' << "Unit: µs" << endl; // titles 
    for (int i = 0; i < 100; i++)
    {
        out_file << i << ',' << insertArr[i] << ',' << searchArr[i] << "\n"; //each line is for one iteration. 3 columns for iteration, insert, and search times 
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

void searchFunction(float search[100], LL linkedList, int size, int intArr[], int range, int indx) // the purpose of this function is to search for int indices within the array within a range: first is 0,99, then 0,199... 0, 9999
{
    int randArr[100];
    for (int i = 0; i < 100; i++)//populate the rand index array 
    {
        randArr[i] = rand() % (range + 1);// range = 0,99 the first time, 199 the second time, etc: the range variable being passed in is equal to the element of the int array that was just inserted in the insert function
    }
    auto start = chrono::steady_clock::now();
    for (int i = 0; i < 100; i++) // search for 100 values within the range 
    {
        linkedList.searchList(intArr[randArr[i]]); //search for the random indices 
    }
    auto end = chrono::steady_clock::now();
    search[indx] = chrono::duration_cast<chrono::microseconds>(end - start).count() / (100 * 1.0);
}

void insertFunction(float insert[100], float search[100], LL & linkedList, int size, int intArr[]) // the purpose of this function is to insert the values from the integer array into a linked list and 
//to record the time it takes for each set of 100 values
{
    auto insertStart = chrono::steady_clock::now();
    for (int i = 0, j = 0; i < size; i++)
    {
        linkedList.insertNode(intArr[i]); 
        if ((i + 1) % 100 == 0 && i != 1) // I use i + 1 because the array is zero index, so the last is index 9999: this only adds to the insert when the iteration is a multiple of 100 
        {
            auto insertEnd = chrono::steady_clock::now();
            insert[j] = chrono::duration_cast<chrono::microseconds>(insertEnd - insertStart).count() / (100 * 1.0); // divide by 100 because we are looking at the time of addition of 100 inserts 
            searchFunction(search, linkedList, size, intArr, i, j); // now we search through all elements of the LL 
            j++;
            insertStart = chrono::steady_clock::now();
        }
    }
}

int main()
{
    string dataSetA = "A.csv"; //Rather than command line, we can put file names here
    string dataSetB = "B.csv"; 
    int size = 10000; //number of elements we want to store 
    int intArr[size]; //to store the values from the csv 
    float insert[100]; // create the storage arrays for the runtimes 
    float search[100]; 
    if (processFile(dataSetA, intArr, size) == -1)
    {
        return 0;
    } 
    LL linkedList = LL(); //create a class object 
    

    //insert
    insertFunction(insert, search, linkedList, size, intArr); // this function also calls a search function 

    exportData(insert, search, "LLGraphsA.csv"); // now, we export the data 
    //linkedList.printPath();

    linkedList.deleteEntireNetwork(); // fresh start 

    // Now, we repeat for file B 
    if (processFile(dataSetB, intArr, size) == -1)
    {
        return 0;
    } 
    insertFunction(insert, search, linkedList, size, intArr);
    exportData(insert, search, "LLGraphsB.csv");
    //linkedList.printPath();
    linkedList.deleteEntireNetwork();

    return 0; 
}