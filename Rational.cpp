#include "Rational.h"
#include "sstream"

/**
 *      Cosc326 Etude 8: Rationals. Written May 2023.
 *      This is our solution to the Rationals etude.
 *      @author Andrew Goh
 *      @author Josh Argyle
 */

namespace cosc326 {

	/**
	* Default constructor that creates Rational with a value of 0
	*/
	Rational::Rational() {
		this->whole = Integer();
		this->denominator = Integer();
		this->numerator = Integer();
	}

	/**
	* Constructor that takes string
    * ASSUMES STRING FOLLOWS PROPER FORMAT IN README
	*/
    Rational::Rational(const std::string& str) {
        //Variables
        string value = "";
        Integer w;
        Integer d;
        Integer n;
        //Loop through string and get parts
        for (auto x : str) {
            if (x == '-') {
                this->sign = false;
                continue;
            }
            if (x == '+') continue;
            //Set whole if theres a .
            if (x == '.') {
                w = Integer(value);
                value = "";
                continue;
            }
            if (x == '/') { //Set numerator if theres a /
                n = Integer(value);
                value = "";
                continue;
            }
            value = value + x;
        }
        if (d == Integer() && n == Integer()) w = Integer(value);
        //Set denominator
        d = Integer(value);
        //Simplify fraction if any
        if (n != Integer() && d != Integer()) {
            //If numerator is bigger than denominator, add to whole and fix denominator
            if (n >= d) {
                Integer div = n / d;
                n %= d;
                w += div;
            }
            //Simplify fraction
            Integer g = gcd(n, d);
            //Divide d and n by gcd
            d /= g;
            n /= g;
        }
        //Fully simplify if d = n;
        if (d == n) {
            d = Integer();
            n = Integer();
        }
        //If d or n = 0; both have to be 0;
        if (d == Integer() || n == Integer()) {
            d = Integer();
            n = Integer();
        }
        //Set params
        this->whole = w;
        this->denominator = d;
        this->numerator = n;

    }

	/**
	* Constructor that duplicates the provided Rational
	*/
	Rational::Rational(const Rational& r) {
		this->whole = r.getWhole();
		this->denominator = r.getDenominator();
		this->numerator = r.getNumerator();
		this->sign = r.getSign();
	}

	/**
	* Constructor that sets the whole number value with an Integer
    * Sets numerator and denominator to 0 and accounts for the sign of the Integer
	*/
	Rational::Rational(const Integer& a) { 
		this->whole = a.getValue();
        this->denominator = Integer();
        this->numerator = Integer();
        //Set sign
        this->sign = a.getSign();
	}

	/**
	* Constructor that sets the whole number value with two integers 
	* Essentially a / b 
	*/ 
	Rational::Rational(const Integer& a, const Integer& b) {
        //Variables
        string value = ""; 
        Integer w; 
        Integer d = b; 
        Integer n = a;
        //Account for both a and b being negative to avoid oversimplification
        if (!a.getSign() && !b.getSign()) {
            d.setSign(true);
            n.setSign(true);
        }
        //Simplify fraction if any
        if (n != Integer() && d != Integer()) { 
            //If numerator is bigger than denominator, add to whole and fix denominator
            if (n >= d) { 
                Integer div = n / d;
                n %= d;
                w += div;
            } 
            //Simplify fraction
            Integer g = gcd(n, d); 
            //Divide d and n by gcd
            d /= g;
            n /= g;
        }
        //Fully simplify if d = 1;
        if (d == n) {
            d = Integer();
            n = Integer();
        }
        //If d or n = 0; both have to be 0;
        if (d == Integer() || n == Integer()) {
            d = Integer();
            n = Integer();
        }
        //Set sign
        if (!a.getSign() && b.getSign()) this->sign = false;
        if (a.getSign() && !b.getSign()) this->sign = false;
        //Set params
        this->whole = w; 
        this->denominator = d; 
        this->numerator = n; 
	}

