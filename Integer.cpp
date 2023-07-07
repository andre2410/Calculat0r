#include "Integer.h"

/**
 *      Cosc326 Etude 8: Rationals. Written May 2023.
 *      This is our solution to the Rationals etude.
 *      @author Andrew Goh
 *      @author Josh Argyle
 */

/**
*Functions for Integer class
*/

namespace cosc326 {
	/*
	* Default constructor that creates Integer with a value of 0
	*/
	Integer::Integer() {
		//Set value to zero
		this->value = { '0' };
	}

    /*
    * Constructor that initializes Integer with the provided vector
	* DOES NOT SET SIGN
    */
    Integer::Integer(const vector<char>& initialValue) {
        this->value = initialValue;
    }

	/*
	 *
	* Constructor that duplicates the provided Integer
	* Assumes Integer is valid
	*/
	Integer::Integer(const Integer& i) {
		//Set value to Integer i value
		this->value = i.value;
		this->sign = i.getSign();
	}

	/*
	* Constructor that takes string
	*/
	Integer::Integer(const string& s) {
		//Clear value just in case
		this->value.clear();
		//Loop through string 
		for (int i = 0; i < s.length(); i++) {
			//Check for sign
			if (i == 0) {
				if (s[i] == '+') {//Continue loop as sign is default true
					continue;
				}
				if (s[i] == '-') {//Set sign to false
					this->setSign(false);
					continue;
				}
			}
			//Check for troll input
			if (isdigit(s[i]) == false) {
				cout << "Input is non numeric!" << endl;
				this->value.clear();
				return;
			}
			//Append to value if its not
			this->value.push_back(s[i]);
		}
        Integer zero = Integer();
        if (this->getValue() == zero.getValue()) this->setSign(true);
	}

	/*
	* Destructor for Integer
	*/
	Integer::~Integer() {
	}

	/**
	* Accessor for local variable sign
	*/
    bool Integer::getSign() const {
        return this->sign;
    }

	/**
	* Mutator for local variable sign
	*/
    void Integer::setSign(bool sign) {
        this->sign = sign;
    }

	/**
	* Accessor for local variable value
	*/
	vector<char> Integer::getValue() const {
		return this->value;
	}

	/**
	* Mutator for local variable value
	*/
	void Integer::setValue(const string& s) {
		//empty value vector
        if (s == "0") {
            this->sign = true;
        }
		this->value.clear();
		//Loop through string 
		for (int i = 0; i < s.length(); i++) {
			this->value.push_back(s[i]);
		}
	}

	/**
	* Function to set Integer value to Integer i value
	*/
	Integer& Integer::operator=(const Integer& i) {
		//Get value
		vector<char> v = i.getValue();
		//Assign value to this.value
		this->value = v;
        this->sign = i.getSign();
		return *this;
	}

	/**
	* Function to set value of Integer to negative
	*/
	Integer Integer::operator-() {
		this->setSign(false);
		return Integer(*this);
	}

	/**
	* Function to set value of Integer to positive
	*/
	Integer Integer::operator+() {
		this->setSign(true);
		return Integer(*this);
	}

