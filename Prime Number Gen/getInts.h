/*
Adam Walls
CS315-002
*/
#ifndef GETINTS_H_INCLUDED
#define GETINTS_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include "arithmetic.h"

using namespace std;

//This function parses the txt file line by line and puts them into vectors num1 & num2
void txtToVec(vector<int>& mod, vector<int>& num1, vector<int>& num2)
{
    //PRE:
    //POST:

    int num;
    string fileName;
    ifstream numFile; //variable to hold txt file data

    cout << "Enter the text file name for the modular number.";
    cout << endl;
    cin >> fileName;

    numFile.open(fileName.c_str()); //variable to hold txt file data

    //loop through txt file
    while(numFile >> num)
        mod.insert(mod.end(), num);

    //close txt file
    numFile.close();

    //add 0 if the txt file is empty
    if(mod.size()==0)
        mod.insert(mod.end(), 0);

    cout << "Enter the text file name for the first number.";
    cout << endl;
    cin >> fileName;

    numFile.open(fileName.c_str()); //variable to hold txt file data

    //loop through txt file
    while(numFile >> num)
        num1.insert(num1.end(), num);

    //close txt file
    numFile.close();

    //add 0 if the txt file is empty
    if(num1.size()==0)
        num1.insert(num1.end(), 0);

    cout << "Enter the text file name for the second number.";
    cout << endl;
    cin >> fileName;

    //Open second txt file
    numFile.open(fileName.c_str());

    //loop through txt file
    while(numFile >> num)
        num2.insert(num2.end(), num);
    numFile.close();

    //add 0 if the txt file is empty
    if(num2.size()==0)
        num2.insert(num2.end(), 0);
}

vector<int> StrtoInt(string num)
{
    //PRE:
    //POST:

    vector<int> n;
    string t;
    for(int i = 0; i < num.size(); i++)
    {
        t = num.at(i);//gets digit at current position ion the string
        int temp = atoi(t.c_str());//converts character into integer
        n.insert(n.end(), temp);//vector gets digit at current position in the string
    }
    return n;
}


//Gets the contents of a text file and reads them into a nested vector of ints test
//calls the StrtoInt function to do so
void getNumsfromTxt(vector< vector<int> >& test, int bits)
{
    //PRE:
    //POST:

    ostringstream os;
    os << "result" << bits << ".txt";
    string num, fileName = os.str();
    cout << fileName << endl;
    ifstream numFile; //variable to hold txt file data

    cout << "Now reading from txt file into test vector.";
    cout << endl;

    numFile.open(fileName.c_str()); //variable to hold txt file data

    //loop through txt file
    while(numFile >> num)
        {
            test.push_back(StrtoInt(num));
        }

    //close txt file
    numFile.close();
}

//Converts the contents of a vector of ints into a text file with a given amount of
//integers in the vector built into the name of the text file
void RantoTxt(vector<vector<int> > Ran, int numsToGen)
{
    //PRE:
    //POST:

    ofstream outFile; // Create output file
    ostringstream os;
    string filename;
    os << "result" << numsToGen << ".txt";
    filename = os.str();

    outFile.open(filename.c_str()); // Open txt file named intData

    for(int i = 0; i < Ran.size(); i++)
        {
            for(int j = 0; j < Ran.at(i).size(); j++)
                {
                    outFile << Ran.at(i).at(j); // gets LSD
                }
             outFile << "\n";
        }
    outFile.close();
    }

#endif // GETINTS_H_INCLUDED
