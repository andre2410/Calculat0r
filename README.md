# Calculat0r

By Andrew Goh

## About
Anyone can make a calculator app with code by just following any tutorial online. However, they all have a limit on the size of the value being calculated.

If the calculator uses ints to calculate, it will run into overflow errors once a value bigger than max_int is used.

This calculator does not have that problem.

Not only can this calculator can compute whole numbers of any size, it also can calculate fractions and rational numbers of any size.

The code was based on a given task from my Univeristy course and I feel proud to share it and put it to use. I made it with Josh Argyle (lizzidthelich@gmail.com)

## Usage
GUI needs to be made!

### Instructions to run program with main.cpp
Download files from repository. Make sure you have a C/C++ compiler like gnu installed prior to running.
Open the folder in your favourite IDE as you have to input your usage in main.cpp.

If you are using Visual Studio and you have cmake installed, it will automatically compile and you can use the Rational class following
the usage above. By running RationalThinking.exe, Visual Studio will automatically compile and open a terminal where everything
printed to stdout can be seen.

If you are using any other IDE or on MACOS that is not using Visual Studio, that is rather unfortunate.
You will have to compile it in the terminal from your IDE (easiest way).
Open a new terminal in your IDE and make sure the directory in the IDE is set to the folder from the repository.

Compile EACH class using the following commands: 
1. g++ -W -c Integer.cpp -o Integer.o <br>
2. g++ -W -c Rational.cpp -o Rational.o <br>
3. g++ -W  main.cpp Integer.o Rational.o -o main <br>

Run the program using: .\main

Once running, everything that is printed to stdout can be seen in the terminal

If any changes are made to any file, please run commands again starting from the command in 1.

### About Rational class 
The Rational class stores fraction values using 3 separate Integers. The Integers are defined in the Integer class.
The Rational class uses them to represent a fraction's parts as whole number, numerator and denominator.

The Rational class can be initialised with 6 different constructors:
- Rational(): stores value as 0.
- Rational(string str): takes string and stores value accordingly. See note below.
- Rational(Integer a): takes value of Integer and stores it into the whole number value.
- Rational(Integer a, Integer b): stores *a* as numerator and *b* as denominator
- Rational(Integer a, Integer b, Integer c): stores *a* as whole number, *b* as numerator, *c* as denominator

*Regarding the constructor that takes a string, the string must follow the format stated below:
- Just whole number: Input string with just a whole number e.g "12" or "240".
- Fraction: Input string with numerator and denominator separated by '/' without a space in between. e.g "1/4" or "3/8".
- Mixed number: Input string with whole number then '.' then fraction. e.g "1.1/4" or "5.3/8".

Once initialised, the Rational instance can be use operators to calculate using another Rational instance.

A brief summary of supported operations, where q and r are both initialised Rationals:
- q = r: sets q to the value of r.
- +q: sets q to positive.
- -q: sets q to negative.
- q += r: adds r to q.
- q -= r: subtracts r from q.
- q *= r: multiplies q with r.
- q /= r: divides q by r.
- q + r: same as q += r but does not set q to q + r.
- q - r: same as q -= r but does not set q to q - r.
- q * r: same as q *= r but does not set q to q * r.
- q / r: same as q /= r but does not set q to q / r.
- q > r: returns true if q is greater than r, false otherwise.
- q < r: returns true if q is smaller than r, false otherwise.
- q <= r: returns true if q is smaller or equal to r, false otherwise.
- q >= r: returns true if q is greater or equal to r, false otherwise.
- q == r: returns true if q is equal to r, false otherwise.
- q != r: returns true if q is not equal to r, false otherwise.

C++ ostream and istream operators are overloaded too, so value of Rational can be printed using (cout << q;) and Rational 
can be set using (cin >> q) where the input from stdin must follow the string format mentioned earlier.




