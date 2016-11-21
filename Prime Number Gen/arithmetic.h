#include <iostream>
#include <vector>

#ifndef ARITHMETIC_H_INCLUDED
#define ARITHMETIC_H_INCLUDED

using namespace std;

const int base2 = 2;
class arithmetic
{
private:
    vector<int> sum;
    vector<int> q;
    vector<int> r;
public:
    vector<int> Add(vector<int> x, vector<int> y, int base);
    vector<int> Sub(vector<int> x, vector<int> y);
    vector<int> Mul(vector<int> x, vector<int> y);
    void Div(vector<int> x, vector<int> y);
    vector<int> Mod(vector<int> x, vector<int> y);
    vector<int> Mod_Exp(vector<int> x, vector<int> y, vector<int> n);
    vector<int> bin2Dec(vector<int> bin);
    vector<int> ItBin2dec(vector<int> bin);
    vector<int> By2inDec( vector<int> w );
    bool gTe(vector<int> x, vector<int> y);
    void print(vector<int> x);
    bool eqOne(vector<int> x);
};
#endif // ARITHMETIC_H_INCLUDED
