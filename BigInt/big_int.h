#ifndef BIGINT_H
#define BIGINT_H

// C++ Libraries
#include <vector>
#include <iostream>

//Insert class definition
 
class BigInt {

public:
	
	// Default constructor creates big integer 0
	BigInt();
	// Constructor creates big integer from integer given
	BigInt(int val);
	// Destructor 
	// Might not need this
	//~BigInt();
	
	// Returns the number of digits in the big integer
	unsigned int size() const;

	// Overload operators for arithmetic operations

	// Adds big integers together
	BigInt operator +(const BigInt& num);
	// Returns true if 
	// bool operator <(const BigInt &num);
	// Returns false if 
	// bool operator >(const BigInt &num);

	// Overload I/O operators
	friend std::istream& operator >>(std::istream& in, const BigInt& num);
	friend std::ostream& operator <<(std::ostream& out, const BigInt& num);

private:
	// Represention of big integer as a vector of numbers
	std::vector<int> data_;
	// Current number of digits in big integer
	unsigned int size_;
	// True if big integer is negative
	bool signed_;
	//BigInt max (const BigInt &num, const BigInt &num);
};
 
#endif // BIGINT_H
