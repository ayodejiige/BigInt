#include "big_int.h"
#include <iostream>

// Needs to follow google style standards
// Need to add error checking

BigInt::BigInt() {
	size_ = 0;
	signed_ = false;
}

BigInt::BigInt(int val) {
	int temp = val;
    size_ = 0;

    //std::cout<<"Converting " << val << " to big integer " << std::endl;
	while (temp!=0) {
        //std::cout<<"adding " << temp%10 << std::endl;

		data_.push_back(temp%10);
		size_++;
		temp = temp/10;
	}

	if (val<0) {
		signed_=true;
	}
	else {
		signed_=false;
	}

    int i;

    //std::cout << "Just added : ";
    for (i = size_-1; i>=0; i--) {
        //std::cout << data_[i];
    }

    //std::cout << std::endl;

}

unsigned int BigInt::size() const {
	return size_;
}


BigInt BigInt::operator +(const BigInt& num) {

	BigInt temp;
	std::vector<int> temp_digits;

	int carry = 0, sum;
	std::vector<int> addend1 = this->data_;
	std::vector<int> addend2 = num.data_;

	int n = std::max(this->size_, num.size_);
    //std::cout << "Adding, n is " << n << std::endl;
	int i ;
	for (i=0; i<n; i++) {
		if (addend1.size()<i) {
			sum = addend2[i] + carry;
		}
		else if (addend2.size()<i) {
			sum = addend1[i] + carry;
		}

		else {
			sum = addend1[i] + addend2[i] + carry;
		}

		//std::cout << "Sum is " << sum << std::endl;
		carry = sum/10;
		sum = sum%10;
		temp.data_.push_back(sum);
		temp.size_++;
		//std::cout << "Sum is now " << sum << std::endl;
	}

	if (carry != 0) {
        temp_digits.push_back(carry);
        temp.size_ ++;
	}

   /*//std::cout << "Just added : ";

    for (i = temp.size_-1; i>=0; i--) {
        //std::cout << temp.data_[i];
    }*/
	return temp;
}

std::istream& operator>> (std::istream& in, const BigInt& num) {
	return in;
} //need to implement properly

std::ostream& operator<< (std::ostream& out, const BigInt& num) {
	int i;
	if (num.signed_) out << '-';

	for (i=num.size_-1; i>=0; i--) {
		out << num.data_[i];
	}

	return out;
} //try converting to string