	/**
	* Constructor that sets the whole number value with two integers
	* Essentially a + b / c
	*/
	Rational::Rational(const Integer& a, const Integer& b, const Integer& c) {
        //Variables
        string value = "";
        Integer w = a;
        Integer d = c;
        Integer n = b;
        //Account for both a and b being negative to avoid oversimplification
        if (!b.getSign() && !c.getSign()) {
            d.setSign(true);
            n.setSign(true);
        }
        //Simplify fraction if any
        if (n != Integer() && d != Integer()) {
            //If numerator is bigger than denominator, add to whole and fix denominator
            if (n >= d) {
                Integer div = n / d;
                n %= d;
                w += div;
            }
            //Simplify fraction
            Integer g = gcd(n, d);
            //Divide d and n by gcd
            d /= g;
            n /= g;
        }
        //Fully simplify if d = 1;
        if (d == n) {
            d = Integer();
            n = Integer();
        }
        //If d or n = 0; both have to be 0;
        if (d == Integer() || n == Integer()) {
            d = Integer();
            n = Integer();
        }
        //Set sign 
        if (!a.getSign() && b.getSign() && c.getSign()) this->sign = false;
        if (a.getSign() && !b.getSign() && c.getSign()) this->sign = false;
        if (a.getSign() && b.getSign() && !c.getSign()) this->sign = false;
        //Set params
        this->whole = w;
        this->denominator = d;
        this->numerator = n;
    }

	/*
	* Destructor for Rational
	*/
	Rational::~Rational() {

	}

	/**
	* Accessor for local variable whole
	*/
	Integer Rational::getWhole() const{
		return this->whole;
	}

	/**
	* Accessor for local variable numerator
	*/
	Integer Rational::getNumerator() const{
		return this->numerator;
	}

	/**
	* Accessor for local variable denominator
	*/
	Integer Rational::getDenominator() const{
		return this->denominator;
	}

	/**
	* Accessor for local variable sign
	*/
	bool Rational::getSign() const{
		return this->sign;
	}

	/**
	* Mutator for local variable whole
	*/
	void Rational::setWhole(Integer& whole) {
		this->whole = whole;
	}

	/**
	* Mutator for local variable numerator
	*/
	void Rational::setNumerator(Integer& num){
		this->numerator = num;
	}

	/**
	* Mutator for local variable denominator
	*/
	void Rational::setDenominator(Integer& denom){
		this->denominator= denom;
	}

	/**
	* Mutator for local variable sign
	*/
	void Rational::setSign(bool sign){
		this->sign = sign;
	}

    /**
    * Function to set Rational to other Rational value
    */
	Rational& Rational::operator=(const Rational& r) {
		this->whole = r.getWhole();
		this->denominator = r.getDenominator(); 
		this->numerator = r.getNumerator(); 
		this->sign = r.getSign();
		return *this;
	}

    /**
    * Set sign of rational to negative
    */
	Rational Rational::operator-() {
        this->setSign(false);
		return Rational(*this);
	}

    /**
    * Set sign of rational to positive
    */
	Rational Rational::operator+() {
        this->setSign(true);
		return Rational(*this);
	}

