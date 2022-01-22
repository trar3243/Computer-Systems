Project- README
CSCI 2270 Summer 2021 

This project required implementations of several data structures and analysis of run-time complexity. 
Any plagiarism of this project is expressly forbidden. 

This project includes 17 files:
A.csv
B.csv

bst.cpp
bst.hpp
bstdriver.cpp

hashchain.cpp
hashchain.hpp
hashchaindriver.cpp

hashlinear.cpp
hashlinear.hpp
hashlineardriver.cpp

hashquad.cpp
hashquad.hpp
hashquaddriver.cpp

sll.cpp
sll.hpp
slldriver.cpp


Required Text 
Two csv files, which are already included. Dataset A is named "A.csv" and dataSet B is named "B.csv". 

Required Libraries
To run this application you need to include the specific .hpp file for each structure. All necessary libraries are already included in each of the five driver files. These include:
"sll.hpp"
"bst.hpp"
"hashchain.hpp"
"hashlinear.hpp"
"hashquad.hpp"
<string>
<iostream>
<iomanip>
<cmath> 
<chrono>
<fstream>
<sstream>


Compile and Run
g++ -std=c++11 bst.cpp bstdriver.cpp

g++ -std=c++11 hashchain.cpp hashchaindriver.cpp

g++ -std=c++11 hashlinear.cpp hashlineardriver.cpp

g++ -std=c++11 hashquad.cpp hashquaddriver.cpp

g++ -std=c++11 sll.cpp slldriver.cpp

Notes
If you prefer to read in your own csv files, you would need to change the csv file names which are at the first two lines of each main function. 
The .csv files must be in the current folder. 
The output files will appear after you ./a.out so long as the input files are present within the current folder. 


Author
Troy Arthur 