	/**
	* Function for addition
	* Equivalent to y = y + x;
	*/
	Integer& Integer::operator+=(const Integer& i) {
        //Variables needed
        int carry = 0;
        //Temp storage for comparing
        Integer temp = Integer(this->getValue());
        temp.setSign(this->getSign());
        // For -lhs and +rhs
        // -5 + 10 is the same as 10 - 5, but we need to make sure the signs are ok.
        if (!this->getSign() && i.getSign()) {
            Integer posLHS = Integer(this->value);
            posLHS.setSign(true);
            Integer result = i - posLHS;
            this->value = result.getValue();
            this->setSign(result.getSign());
            return *this;
        // For +lhs and -rhs
        // 5 + -10 is the same as 5 - 10
        } else if (this->getSign() && !i.getSign()) {
            Integer posRHS = Integer(i.value);
			posRHS.setSign(true);
            Integer workingLeft = Integer(this->getValue());
            Integer result = workingLeft - posRHS;
            this->value = result.getValue();
            this->setSign(result.getSign());
            return *this;
		}
		//Vectors for calculation
		vector<char> y = this->getValue();
		vector<char> x = i.getValue();
		vector<char> result;
		// For each digit in the input integers, add them.
		while (!y.empty() && !x.empty()) {
			int a = y.back() - '0';
			int b = x.back() - '0';
			int addition = (a + b + carry);
			// If the value is greater than or equal to 10, we have a carry.
			if (addition >= 10) {
				carry = 1;
			}
			else {
				carry = 0;
			}
			addition = addition % 10;
			result.insert(result.begin(), addition + '0');
			// Remove the last two values.
			y.pop_back();
			x.pop_back();
		}
		// If there are numbers left in y.
		while (!y.empty()) {
			int addition = ((y.back() - '0') + carry);
			// If the value is greater than or equal to 10, we have a carry.
			if (addition >= 10) {
				carry = 1;
			}
			else {
				carry = 0;
			}
			addition = addition % 10;
			result.insert(result.begin(), addition + '0');
			// Remove the last two values.
			y.pop_back();
		}
		// If there are numbers left in x.
		while (!x.empty()) {
			int addition = ((x.back() - '0') + carry);
			// If the value is greater than or equal to 10, we have a carry.
			if (addition >= 10) {
				carry = 1;
			}
			else {
				carry = 0;
			}
			addition = addition % 10;
			result.insert(result.begin(), addition + '0');
			// Remove the last two values.
			x.pop_back();
		}
		// If there's still a carry after the addition, insert it at the beginning.
		if (carry == 1) {
			result.insert(result.begin(), carry + '0');
		}
		//Check signs, if both are negative, result is negative
		if (!this->getSign() && !i.getSign()) {
			this->setSign(false);
		}
		//Set value to result vector and return
		this->value = result;
		return *this;
	}

	/**
	* Function for subtraction
	* Equivalent to y = y - x;
	*/
	Integer& Integer::operator-=(const Integer& i) {
        Integer zero = Integer();
        //Initialise Integer copies
        Integer lhs = Integer(this->getValue());
        lhs.setSign(this->getSign());
        Integer rhs = Integer(i.getValue());
        rhs.setSign(i.getSign());
        if (lhs.getValue() == zero.getValue()) lhs.setSign(true);
        if (rhs.getValue() == zero.getValue()) rhs.setSign(true);
        if (lhs == rhs) {
            this->value = { '0' };
            this->sign = 1;
            return *this;
        }
        // If only left side is negative.
        // rhs += the positive version of lhs, switch sign.
        if (!this->sign && i.sign) {
            lhs.setSign(true); // Just in case, reset it to a positive number.
            Integer result = i + lhs;
            this->value = result.getValue();
            this->setSign(false);
            return *this;
        }
        // If only right side is negative.
        // lhs -= positive version of rhs.
        if (this->sign && !i.sign) {
            rhs.setSign(true);
            Integer result = i - rhs;
            this->value = result.getValue();
            this->setSign(result.sign);
            return *this;
        }
        // If both values are negatives.
        if (!this->sign && !i.sign) {
            lhs.setSign(true);
            rhs.setSign(true);
            Integer result = lhs - rhs;
            this->value = result.getValue();
            this->sign = false;
            return *this;
        }
        // If both are negative, it is dealt with at end of method.
        // If neither are, then it is all good.
        // Flag to check if the rhs is a bigger number, ie we will end up with a negative result.
        // If is it bigger, we flip the operands and negate the result. This is for 2 positive numbers.
        bool sizeFlag = lhs < rhs;
        vector<char> leftHand = (sizeFlag ? rhs.getValue() : lhs.getValue()); // Set the greater value to the lhs.
        vector<char> rightHand = (sizeFlag ? lhs.getValue() : rhs.getValue());// Set the lesser value to the rhs.
        vector<int> result;
        // Store the carry.
        int carry = 0;
        // Do this the same as the addition method, with while loops.
        while (!leftHand.empty() && !rightHand.empty()) {
            int subtraction = (10 + (leftHand.back() - '0') - (rightHand.back() - '0') - carry);
            result.insert(result.begin(), (subtraction % 10));
            leftHand.pop_back();
            rightHand.pop_back();
            if (subtraction < 10) {
                carry = 1;
            } else {
                carry = 0;
            }
        }
        // Do this the same as the addition method, with while loops.
        while (!leftHand.empty()) {
            int subtraction = (10 + (leftHand.back() - '0') - carry);
            result.insert(result.begin(), (subtraction % 10));
            leftHand.pop_back();
            if (subtraction < 10) {
                carry = 1;
            } else {
                carry = 0;
            }
        }
        // Do this the same as the addition method, with while loops.
        while (!rightHand.empty()) {
            int subtraction = (10 + (rightHand.back() - '0')- carry);
            result.insert(result.begin(), ((subtraction % 10) ));
            rightHand.pop_back();
            if (subtraction < 10) {
                carry = 1;
            } else {
                carry = 0;
            }
        }
        // Make vector<char> from result.
        vector<char> charVector;
        for (int num : result) {
            char val = num + '0';
            charVector.push_back(val);
        }
        // Create and return a new Integer object with the result.
        Integer resultInteger(charVector);
        if (sizeFlag) {
            resultInteger.setSign(false);
        }
        resultInteger = stripZeros(resultInteger);

        this->value = resultInteger.getValue();
        this->sign = resultInteger.getSign();
        return *this;
	}

