/*
    Author: Adam Walls
*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <ostream>
#include "getInts.h"
#include "arithmetic.h"

using namespace std;

vector<int> genRandNum(int n);//generates a prime number candidate
void result(vector< vector<int> > Ran);//prints whether each candidate was actually prime
unsigned int binToDec(vector<int> n);//converts a vector representation of a binary integer to a decimal
void GetRandomNumbersToTxtFile(int numsToGen, int numOfBits, arithmetic& a);//sends generated numbers to a text file
bool brutePrimeCheck(int num);//tests an integer for primality by looking for factors up to the square root of the number

int main()
{
    arithmetic a;
    bool isPrime;
    unsigned int dec = 0;
    vector<int> temp, result;
    vector< vector<int> > Ran;

    GetRandomNumbersToTxtFile(100, 16, a);//will generate 100 16-bit integers uniformly at random
    getNumsfromTxt(Ran, 16);//Gets 16-bit numbers from txt file and puts them into Ran

    for(int i = 0; i < Ran.size(); i++)
    {
        temp = Ran.at(i);//gets the current vector representation of the binary integer
        dec = binToDec(temp);//converts the integer to an unsigned decimal integer
        a.print(Ran[i]);
        cout << "The integer in decimal is: " << dec << endl;
        isPrime = brutePrimeCheck(dec);//checks to see if the integer can be divided into evenly(is not prime)
        result.push_back(isPrime);//stores the result in the vector result
    }
    cout << "Here is a vector corresponding to each prime number candidate: (1 is prime, 0 is composite)" << endl;
    a.print(result);//prints the results for each integer as they appeared in the txt file*/
    return 0;
}



//generates a random binary number eligible for primality
vector<int> genRandNum(int n)
{
    vector<int> a(n, 1);
    int j;//a temporary variable to catch the random number

    for(unsigned int i = 1; i < a.size()-1; i++)
        {
         j = (rand()%(2)); //random number from 0 to i
         a.at(i)=j;
        }
    return a;
}

//outputs the prime numbers generated to a text file
void result(vector< vector<int> > Ran)
{
    ofstream outFile; // Create output file

    outFile.open("result.txt"); // Open txt file named intData

    for(unsigned long int i = 0; i < 100; i++)
        {
            for(int j = 0; j < Ran.at(i).size(); j++)
                {
                outFile << Ran.at(i).at(j); // gets LSD
                }
            outFile << "\n";
        }
}


//This function takes the vector representation of any binary number up to 16 bits and returns a decimal integer
unsigned int binToDec(vector<int> n)
{
    unsigned int dec=0;
    for(int i = n.size()-1; i >= 0; i--)
    {
        //cout << n.at(i) << " ";
        dec+=n.at(i);
        if(i > 0)//accounts for 2^0
            dec*=2;
        //cout<< dec << endl;
    }
    return dec;
}

//This generates the number of prime candidates to generate
void GetRandomNumbersToTxtFile(int numsToGen, int numOfBits, arithmetic& a)
{
    bool isPrime;
    unsigned int count=0;
    vector<int> mod, x(2,1), y, ans, one(1,1);
    vector< vector<int> > Ran;

    for(int i=0; i<1; i++)//random number generator seed
		srand(int(time(0)));

    while(Ran.size() < numsToGen)
        {
            count+=1;
            vector<int> ran;
            ran = genRandNum(numOfBits);//set to generate random 16-bit prime integer candidate
            y = a.Sub(ran, one);//y = N-1
            ans = a.Mod_Exp(x, y, ran);// ans = 3^N-1 (mod N)

            isPrime = a.eqOne(ans);//checks to see if it passes the primality test
            if(isPrime)
            {
                Ran.push_back(ran);
                cout << "Numbers left to generate: " << numsToGen - Ran.size() << endl;//shows user how many integers left to generate
            }
        }
        cout << "The number of attempts to generate the prime";
        cout << "candidates is "<< count << "." <<endl; //tracks the number of tries to generate 100 prime #s
    RantoTxt(Ran, numOfBits);//sends each integer to txt file
}


//tests whether an integer is composite
bool brutePrimeCheck(int num)
{
    bool gt = true;
    unsigned int root = 2;
    unsigned int squared = root*root;
    while(squared < num)
    {
        if(num%root == 0)
        {
            cout << root << endl;
            return false;
        }
        root+=1;
        squared=root*root;
    }
    return true;
}