    /**
    * Function for addition
    * Equivalent to q = q + r;
    */
    Rational& Rational::operator+=(const Rational& r) {
        // If the left sign is positive and right is negative, the result will be a negative version of a subtraction.
        if (this->getSign() && !r.getSign()) {
            Rational lhs = Rational(*this);
            lhs.setSign(true);
            Rational rhs = Rational(r);
            rhs.setSign(true);
            Rational result = rhs - lhs;
            result.setSign(false);
            *this = result;
            return *this;
        }
        // If the left sign is negative and the right is a positive, the result will be a positive version of a subtraction.
        if (!this->getSign() && r.getSign()) {
            Rational lhs = Rational(*this);
            lhs.setSign(true);
            Rational rhs = Rational(r);
            rhs.setSign(true);
            Rational result = lhs - rhs;
            result.setSign(true);
            *this = result;
            return *this;
        }
        // LHS values.
        Integer lhsWhole = this->getWhole();
        Integer lhsNumer = this->getNumerator();
        Integer lhsDenom = this->getDenominator();
        // RHS values.
        Integer rhsWhole = r.getWhole();
        Integer rhsNumer = r.getNumerator();
        Integer rhsDenom = r.getDenominator();
        //Check if either denominator or numerator is 0, set to 1 in order not to destroy calculation
        if (lhsDenom == Integer("0")) lhsDenom = Integer("1");
        if (rhsDenom == Integer("0")) rhsDenom = Integer("1");
        //Calculate component copies of q and r
        Integer lhsWorkingNumerator = ((lhsWhole * lhsDenom) + lhsNumer) * rhsDenom;
        Integer rhsWorkingNumerator = ((rhsWhole * rhsDenom) + rhsNumer) * lhsDenom;
        Integer workingDenominator = (rhsDenom * lhsDenom);
        Integer workingNumerator = lhsWorkingNumerator + rhsWorkingNumerator;
        //Simplify calculated components using GCD
        Integer GCD = gcd(workingNumerator, workingDenominator);
        workingNumerator /= GCD;
        workingDenominator /= GCD;
        Integer wholeResult = workingNumerator / workingDenominator;
        workingNumerator %= workingDenominator;
        // If the signs are both negative, the result will be a negative.
        if (!this->getSign() && !r.getSign()) {
            this->setSign(false);
        }
        // If the signs are both positive, the result will be a positive.
        if (this->getSign() && r.getSign()) {
            this->setSign(true);
        }
        //Assign final values to Rational
        this->setWhole(wholeResult);
        this->setNumerator(workingNumerator);
        this->setDenominator(workingDenominator);

        return *this;
    }

    /**
    * Function for subtraction
    * Equivalent to q = q - r;
    */
    Rational& Rational::operator-=(const Rational& r) {
        //Set copies of Rationals
        Rational lhsCopy = Rational(*this);
        Rational rhsCopy = Rational(r);
        // If the signs are both negative, the result will be a negative.
        if (!this->getSign() && !r.getSign()) {
            this->setSign(false);
        }
        // If the signs are both positive, the result will be a positive, only if right side is smaller.
        if (lhsCopy < rhsCopy && this->getSign() && r.getSign()) {
            this->setSign(true);
        }
        // If the left sign is positive and right is negative, the result will be a negative version of an addition.
        if (this->getSign() && !r.getSign()) {
            Rational lhs = Rational(*this);
            lhs.setSign(true);
            Rational rhs = Rational(r);
            rhs.setSign(true);
            Rational result = rhs + lhs;
            result.setSign(true);
            *this = result;
            return *this;
        }
        // If the left sign is negative and the right is a positive, the result will be a positive version of an addition.
        if (!this->getSign() && r.getSign()) {
            Rational lhs = Rational(*this);
            lhs.setSign(true);
            Rational rhs = Rational(r);
            rhs.setSign(true);
            Rational result = lhs + rhs;
            result.setSign(false);
            *this = result;
            return *this;
        }
        // LHS values.
        Integer lhsWhole = this->getWhole();
        Integer lhsNumer = this->getNumerator();
        Integer lhsDenom = this->getDenominator();
        // RHS values.
        Integer rhsWhole = r.getWhole();
        Integer rhsNumer = r.getNumerator();
        Integer rhsDenom = r.getDenominator();
        //Check if either denominator or numerator is 0, set to 1 in order not to destroy calculation
        if (lhsDenom == Integer("0")) lhsDenom = Integer("1");
        if (rhsDenom == Integer("0")) rhsDenom = Integer("1");
        //Calculate component copies of q and r
        Integer lhsWorkingNumerator = ((lhsWhole * lhsDenom) + lhsNumer) * rhsDenom;
        Integer rhsWorkingNumerator = ((rhsWhole * rhsDenom) + rhsNumer) * lhsDenom;
        //If numerator is 0, assing whole to numerator and recalculate
        if (lhsWorkingNumerator == Integer("0")) lhsWorkingNumerator = lhsWhole;
        if (rhsWorkingNumerator == Integer("0")) rhsWorkingNumerator = rhsWhole;
        Integer workingDenominator = (rhsDenom * lhsDenom);
        Integer workingNumerator = lhsWorkingNumerator - rhsWorkingNumerator;
        //Simplify components using gcd
        Integer GCD = gcd(workingNumerator, workingDenominator);
        workingNumerator /= GCD;
        workingDenominator /= GCD;
        Integer wholeResult = workingNumerator / workingDenominator;
        workingNumerator %= workingDenominator;
        // If the signs are both negative, the result will be a positive.
        if (lhsCopy > rhsCopy && !this->getSign() && !r.getSign()) {
            this->setSign(true);
        }
        // If the signs are both positive, the result will be a negative.
        if (lhsCopy < rhsCopy && this->getSign() && r.getSign()) {
            this->setSign(false);
        }
        //If lhs is smaller, set sign to negative
        if (lhsCopy < rhsCopy) {
            this->setSign(false);
        }
        //Assign params
        this->setWhole(wholeResult);
        this->setNumerator(workingNumerator);
        this->setDenominator(workingDenominator);

        return *this;
    }