	/**
	* Function for multiplication
	* Equivalent to y = y*x;
	*/
	Integer& Integer::operator*=(const Integer& i) {
		//Variables for calculation
		vector<char> y = this->getValue();
		vector<char> x = i.getValue();
		vector<char> result;
		int carry = 0;
		//Store value
		Integer temp = Integer();
		Integer temp2 = Integer();
		//Compare lengths and sort
		if (x.size() > y.size()) {
			y = i.getValue();
			x = this->getValue();
		}
		//Get y size
		int ysize = y.size() - 1;
		//Loop through 
		for (int j = x.size() - 1; j >= 0; j--) {
			int a = x[j] - '0';
			carry = 0;
			if (j != x.size() - 1) {
				for (int c = 0; c < (x.size() - 1) - j; c++) {
					result.insert(result.begin(), carry + '0');
				}
			}
			for (int k = ysize; k >= 0; k--) {
				//Multiply each value and append it to result vector
				int b = y[k] - '0';
				int multiply = (a * b) + carry;
				if (multiply >= 10 && k != 0) {// If multiply is above 10, need to carry over
					int final = multiply % 10;
					result.insert(result.begin(), final + '0');
					//Calculate value of carry
					carry = (multiply - final) / 10;
				}
				else if (multiply >= 10 && k == 0) {//If multiply is above 10, need to append whole value to result
					int final = multiply % 10;
					//Insert second last int
					result.insert(result.begin(), final + '0');
					//Process and insert final value
					int last = (multiply - final) / 10;
					result.insert(result.begin(), last + '0');
					carry = 0;
				}
				else {
					result.insert(result.begin(), multiply + '0');
					carry = 0;
				}
			}
			//Account for carry over
			if (carry == 1) {
				result.insert(result.begin(), carry + '0');
			}
			string str(result.begin(), result.end());
			temp2.setValue(str);
			temp += temp2;
			//cout << temp;
			result.clear();
		}
		//Set current value to temp.value
		vector<char>multiplied = temp.getValue();
		string str2(multiplied.begin(), multiplied.end());
        // If both inputs are positive or negative, the sign is positive. Otherwise, it is false.
        if ((this->sign && i.getSign()) || (!this->sign && !i.getSign())) {
            this->setSign(true);
        } else {
            this->setSign(false);
        }
		this->setValue(str2);
		return *this;
	}

