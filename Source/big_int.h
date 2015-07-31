#ifndef BIGINT_H
#define BIGINT_H

// C++ Libraries
#include <cstdlib>
#include <vector>
#include <iostream>

// Insert class definition

class BigInt {
 public:
  // Default constructor creates big integer 0
  BigInt();
  // Constructor creates big integer from integer given
  BigInt(int val);
  // Destructor
  ~BigInt();
  // Copy Constructor
  BigInt(const BigInt& source);

  // Returns the number of digits in the big integer
  unsigned int size() const;

  // Assignment operator
  BigInt operator=(const BigInt& rvalue);
  BigInt operator=(const int& rvalue);

  // Basic arithmetic operators
  BigInt operator+(const BigInt& rvalue) const;
  BigInt operator-(const BigInt& rvalue) const;
  // BigInt operator *(const BigInt& rvalue);
  // BigInt operator /(const BigInt& rvalue);
  // BigInt operator %(const BigInt& rvalue);

  BigInt operator+=(const BigInt& rvalue);
  BigInt operator-=(const BigInt& rvalue);
  // void operator *=(const BigInt& rvalue);
  // void operator /=(const BigInt& rvalue);

  // Boolean operators
  bool operator==(const BigInt& rvalue) const;
  bool operator!=(const BigInt& rvalue) const;
  bool operator<=(const BigInt& rvalue) const;
  bool operator>=(const BigInt& rvalue) const;
  bool operator<(const BigInt& rvalue) const;
  bool operator>(const BigInt& rvalue) const;

  // I/O operators
  friend std::istream& operator>>(std::istream& in, BigInt& rvalue);
  friend std::ostream& operator<<(std::ostream& out, const BigInt& rvalue);

 private:
  // Member variable

  // Represention of big integer as a vector of numbers
  std::vector<int> data_;
  // Current number of digits in big integer
  unsigned int size_;
  // True if big integer is negative
  bool signed_;
  // BigInt max (const BigInt &rvalue, const BigInt &rvalue);

  // Helper functions
  BigInt switch_sign(BigInt value) const;
};

#endif  // BIGINT_H