    /**
     * Function for multiplication
     * Equivalent to q = q * r;
     */
	Rational& Rational::operator*=(const Rational& r) {
        // LHS values.
        Integer lhsWhole = this->getWhole();
        Integer lhsNumer = this->getNumerator();
        Integer lhsDenom = this->getDenominator();
        // RHS values.
        Integer rhsWhole = r.getWhole();
        Integer rhsNumer = r.getNumerator();
        Integer rhsDenom = r.getDenominator();
        //If either = 0, set to 1 to not destroy calculation
        if (lhsDenom == Integer("0")) lhsDenom = Integer("1");
        if (rhsDenom == Integer("0")) rhsDenom = Integer("1");
        // Get the whole as fractions.
        Integer lhsWorkingNumerator = (lhsWhole * lhsDenom) + lhsNumer;
        Integer rhsWorkingNumerator = (rhsWhole * rhsDenom) + rhsNumer;
        // Get the whole numerator and denominator.
        Integer workingNumerator = lhsWorkingNumerator * rhsWorkingNumerator;
        Integer workingDenominator = lhsDenom * rhsDenom;
        // Simplify using gcd
        Integer resultWhole = workingNumerator / workingDenominator;
        workingNumerator %= workingDenominator;
        Integer GCD = gcd(workingNumerator, workingDenominator);
        workingNumerator /= GCD;
        workingDenominator /= GCD;
        // If both signs are negative or positive, this sign is positive.
        if (this->getSign() == r.getSign()) this->setSign(true);
        // If they are different, the sign is negative.
        else if (this->getSign() != r.getSign()) this->setSign(false);
        //Assign params
        this->setWhole(resultWhole);
        this->setNumerator(workingNumerator);
        this->setDenominator(workingDenominator);

		return *this;
	}

