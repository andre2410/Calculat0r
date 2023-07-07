#pragma once
/**
 *      Cosc326 Etude 8: Rationals. Written May 2023.
 *      This is our solution to the Rationals etude.
 *      @author Andrew Goh
 *      @author Josh Argyle
 */
// Most compilers understand the once pragma, but just in case...
#ifndef RATIONAL_H_INCLUDED
#define RATIONAL_H_INCLUDED

#include <iostream>
#include <string>
#include "Integer.h"

namespace cosc326 {

	class Rational {
    
	public:
		//Constructors
		Rational();
        Rational(const std::string& str);
        Rational(const Rational& r);
        Rational(const Integer& a); // a
        Rational(const Integer& a, const Integer& b); // a/b
        Rational(const Integer& a, const Integer& b, const Integer& c); // a + b/c

        //Destructor
		~Rational();

		//Accessors
		Integer getWhole() const;
		Integer getNumerator() const;
		Integer getDenominator() const;
		bool getSign() const;

		//Mutators
		void setWhole(Integer& whole);
		void setNumerator(Integer& num);
		void setDenominator(Integer& denom);
		void setSign(bool sign);

		//Assign operator
        Rational& operator=( const Rational& r); // q = r;
        
		// Unary operators
		Rational operator-(); // -r;
		Rational operator+(); // +r;
	   
        // Arithmetic assignment operators
		Rational& operator+=(const Rational& r); // q += r;
		Rational& operator-=(const Rational& r); // q -= r;
		Rational& operator*=(const Rational& r); // q *= r;
		Rational& operator/=(const Rational& r); // q /= r;
												 
		// lhs < rhs -- a 'friend' means < isn't a member, but can access the private parts of the class.
		// You may need to make some other functions friends, but do so sparingly.
		friend bool operator<(const Rational& lhs, const Rational& rhs);

	private:
		// Can add internal storage or methods here
		Integer whole;
		Integer numerator;
		Integer denominator;
		bool sign = true;
    };

	// Binary operators
	Rational operator+(const Rational& lhs, const Rational& rhs); // lhs + rhs;
	Rational operator-(const Rational& lhs, const Rational& rhs); // lhs - rhs;
	Rational operator*(const Rational& lhs, const Rational& rhs); // lhs * rhs;
	Rational operator/(const Rational& lhs, const Rational& rhs); // lhs / rhs;
	
	//Print operators
	std::ostream& operator<<(std::ostream& os, const Rational& i);  // std::cout << i << std::endl;
	std::istream& operator>>(std::istream& is, Rational& i);        // std::cin >> i;

	//Comparison operators
	bool operator> (const Rational& lhs, const Rational& rhs); // lhs > rhs
	bool operator<=(const Rational& lhs, const Rational& rhs); // lhs <= rhs
	bool operator>=(const Rational& lhs, const Rational& rhs); // lhs >= rhs
	bool operator==(const Rational& lhs, const Rational& rhs); // lhs == rhs
	bool operator!=(const Rational& lhs, const Rational& rhs); // lhs != rhs

	//Helper function
	bool isZeroed(const Rational& rational);

}

#endif