	/**
	* Function for division using divide and conquer
	* Equivalent to y = y/x;
	*/
	Integer& Integer::operator/=(const Integer& i) {
        if (i == Integer("1")) return *this;
        // Get copies of  the two values we are working with.
        Integer leftHand = Integer(this->getValue());
        Integer rightHand = Integer(i.getValue());
        // If both inputs are positive or negative, the sign is positive. Otherwise, it is false.
        if ((this->sign && i.getSign()) || (!this->sign && !i.getSign())) {
            this->setSign(true);
        } else {
            this->setSign(false);
        }
        // If the divisor is 0, return the dividee.
        if (rightHand == Integer()) {
            this->value = leftHand.value;
        }
        Integer low = Integer("0");
        Integer high = Integer(leftHand.value);
        Integer mid = Integer((high - low).value);
        mid = splitInHalf(mid);
        mid += low;
        //Loop until calculation finishes
        while (true) {
            // Strip leading zeros from all numbers.
            mid = stripZeros(mid);
            high = stripZeros(high);
            low = stripZeros(low);
            // If mid * input2 equals input1, return mid, as it is our divisor.
            if ((mid * rightHand) == leftHand) {
                this->value = mid.getValue();
                return *this;
            }
            // If low or high equal mid, return mid as it is as close as we will get.
            else if ((low == mid) || (high == mid)) {
                this->value = mid.getValue();
                return *this;
            }
            // If mid * input2 is greater than input1, set high as mid, and recalculate mid.
            else if ((rightHand * mid) > leftHand) {
                high = mid;
                mid = (high - low);
                mid = splitInHalf(mid);
                mid += low;
            }
            // If mid * input2 is smaller than input1, set low as mid, and recalculate mid.
            else if (leftHand > (rightHand * mid)) {
                low = mid;
                mid = (high - low);
                mid = splitInHalf(mid);
                mid += low;
            }
        }
	}

	/**
	* Function for modulus operator
	* Equivalent to y = y % x;
	*/
	Integer& Integer::operator%=(const Integer& i) {
		Integer leftHand = Integer(this->getValue());
        Integer rightHand = Integer(i.getValue());
        Integer c = leftHand / rightHand;
        Integer d = leftHand - (rightHand * c);
        this->value = d.getValue();
        return *this;
	}
	
    //Following operations uses the operations above for calculation
    //e.g + would call +=

	/**
	* Function for binary addition
	* Equivalent to y + x;
	*/
	Integer operator+(const Integer& lhs, const Integer& rhs) {
        Integer left = lhs.getValue();
        left.setSign(lhs.getSign());
        Integer right = rhs.getValue();
        right.setSign(rhs.getSign());
		return left += right;
	}

	/**
	* Function for binary subtraction
	* Equivalent to y - x;
	*/
	Integer operator-(const Integer& lhs, const Integer& rhs) {
        Integer left = lhs.getValue();
        left.setSign(lhs.getSign());
        Integer right = rhs.getValue();
        right.setSign(rhs.getSign());
        return left -= right;
    }
    
	/**
	* Function for binary multiplication
	* Equivalent to y * x;
	*/
	Integer operator*(const Integer& lhs, const Integer& rhs) {
        Integer left = lhs.getValue();
        left.setSign(lhs.getSign());
        Integer right = rhs.getValue();
        right.setSign(rhs.getSign());
        return left *= right;
	}

	/**
	* Function for binary division
	* Equivalent to y / x;
	*/
	Integer operator/(const Integer& lhs, const Integer& rhs) {
        Integer left = lhs.getValue();
        left.setSign(lhs.getSign());
        Integer right = rhs.getValue();
        right.setSign(rhs.getSign());
        return left /= right;
	}

