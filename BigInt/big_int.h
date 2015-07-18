#ifndef BIGINT_H
#define BIGINT_H

// C++ Libraries
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

//Insert class definition
 
class BigInt
{
	
public:
	
	// Default constructor creates big integer 0
	BigInt();
	// Constructor creates big integer from integer given
	BigInt(int num);
	// Destructor 
	// Might not need this
	//~BigInt();
	
	// Returns the number of digits in the big integer
	unsigned int size() const;

	// Overload operators for arithmetic operations

	// Adds big integers together
	BigInt operator +(BigInt num);

	// Overload I/O operators
	friend std::istream& operator>> (std::istream& in, BigInt& num);
	friend std::ostream& operator<< (std::ostream& out, const BigInt& num);
	


private:
	// Represention of big integer as a vector of numbers
	std::vector<int> big_int_;

	// Current number of digits in big integer
	unsigned int size_;

	// Returns whether or not integer is signed
	bool signature() const;
};
 
#endif