    /**
     * Function for division
     * Equivalent to q = q / r;
     */
	Rational& Rational::operator/=(const Rational& r) {
        // LHS values.
        Integer lhsWhole = this->getWhole();
        Integer lhsNumer = this->getNumerator();
        Integer lhsDenom = this->getDenominator();
        // RHS values.
        Integer rhsWhole = r.getWhole();
        Integer rhsNumer = r.getNumerator();
        Integer rhsDenom = r.getDenominator();
        //If either = 0, set to 1 to not destroy calculation
        if (lhsDenom == Integer("0")) lhsDenom = Integer("1");
        if (rhsDenom == Integer("0")) rhsDenom = Integer("1");
        // Get the whole as fractions.
        Integer lhsWorkingNumerator = (lhsWhole * lhsDenom) + lhsNumer;
        Integer rhsWorkingNumerator = (rhsWhole * rhsDenom) + rhsNumer;
        // Get the whole numerator and denominator, by swapping the numerator and denominator
        // of the rhs fraction.
        Integer workingNumerator = lhsWorkingNumerator * rhsDenom;
        if (workingNumerator == Integer("0")) workingNumerator = lhsWhole;
        Integer workingDenominator = rhsWorkingNumerator * lhsDenom;
        if (workingDenominator == Integer("0")) workingDenominator = rhsWhole;
        // Simplify using gcd
        Integer resultWhole = workingNumerator / workingDenominator;
        workingNumerator %= workingDenominator;
        Integer GCD = gcd(workingNumerator, workingDenominator);
        workingNumerator /= GCD;
        workingDenominator /= GCD;
        //Assign params using a copy
        Rational a = Rational();
        a.setWhole(resultWhole);
        a.setNumerator(workingNumerator);
        a.setDenominator(workingDenominator);
        a.setSign(this->getSign());

        *this = a;
        return *this;
    }

    //Following operations uses the operations above for calculation
    //e.g + would call +=

    /**
    * Function for binary addition
    * Equivalent to q + r;
    */
	Rational operator+(const Rational& lhs, const Rational& rhs) {
        Rational lhsCopy = Rational(lhs);
        lhsCopy += rhs;
		return lhsCopy;
	}

    /**
    * Function for binary subtraction
    * Equivalent to q - r;
    */
	Rational operator-(const Rational& lhs, const Rational& rhs) {
        Rational lhsCopy = Rational(lhs);
        lhsCopy -= rhs;
        return lhsCopy;
	}

    /**
    * Function for binary multiplication
    * Equivalent to q * r;
    */
	Rational operator*(const Rational& lhs, const Rational& rhs) {
        Rational lhsCopy = Rational(lhs);
        lhsCopy *= rhs;
        return lhsCopy;
	}

    /**
    * Function for binary division
    * Equivalent to q / r;
    */
	Rational operator/(const Rational& lhs, const Rational& rhs) {
        Rational lhsCopy = Rational(lhs);
        lhsCopy /= rhs;
        return lhsCopy;
	}

    //Functions for printing options.

    /**
    * Overloading ostream operator for Rational class
    */
	std::ostream& operator<<(std::ostream& os, const Rational& i) {
		vector<char>v;
		//Values of i
		vector<char>whole = i.getWhole().getValue();
		vector<char>num = i.getNumerator().getValue();
		vector<char>denom = i.getDenominator().getValue();
		//Create strings
		string a(whole.begin(), whole.end());
		string b(num.begin(), num.end());
		string c(denom.begin(), denom.end());
		string final;
		string sign;
		//Lazy append
		if (!i.getSign()) sign = "-";
		if (a != "0") final = final + a;
		if (b != "0" && c != "0") final = b + "/" + c;
		if (a != "0" && b != "0" && c != "0") final = a + "." + b + "/" + c;
		os << sign + final << endl; 
		return os;
	}

    /**
     * Overloading istream operator for Rational class
     */
	std::istream& operator>>(std::istream& is, Rational& i) {
		string s;
		is >> s;
		Rational temp = Rational(s);
		i = temp;
		return is;
	}

    //Functions for comparing 2 integer classes

    /**
    * Function for less than comparison
    * Equivalent to q < r;
    */
	bool operator<(const Rational& lhs, const Rational& rhs) {
        // If the value is not greater than and not equal to, it must be smaller.
        if (!(lhs > rhs) && !(lhs == rhs)) return true;
		return false;
	}

    /**
    * Function for checking if Rational value is 0
    */
    bool isZeroed(const Rational& input) {
        // Make an empty Integer.
        Integer zeroed = Integer("0");
        // Compare each part with the empty integer.
        Integer whole = input.getWhole();
        Integer numerator = input.getNumerator();
        Integer denominator = input.getDenominator();
        // If they are all 0, return true;
        if (whole == zeroed && numerator == zeroed && denominator == zeroed) {
            return true;
        }
        return false;
    }