	/**
	* Function for binary division
	* Equivalent to y % x;
	*/
	Integer operator%(const Integer& lhs, const Integer& rhs) {
        Integer left = lhs.getValue();
        left.setSign(lhs.getSign());
        Integer right = rhs.getValue();
        right.setSign(rhs.getSign());
        return left %= right;
	}

	//Functions for printing options.

    /**
    * Overloading ostream operator for Integer class
    */
    std::ostream& operator<<(std::ostream& os, const Integer& i) {
        //Create string
        vector<char> v = i.getValue();
        string o(v.begin(), v.end());
        //Return o string
        if (!i.getSign()) { // This prints the - sign before the number if it is a negative.
            os << '-';
        }
        os << o << std::endl;
        return os;
    }

	/**
	* Overloading istream operator for Integer class
	*/
	std::istream& operator>>(std::istream& is, Integer& i) {
		string s;
		is >> s;
		//Set variable
		i.setValue(s);
		return is;
	}

    //Functions for comparing 2 integer classes

	/**
	* Function for less than comparison
	* Equivalent to y < x;
	*/
    bool operator<(const Integer& lhs, const Integer& rhs) {
        if (lhs != rhs && !(lhs > rhs)) return true;
        return false;
    }

	/**
	* Function for greater than comparison
	* Equivalent to y > x;
	*/
    bool operator> (const Integer& lhs, const Integer& rhs) {
        //Set up copis of lhs and rhs
        Integer strippedLHS = Integer(lhs);
        strippedLHS = stripZeros(strippedLHS);
        Integer strippedRHS = Integer(rhs);
        strippedRHS = stripZeros(strippedRHS);
        Integer zero = Integer();
        if (strippedLHS.getValue() == zero.getValue()) strippedLHS.setSign(true);
        if (strippedRHS.getValue() == zero.getValue()) strippedRHS.setSign(true);
        vector<char> leftHand = strippedLHS.getValue();
        vector<char> rightHand = strippedRHS.getValue();
        // If they values are both negatives, the smaller one is the greater number.
        // -15 > -5 should be false.
        if (!lhs.getSign() && !rhs.getSign()) {
            Integer posLHS = Integer(leftHand);
            Integer posRHS = Integer(rightHand);
            if (posLHS > posRHS) return false;
            return true;
        }
        // If the number is a negative and other is a positive, it is not bigger.
        if (!lhs.getSign() && rhs.getSign()) return false;
        //get longer and shorter
        int shorter = std::min(leftHand.size(), rightHand.size());
        int longer = std::max(leftHand.size(), rightHand.size());
        // If both are the same length.
        if (shorter == longer) {
            // For every int value in the two numbers.
            for (int i = 0; i < leftHand.size(); i++) {
                // If the leftHand's value is smaller, return false.
                if (leftHand[i] < rightHand[i]) return false;
                    // If the leftHand's value is larger, return true.
                else if (leftHand[i] > rightHand[i]) return true;
            }
        }
        // If left is longer
        if (leftHand.size() > rightHand.size()) {
            // For all of the values that the right hand side doesn't have, if they are not a leading
            // 0 return true.
            for (int i = 0; i < longer - shorter; i++) {
                if (leftHand[i] > 0) return true;
            }
            // For the rest of the values
            for (int i = 0; i < shorter; i++) {
                // If the leftHand's value is smaller, return false.
                if (leftHand[i + shorter - 1] < rightHand[i]) return false;
                    // If the leftHand's value is larger, return true.
                else if (leftHand[i + shorter - 1] > rightHand[i]) return true;
            }
        }
        // If right is longer
        if (rightHand.size() > leftHand.size()) {
            // For all of the values that the right hand side doesn't have, if they are not a leading
            // 0 return false.
            for (int i = 0; i < longer - shorter; i++) {
                if (rightHand[i] > 0) return false;
            }
            // For the rest of the values
            for (int i = 0; i < shorter; i++) {
                // If the leftHand's value is smaller, return false.
                if (rightHand[i + shorter - 1] < leftHand[i]) return true;
                    // If the leftHand's value is larger, return true.
                else if (rightHand[i + shorter - 1] > leftHand[i]) return false;
            }
        }
        // If the values are the same, one is not larger than the other so return false.
        return false;
    }

