#include "big_int.h"

#include <iostream>

// Need to add error checking
// Use try and catch for error handling
// have different cases for errors
// try conversion to string to input into array

BigInt::BigInt() {
  size_ = 0;
  signed_ = false;
}

BigInt::BigInt(int val) {
  int temp = val;
  size_ = 0;

  if (val < 0) {
    signed_ = true;
    temp *= -1;
  } else {
    signed_ = false;
  }
  do {
    data_.push_back((char)temp % 10);
    size_++;
    temp = temp / 10;
  } while (temp != 0);

  // std::cout << "Just created : " << val << std::endl;
  // std::cout << "Signed is : " << signed_ << std::endl;
}

BigInt::BigInt() {

}

BigInt::~BigInt() { data_.clear(); }

BigInt::BigInt(const BigInt& source) {
  this->size_ = source.size_;
  this->signed_ = source.signed_;
  this->data_ = source.data_;
}

// Operation to get size
unsigned int BigInt::size() const { return size_; }

// Assignment Operation
BigInt BigInt::operator=(const BigInt& rhs) {
  if (this == &rhs) return *this;

  this->size_ = rhs.size_;
  this->signed_ = rhs.signed_;
  this->data_ = rhs.data_;

  return *this;
}

BigInt BigInt::operator=(const int& rhs) {
  int temp = rhs;
  size_ = 0;

  if (rhs < 0) {
    signed_ = true;
  } else {
    signed_ = false;
  }

  while (temp != 0) {
    data_.push_back(temp % 10);
    size_++;
    temp = temp / 10;
  }

  return *this;
}

// Addition operation
BigInt BigInt::operator+(const BigInt& rhs) const {
  if (rhs.size_ == 0 || this->size_ == 0) {
    std::cerr << "Empty big integer has been passed" << std::endl;
    exit(EXIT_FAILURE);
  }

  if (rhs.signed_ && !this->signed_) {
    return (*this) - rhs;
  } else if (this->signed_ && !rhs.signed_) {
    // std::cout << "doing rhs - this" << std::endl;
    return rhs - switch_sign(*this);
  }

  BigInt temp;
  std::vector<int> addend1 = this->data_;
  std::vector<int> addend2 = rhs.data_;
  int sum, carry = 0, n = std::max(this->size_, rhs.size_);

  for (int i = 0; i < n; i++) {
    if (addend1.size() < i + 1) {
      sum = addend2[i] + carry;
    } else if (addend2.size() < i + 1) {
      sum = addend1[i] + carry;
    } else {
      sum = addend1[i] + addend2[i] + carry;
    }
    carry = sum / 10;
    sum = sum % 10;

    temp.data_.push_back(sum);
    temp.size_++;
  }

  if (carry != 0) {
    temp.data_.push_back(carry);
    temp.size_++;
  }

  if (this->signed_ && rhs.signed_) {
    temp.signed_ = true;
  }

  return temp;
}

// Subtraction operation
BigInt BigInt::operator-(const BigInt& rhs) const {
  if (rhs.size_ == 0 || this->size_ == 0) {
    std::cerr << "Empty big integer has been passed" << std::endl;
    exit(EXIT_FAILURE);
  }

  if (rhs == *this) {
    return BigInt(0);
  }  // need to do this much better

  if (rhs > *this) {
    return switch_sign(rhs - (*this));
  }

  if (rhs.signed_ && !this->signed_) {
    return *this + switch_sign(rhs);
  } else if (this->signed_ && !rhs.signed_) {
    return rhs + switch_sign(*this);
  }

  BigInt temp;
  std::vector<int> minuend = this->data_;
  std::vector<int> subtrahend = rhs.data_;
  int diff, borrow = 0, n = std::max(this->size_, rhs.size_);

  for (int i = 0; i < n; i++) {
    if (subtrahend.size() < i + 1) {
      // std::cout << minuend[i] << '-' << borrow << std::endl;
      diff = minuend[i] - borrow;
    } else {
      // std::cout << minuend[i] << '-' << subtrahend[i] << '-' << borrow
      // << std::endl;
      diff = minuend[i] - subtrahend[i] - borrow;
    }

    if (diff < 0) {
      diff += 10;
      borrow = 1;
    } else {
      borrow = 0;
    }

    temp.data_.push_back(diff);
    temp.size_++;
  }

  // Need to do this more efficiently
  for (int i = temp.size_ - 1; i >= 0; i--) {
    // std::cout<<temp<<std::endl;
    if (temp.data_[i] == 0) {
      temp.data_.pop_back();
      temp.size_--;
    } else {
      break;
    }
  }

  return temp;
}

BigInt BigInt::operator+=(const BigInt& rhs) {
  // std::cout << "adding em up big!!!" << std::endl;
  *this = *this + rhs;
  return *this;
}


BigInt BigInt::operator-=(const BigInt& rhs) {
  // std::cout << "subtracting em up big!!!" << std::endl;
  *this = *this - rhs;
  return *this;
}

// Equal to operation
bool BigInt::operator==(const BigInt& rhs) const {
  if (this->size_ != rhs.size_) return false;

  if (this->signed_ != rhs.signed_) return false;

  for (int i = 0; i < rhs.size_; i++) {
    if (this->data_[i] != rhs.data_[i]) return false;
  }
  return true;
}

// Less than or equal to operation
bool BigInt::operator<=(const BigInt& rhs) const {
  return (*this) < rhs || (*this) == rhs;
}

// Greater than or equal to operation
bool BigInt::operator>=(const BigInt& rhs) const {
  return (*this) > rhs || (*this) == rhs;
}

// Not equal to operation
bool BigInt::operator!=(const BigInt& rhs) const {
  return !((*this) == rhs);
}

// Greater than operation
bool BigInt::operator>(const BigInt& rhs) const {
  // std::cout << "comparing " << *this << " > " << rhs << std::endl;
  if (this->signed_ == true && rhs.signed_ == false) {
    // std::cout<<"Comparing negative to positive"<<std::endl;
    return false;
  } else if (this->signed_ == false && rhs.signed_ == true) {
    // std::cout<<"Comparing positive to negative"<<std::endl;
    return true;
  } else if (this->signed_ == true && rhs.signed_ == true) {
    return switch_sign(rhs) > switch_sign(*this);
  }

  if (this->size_ > rhs.size_) {
    return true;
  } else if (this->size_ < rhs.size_) {
    return false;
  }

  for (int i = this->size_ - 1; i >= 0; i--) {
    if (this->data_[i] > rhs.data_[i]) {
      return true;
    } else if (this->data_[i] < rhs.data_[i]) {
      return false;
    }
  }

  return false;
}

// Less than operation
bool BigInt::operator<(const BigInt& rhs) const {
  // std::cout << "comparing " << *this << " < " << rhs << std::endl;
  return rhs > *this;
}

// Function to take in the number via stream
std::istream& operator>>(std::istream& in, BigInt& rhs) {
  int temp;
  in >> temp;
  rhs = temp;
  return in;
}

// Function to print out the number via stream
std::ostream& operator<<(std::ostream& out, const BigInt& rhs) {
  if (rhs.size_ == 0) {
    std::cerr << "Empty big integer has been passed" << std::endl;
    exit(EXIT_FAILURE);
  }
  if (rhs.signed_) out << '-';

  for (int i = rhs.size_ - 1; i >= 0; i--) {
    out << rhs.data_[i];
  }

  return out;
}  // try converting to string

// Helper function to change a number from positive to negative
BigInt BigInt::switch_sign(BigInt value) const {
  BigInt temp = value;
  temp.signed_ = !temp.signed_;
  return temp;
}
