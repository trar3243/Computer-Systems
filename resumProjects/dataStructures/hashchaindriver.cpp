//this is the driver file for a hash chain 
#include "hashchain.hpp"
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath> 
#include <chrono>
#include <fstream>
#include <sstream>

using namespace std; 

void exportData(float insertArr[100], float searchArr[100], int insertCollisions[], int searchCollisions[], string fileName) // the purpose of this function is to take the arrays that have the runtimes and export them to a csv file to create the graphs 
{
    ofstream out_file; 
    out_file.open(fileName); 
    if(out_file.fail()) // this will happen if the output file does not open 
    {
        cout << "failed to open the output file" << endl;
        return;
    }
    out_file << "Iteration" << ',' << "Insert" << ',' << "Search" << ',' << "Insert Collisions" << ',' << "Search Collisions" << ',' << "Unit: ns" << endl; //titles 
    for (int i = 0; i < 100; i++) // export the information in all relevant arrays 
    {
        out_file << i << ',' << insertArr[i] << ',' << searchArr[i] << ',' << insertCollisions[i] << ',' << searchCollisions[i] <<"\n"; 
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

void searchFunction(float search[100], HashTable & table, int size, int intArr[], int range, int indx)
{
    int randArr[100];
    for (int i = 0; i < 100; i++)//populate the rand index array 
    {
        randArr[i] = rand() % (range + 1);// range = 0,99 the first time, 199 the second time, etc: the range variable being passed in is equal to the element of the int array that was just inserted in the insert function
    }
    auto start = chrono::steady_clock::now();
    for (int i = 0; i < 100; i++) // search for 100 values within the range 
    {
        int random = rand() % (range + 1); // range = 0,99 the first time, 200 the second time, etc 
        table.searchItem(intArr[randArr[i]]); 
    }
    auto end = chrono::steady_clock::now();
    search[indx] = chrono::duration_cast<chrono::nanoseconds>(end - start).count() / (100 * 1.0); // divide by 100 because we want averages 
}

void insertFunction(float insert[100], float search[100], HashTable & table, int size, int intArr[], int totalCollisions[])
{
    auto insertStart = chrono::steady_clock::now();
    int k = 0; //counts num of inserts 
    for (int i = 0, j = 0; i < size; i++)
    {
        table.insertItem(intArr[i]); 
        k++; 
        if ((i + 1) % 100 == 0 && i != 1)// we have reached the one hundreth node 
        {
            auto insertEnd = chrono::steady_clock::now();
            insert[j] = chrono::duration_cast<chrono::nanoseconds>(insertEnd - insertStart).count() / (100 * 1.0); // divide by 100 because we are looking at the time of addition of 100 inserts 
            //now, for collisions
            totalCollisions[j * 2] = table.getNumOfCollision(); // add the total number from before this iteration and subtract from  the now total 
            searchFunction(search, table, size, intArr, i, j); // now we search through all elements
            totalCollisions[j * 2 + 1] = table.getNumOfCollision();
            j++;
            insertStart = chrono::steady_clock::now();
        }
    }
    cout << "completed " << k << " inserts" << endl;
}

void processCollisions(int totalCollisions[], int insertCollisions[], int searchCollisions[]) // the point of this function is to take the collision data for the total collisions and figure out the increase in
//collisions for each 100 inserts and searches
{
    for (int i = 0; i < 200; i++)
    {
        if (i % 2 == 0)//this is an insert value if the index is even 
        {
            if(i == 0)
            {
                insertCollisions[i] = totalCollisions[i]; //the first one is merekly the number of collisions at that time 
            }
            else
            {
                insertCollisions[i/2] = totalCollisions[i] - totalCollisions[i-1]; // otherwise, it is the 1/2 index of the total collisions array 
            }
        }
        else // it is a search collision 
        {
            searchCollisions[i/2] = totalCollisions[i] - totalCollisions[i-1]; //else, take the difference between the total collisions of the previous and current index 
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
    int totalCollisions[200]; //stores all collisions: we will piece it apart later 
    int searchCollisions[100];
    int insertCollisions[100]; 

    if (processFile(dataSetB, intArr, size) == -1) //if -1 is returned, then the file is not present 
    {
        return 0;
    } 
    
    HashTable table = HashTable(10009);//create with size 10009  
    
    insertFunction(insert, search, table, size, intArr, totalCollisions); //this will runt the inserts and searches 

    processCollisions(totalCollisions, insertCollisions, searchCollisions); // this processes the collision array into search and insert collisions 
    exportData(insert, search, insertCollisions, searchCollisions, "HashTableChainGraphB.csv");
    
    HashTable newTable = HashTable(10009);//reset 
    

    if (processFile(dataSetA, intArr, size) == -1)//if -1 is returned, then the file is not present 
    {
        return 0;
    } 
    insertFunction(insert, search, newTable, size, intArr, totalCollisions); // this will run and time the inserts, then will call the search function 
    processCollisions(totalCollisions, insertCollisions, searchCollisions); // this will process the total collisions array 
    exportData(insert, search, insertCollisions, searchCollisions, "HashTableChainGraphA.csv"); //this will export the data 
    //newTable.printTable(); //this will print the table in order of the indices with shown values in each bucket 

    return 0; 
}