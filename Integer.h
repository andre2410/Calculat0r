/**
 *      Cosc326 Etude 8: Rationals. Written May 2023.
 *      This is our solution to the Rationals etude.
 *      @author Andrew Goh
 *      @author Josh Argyle
 */
// Most compilers understand the once pragma, but just in case...
#ifndef INTEGER_H_INCLUDED
#define INTEGER_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>

using namespace std;
namespace cosc326 {

	class Integer {

	public:
		//Constructors
		Integer();                             // Integer i;
		Integer(const Integer& i);             // Integer j(i);
		Integer(const string& s);         // Integer k("123");
        Integer(const vector<char>& initialValue);         // Char vector constructor

		//Destructor
		~Integer();

		//Accessors
		vector<char> getValue() const;
        bool getSign() const;

		//Mutators
		void setValue(const string& s);
        void setSign(bool sign);

		//Assign operator
		Integer& operator=(const Integer& i);  // j = i;

		// Unary operators
		Integer operator-();                   // -j;
		Integer operator+();                   // +j;

		// Arithmetic assignment operators
		Integer& operator+=(const Integer& i); // j += i;
		Integer& operator-=(const Integer& i); // j -= i;
		Integer& operator*=(const Integer& i); // j *= i;
		Integer& operator/=(const Integer& i); // j /= i;
		Integer& operator%=(const Integer& i); // j %= i;

		// lhs < rhs -- a 'friend' means operator isn't a member, but can access the private parts of the class.
		// You may need to make some other functions friends, but do so sparingly.
		friend bool operator<(const Integer& lhs, const Integer& rhs);

	private:
		// Can add internal storage or methods here
		std::vector<char> value;
		bool sign = true;
	};

	// Binary operators
	Integer operator+(const Integer& lhs, const Integer& rhs); // lhs + rhs;
	Integer operator-(const Integer& lhs, const Integer& rhs); // lhs - rhs;
	Integer operator*(const Integer& lhs, const Integer& rhs); // lhs * rhs;
	Integer operator/(const Integer& lhs, const Integer& rhs); // lhs / rhs;
	Integer operator%(const Integer& lhs, const Integer& rhs); // lhs % rhs;

	//Print operators (overloads cout and cin)
	std::ostream& operator<<(std::ostream& os, const Integer& i);  // std::cout << i << std::endl;
	std::istream& operator>>(std::istream& is, Integer& i);        // std::cin >> i;

	//Comparison operators
	bool operator< (const Integer& lhs, const Integer& rhs); // lhs < rhs
	bool operator> (const Integer& lhs, const Integer& rhs); // lhs > rhs
	bool operator<=(const Integer& lhs, const Integer& rhs); // lhs <= rhs
	bool operator>=(const Integer& lhs, const Integer& rhs); // lhs >= rhs
	bool operator==(const Integer& lhs, const Integer& rhs); // lhs == rhs
	bool operator!=(const Integer& lhs, const Integer& rhs); // lhs != rhs

	//Greatest common divisor
	Integer gcd(const Integer& a, const Integer& b);  // i = gcd(a, b);

	//Helper functions
    Integer splitInHalf(const Integer& lhs);
    Integer stripZeros(const Integer& lhs);
}

#endif
