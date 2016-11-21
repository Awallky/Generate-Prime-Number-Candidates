/*
Adam Walls

These methods are defined in the arithmetic class header file
*/
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <ostream>
#include "arithmetic.h"
//#include "getInts.h"

vector<int> arithmetic::ItBin2dec(vector<int> bin)
{
    //PRE:
    //POST:
    vector<int> w;//Define an empty vector w

    for( int i = 0; i < bin.size(); i+=1 )
        {
            w = By2inDec(w);
            if( bin[i] == 1 )//If the first element is 1, making the current number odd
                {
                if( !w.empty() )
                    w[0]= w[0] + 1;

                else if( w.empty() )
                    w.push_back(1);
                }
        }
    return w;
}

//This function multiplies the vector w by 2 in decimal form
vector<int> arithmetic::By2inDec( vector<int> w )
{
    //PRE:
    //POST:
    vector<int> by2;
    by2 = Add(w, w, 10);//Any number added to itself is that number*2
    return by2;
}

//this method works properly only under the assumption that each integer is contained in a vector of integers
//where the LSD is stored in the first position of the vector and the MSD is stored at the end of the vector
vector<int> arithmetic::Add(vector<int> num1, vector<int> num2, int base)
{
    //PRE:
    //POST:

    //Will determine which vector is larger then add them accordingly
	unsigned int size1 = num1.size();
	unsigned int size2 = num2.size();
	vector<int> answer;
	int carry = 0;
    int sum;

    //Do this if num2 larger
	if( size1 <= size2 )
        for( unsigned int i = 0; i < size2; i+=1 )
            {
            if( i > (size1-1) )//If vector is too small, append 0
                num1.push_back(0);

            sum = ( carry + num1[i] + num2[i] )%base;
            carry = ( carry + num1[i] + num2[i] )/base;
            answer.push_back(sum);//get the current digit

            if( (carry != 0) && (i == size2-1) )//can't forget the last carry
                answer.push_back(carry);
            }

    //Do this if num1 larger
    else if( size2 < size1 )
       for( unsigned int i = 0; i < size1; i+=1)
        {
            if( i > (size2-1) )//If vector is too small, append 0
                num2.push_back(0);

            sum = ( carry + num1[i] + num2[i] )%base;
            carry = ( carry + num1[i] + num2[i] )/base;
            answer.push_back(sum);//get the current digit

            if( (carry != 0) && (i == size1-1) )
                answer.push_back(carry);
        }
    return answer;
}

//This returns the difference of two integers iff that x >= y
vector<int> arithmetic::Sub(vector<int> x, vector<int> y)
{
    //PRE:
    //POST:
    //I: x has been shown to be >= y
    //I: they're both n-bit integers
    //O: the difference between x and y

    vector<int> d;//vector representing the difference between x and y
    d.resize( x.size() );
    y.resize( x.size() ); //Resizes y to size of x and inserts 0s at end of vector, where MSB is located
    int num, carry = 0;//carry digit to propagate through subtraction calcs, and num to make code cleaner

    for( int i = 0; i < x.size(); i+=1 )
        {
         num = carry+x[i]+y[i];
         if( (num%2)==1 )
            d[i] = 1;
         else
            d[i]=0;

         num = carry+d[i]+y[i];
         if(num >= 2)
            carry=1;
         else
            carry=0;
        }

    if( d.back() == 0 )
        while( d.back() == 0 )//removes all leading 0s from the difference
            d.pop_back();

    if( d.empty() )
        d.push_back(0);

    return d;
}


//This returns the product of two integers
vector<int> arithmetic::Mul(vector<int> x, vector<int> y)
{
    //PRE:
    //POST:

    vector<int> z;//empty vector representing the product of x,y
    z.push_back(0);
    for( int i = y.size()-1; i >= 0; i-=1 )
        {
         z = Add(z, z, base2);//shifts z once to the right, which in binary is Muling by 2
         if( y.at(i) == 1 )
            z = Add(z, x, base2);//since y is odd, must add x to z*2
        }
    return z;
}

//computes and modifies the quotient and remainder of the arithmetic object for x/y, where x>=y
void arithmetic::Div(vector<int> x, vector<int> y)
{
    //PRE:
    //POST:

    bool gT;//stores result of whether remainder is >= y
    vector<int> one;
    one.push_back(1);//vector containing one to be called when adding one to the quotient or remainder
    q.clear();//remove what was done to q in previous Div function call
    r.clear();//remove what was done to r in previous Div function call
    q.push_back(0);
    r.push_back(0);

    for( int i = x.size()-1; i >= 0; i-=1 )
        {

         q = Add(q, q, base2);//multiplies the quotient by 2
         r = Add(r, r, base2);//multiplies the remainder by 2

         if( x[i]==1 )
            r = Add(r, one, base2);//adds one to the remainder since x is odd

         gT = gTe(r, y);//function returns whether first argument >= second argument
         if( gT == true )//if remainder is >= y, must fix this
            {
             r = Sub(r, y);//subtracts y from 2r
             q = Add(q, one, base2);//adds one to the quotient
            }
        }
}



//Returns the remainder of x/y, where x>=y
vector<int> arithmetic::Mod(vector<int> x, vector<int> y)
{
    vector<int> rem;
    Div(x, y);
    rem = r;
   return rem;
}

//computes the modular exponentiation algorithm discussed in class
vector<int> arithmetic::Mod_Exp(vector<int> x, vector<int> y, vector<int> mod)
{
    //PRE:
    //POST:
    //I:
    //O:

    vector<int> z, quotient, remainder;
    z.push_back(1);//holds x^y mod N

    for( int i = y.size()-1; i >= 0; i-=1 )
        {
        z = Mul(z,z);//z = z^2
        z=Mod(z, mod);//get quotient and remainder

        if(y.at(i)==1)//if y is odd
            {
            z = Mul(z, x);//z = z*x because y is odd
            z = Mod(z, mod);
            }
        }
    return z;
}


//This function will compare two binary numbers and return true if x is >= y
bool arithmetic::gTe(vector<int> x, vector<int> y)
{
    //PRE:
    //POST:

    int sizX, sizY;//Size of the two vectors
    sizX=x.size(); // Get the size of first vector
    sizY=y.size(); //Get size of second vector

    //if size of x > y, then x > y
    if(sizX > sizY)
        return true;
    //if size of y > x, y > x
    if(sizY > sizX)
        return false;

    //at this point, the two vectors are at least the same size
    for(int i = sizX-1; i >= 0; i-=1)
        {
        //Will now look for the first instance where their bits differ
        //Stop searching if they differ and return true if x is 1 and y is 0
        if( (x[i] == 1) && (y[i]==0) )
            return true;
        else if((x[i]==0)&&(y[i]==1))
            return false;
        else
            ;//continue to the next bit
        }

    return true;//at this point, x and y agree on every bit value thus, x == y
    }


void arithmetic::print(vector<int> num)
{
    //PRE:
    //POST:

    //Prints the desired number in vector form with the LSD at the end
    cout << endl;
    cout << "[";
    for(int i = num.size()-1; i >= 0; i--)
        {
        if((i >= 0)&&(i < num.size()-1))
            cout << ", ";
        else
            ;
        cout << num.at(i);
        }
     cout << "]" << endl << endl;
}



bool arithmetic::eqOne(vector<int> ans)
{
    //PRE:
    //POST:
    //I: The result of the exp_mod function
    //O: whether 3^N-1 == l(mod N), i.e. if N is prime
    if( ans.size()==1 && ans.at(0)==1)
    {
        return true;
    }
    return false;
}