	/**
	* Function for less or equal to comparison
	* Equivalent to y <= x;
	*/
    bool operator<=(const Integer& lhs, const Integer& rhs) {
        if (!(lhs > rhs)) return true;
        return false;
    }

	/**
	* Function for greater or equal to comparison
	* Equivalent to y >= x;
	*/
    bool operator>=(const Integer& lhs, const Integer& rhs) {
        if (!(lhs < rhs)) return true;
        return false;
    }

	/**
	* Function for equal comparison
	* Equivalent to y == x;
	*/
    bool operator==(const Integer& lhs, const Integer& rhs) {
        //Set up copies of lhs and rhs
        Integer strippedLHS = Integer(lhs);
        strippedLHS = stripZeros(strippedLHS);
        Integer strippedRHS = Integer(rhs);
        strippedRHS = stripZeros(strippedRHS);
        Integer zero = Integer();
        if (strippedLHS.getValue() == zero.getValue()) strippedLHS.setSign(true);
        if (strippedRHS.getValue() == zero.getValue()) strippedRHS.setSign(true);
        vector<char> leftHand = strippedLHS.getValue();
        vector<char> rightHand = strippedRHS.getValue();
        //Compare both Integers
        if (leftHand == rightHand && strippedLHS.getSign() == strippedRHS.getSign()) return true;
        return false;
    }

	/**
	* Function for does not equal comparison
	* Equivalent to y != x;
	*/
    bool operator!=(const Integer& lhs, const Integer& rhs) {
        if (lhs == rhs) return false;
        return true;
    }

	/**
	* Function for greatest common divisor
	* Equivalent to z = gcd(y,x);
	*/
	Integer gcd(const Integer& a, const Integer& b) {
        //Set up copies of a and b
        Integer x = Integer(a);
        Integer y = Integer(b);
        //Check if either is 0
        if (y == Integer() && x != Integer()) return x;
        if (x == Integer() && y != Integer()) return y;
        //set signs to positive for calculation, because negatives will still have positive gcd
        x.setSign(true);
        y.setSign(true);
        //Calculate gcd
        while (y != Integer()) {
            Integer remainder = x % y;
            x = y;
            y = remainder;
        }
        return x;
	}

    //Helper functions

    /**
    * Function to split Integer value in half, used for divide operator
    * Divides the number by 2, rounding down.
    */
    Integer splitInHalf(const Integer& lhs) {
        int flag = 0;
        vector<char> values = lhs.getValue();
        vector<int> intVal;
        for (char c : values) {
            intVal.insert(intVal.end(), c - '0');
        }
        vector<int> result;
        for (int i = 0; i < intVal.size(); i++) {
            // If the number is even.
            if (intVal[i] % 2 == 0) {
                intVal[i] = (intVal[i] / 2) + flag;
                flag = 0;
                // If the number is odd
            } else {
                intVal[i] -= 1;
                intVal[i] = (intVal[i] / 2) + flag;
                flag = 5;
            }
        }
        vector<char> resultVector;
        for (int i : intVal) {
            resultVector.insert(resultVector.end(), i + '0');
        }
        Integer resInteger = Integer(resultVector);
        return resInteger;
    }

    /**
    * Function to strip leading zeros for calculation
    */
    Integer stripZeros(const Integer& lhs) {
        vector<char> vals = lhs.getValue();
        while (vals.size() > 1 && vals[0] == (0 + '0')) {
            vals.erase(vals.begin());
        }
        Integer stripped = Integer(vals);
        return stripped;
    }
}