    /**
    * Function for greater than comparison
    * Equivalent to q > r;
    */
    bool operator>(const Rational& lhs, const Rational& rhs) {
        // Copy the inputs.
        Rational lhsCopy = Rational(lhs);
        Rational rhsCopy = Rational(rhs);
        // If either is equal to 0, set the signs to positive.
        if (isZeroed(lhsCopy)) lhsCopy.setSign(true);
        if (isZeroed(rhsCopy)) rhsCopy.setSign(true);
        // If lhs is negative and rhs is positive, return false.
        if (!lhsCopy.getSign() && rhsCopy.getSign()) return false;
        // If rhs is negative and lhs is positive, return true.
        else if (lhsCopy.getSign() && !rhsCopy.getSign()) return false;
        // If they both negative, return the opposite value.
        else if (!lhsCopy.getSign() && !rhsCopy.getSign()) {
            Rational lhsNegCopy = Rational(lhs);
            lhsNegCopy.setSign(true);
            Rational rhsNegCopy = Rational(rhs);
            rhsNegCopy.setSign(true);
            return (lhsNegCopy < rhsNegCopy);
        }
        // Otherwise its two positive numbers and we can just make each number into a fraction and compare numerators.
        Integer lhsWorkingNumerator = (lhsCopy.getWhole() * lhsCopy.getDenominator()) + lhsCopy.getNumerator();
        Integer rhsWorkingNumerator = (rhsCopy.getWhole() * rhsCopy.getDenominator()) + rhsCopy.getNumerator();
        lhsWorkingNumerator *= rhsCopy.getDenominator();
        rhsWorkingNumerator *= lhsCopy.getDenominator();
        if (lhsWorkingNumerator > rhsWorkingNumerator) return true;
        return false;
	}

    /**
    * Function for less or equal to comparison
    * Equivalent to q <= r;
    */
	bool operator<=(const Rational& lhs, const Rational& rhs) {
        // If the lhs is not greater than, it is equal or smaller to.
        if (!(lhs > rhs)) return true;
		return false;
	}

    /**
    * Function for greater or equal to comparison
    * Equivalent to q >= r;
    */
	bool operator>=(const Rational& lhs, const Rational& rhs) {
        // If the lhs input is smaller, it is not greater or equal to.
        if (lhs < rhs) return false;
		return true;
	}

    /**
    * Function for equal comparison
    * Equivalent to q == r;
    */
	bool operator==(const Rational& lhs, const Rational& rhs) {
        // Copy the inputs.
        Rational lhsCopy = Rational(lhs);
        Rational rhsCopy = Rational(rhs);
        // If the Rationals equal 0, set their sign to positive.
        if (isZeroed(lhsCopy)) lhsCopy.setSign(true);
        if (isZeroed(rhsCopy)) rhsCopy.setSign(true);
        // If the signs are not the same, return false.
        if (lhsCopy.getSign() != rhsCopy.getSign()) return false;
        // Transform the inputs into fractions.
        Integer lhsCopyWorkingNumerator = (lhsCopy.getWhole() * lhsCopy.getDenominator()) + lhsCopy.getNumerator();
        Integer rhsCopyWorkingNumerator = (rhsCopy.getWhole() * rhsCopy.getDenominator()) + rhsCopy.getNumerator();
        lhsCopyWorkingNumerator *= rhsCopy.getDenominator();
        rhsCopyWorkingNumerator *= lhsCopy.getDenominator();
        // Compare them.
        if (lhsCopyWorkingNumerator == rhsCopyWorkingNumerator) return true;
        return false;
    }

    /**
    * Function for does not equal comparison
    * Equivalent to q != r;
    */
	bool operator!=(const Rational& lhs, const Rational& rhs) {
        // If input are equal, they are not not-equal.
        if (lhs == rhs) return false;
		return true;
	}

}
