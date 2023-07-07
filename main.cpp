/*
* Test main for Rational and Integer
*/

#include <iostream>
using namespace std;

#include "Integer.h"
#include "Rational.h"

using namespace cosc326;

/*
* Extra method to print string of Rational separately
* Same code from cout operator in Rational.cpp
*/
string getAsString(Rational input) {
    vector<char>v;
    //Values of i
    vector<char>whole = input.getWhole().getValue();
    vector<char>num = input.getNumerator().getValue();
    vector<char>denom = input.getDenominator().getValue();
    //Create strings
    string a(whole.begin(), whole.end());
    string b(num.begin(), num.end());
    string c(denom.begin(), denom.end());
    string final;
    string sign;
    //Lazy append
    if (!input.getSign()) sign = "-";
    if (a != "0") final = final + a;
    if (b != "0" && c != "0") final = b + "/" + c;
    if (a != "0" && b != "0" && c != "0") final = a + "." + b + "/" + c;
    string result = sign + final;
    return result;
}


/**
* Main method for running calculations
*/
int main() {

    Rational a = Rational("479/35");
    Rational b = Rational("533/20");
    cout<< a - b;

	return 0;
}


