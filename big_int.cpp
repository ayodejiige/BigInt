#include "big_int.h"

#include <iostream>

// Needs to follow google style standards
// Need to add error checking
// Need to implement for negative rvaluebers
// Need to enable interaction with normal ints
// Need to add edge cases

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
  while (temp != 0) {
    data_.push_back(temp % 10);
    size_++;
    temp = temp / 10;
  }

  //std::cout << "Just created : " << val << std::endl;
  //std::cout << "Signed is : " << signed_ << std::endl;
}

BigInt::~BigInt() { data_.clear(); }

BigInt::BigInt(const BigInt& source) {
  this->size_ = source.size_;
  this->signed_ = source.signed_;
  this->data_ = source.data_;
}
unsigned int BigInt::size() const { return size_; }

BigInt BigInt::operator=(const BigInt& rvalue) {
  if (this == &rvalue) return *this;

  this->size_ = rvalue.size_;
  this->signed_ = rvalue.signed_;
  this->data_ = rvalue.data_;

  return *this;
}

BigInt BigInt::operator=(const int& rvalue) {
  int temp = rvalue;
  size_ = 0;

  if (rvalue < 0) {
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

BigInt BigInt::operator+(const BigInt& rvalue) const {
  if (rvalue.size_ == 0 || this->size_ == 0) {
    std::cerr << "Empty big integer has been passed" << std::endl;
    abort();
  }

  if (rvalue.signed_ && !this->signed_) {
    return (*this) - rvalue;
  } else if (this->signed_ && !rvalue.signed_) {
    // const BigInt copy = *this;
    // BigInt rval = rvalue;
    //std::cout << "doing rvalue - this" << std::endl;
    return rvalue - switch_sign(*this);
  }

  BigInt temp;
  std::vector<int> addend1 = this->data_;
  std::vector<int> addend2 = rvalue.data_;
  int sum, carry = 0, n = std::max(this->size_, rvalue.size_);

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

  if (this->signed_ && rvalue.signed_) {
    temp.signed_ = true;
  }

  return temp;
}

BigInt BigInt::operator-(const BigInt& rvalue) const {
  if (rvalue.size_ == 0 || this->size_ == 0) {
    std::cerr << "Empty big integer has been passed" << std::endl;
    return -1;
  }

  if (rvalue > *this) {
    return switch_sign(rvalue - (*this));
  }
  if (rvalue.signed_ && !this->signed_) {
    return *this + rvalue;
  } else if (this->signed_ && !rvalue.signed_) {
    return rvalue + switch_sign(*this);
  }

  BigInt temp;
  std::vector<int> minuend = this->data_;
  std::vector<int> subtrahend = rvalue.data_;
  int diff, borrow = 0, n = std::max(this->size_, rvalue.size_);

  for (int i = 0; i < n; i++) {
    if (subtrahend.size() < i + 1) {
      //std::cout << minuend[i] << '-' << borrow << std::endl;
      diff = minuend[i] - borrow;
    } else {
      //std::cout << minuend[i] << '-' << subtrahend[i] << '-' << borrow
      //          << std::endl;
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
  for (int i = temp.size_-1; i>=0; i--){
    //std::cout<<temp<<std::endl;
    if (temp.data_[i]==0){
      temp.data_.pop_back();
      temp.size_--;
    }
    else {
      break;
    }
  }

  return temp;
}

BigInt BigInt::operator+=(const BigInt& rvalue) {
  //std::cout << "adding em up big!!!" << std::endl;
  *this = *this + rvalue;
  return *this;
}

bool BigInt::operator==(const BigInt& rvalue) const {
  if (this->size_ != rvalue.size_) return false;

  if (this->signed_ != rvalue.signed_) return false;

  for (int i = 0; i < rvalue.size_; i++) {
    if (this->data_[i] != rvalue.data_[i]) return false;
  }
  return true;
}

bool BigInt::operator<=(const BigInt& rvalue) const {
  return (*this) < rvalue || (*this) == rvalue;
}

bool BigInt::operator>=(const BigInt& rvalue) const {
  return (*this) > rvalue || (*this) == rvalue;
}

bool BigInt::operator!=(const BigInt& rvalue) const {
  return !((*this) == rvalue);
}

bool BigInt::operator>(const BigInt& rvalue) const {
  //std::cout << "comparing " << *this << " > " << rvalue << std::endl;
  if (this->signed_ == true && rvalue.signed_ == false) {
    //std::cout<<"Comparing negative to positive"<<std::endl;
    return false;
  } else if (this->signed_ == false && rvalue.signed_ == true) {
    //std::cout<<"Comparing positive to negative"<<std::endl;
    return true;
  } else if (this->signed_ == true && rvalue.signed_ == true) {
    return switch_sign(rvalue) > switch_sign(*this);
  }

  if (this->size_ > rvalue.size_) {
    return true;
  } else if (this->size_ < rvalue.size_) {
    return false;
  }

  for (int i = this->size_ - 1; i >= 0; i--) {
    if (this->data_[i] > rvalue.data_[i]) {
      return true;
    } else if (this->data_[i] < rvalue.data_[i]) {
      return false;
    }
  }

  return false;
}

bool BigInt::operator<(const BigInt& rvalue) const {
  //std::cout << "comparing " << *this << " < " << rvalue << std::endl;
  return rvalue > *this;
}

std::istream& operator>>(std::istream& in, const BigInt& rvalue) {
  return in;
}  // need to implement properly

std::ostream& operator<<(std::ostream& out, const BigInt& rvalue) {
  if (rvalue.signed_) out << '-';

  for (int i = rvalue.size_ - 1; i >= 0; i--) {
    out << rvalue.data_[i];
  }

  return out;
}  // try converting to string

BigInt BigInt::switch_sign(BigInt value) const {
  BigInt temp = value;
  temp.signed_ = !temp.signed_;
  return temp;
}