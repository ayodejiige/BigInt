#include "big_int.h"

#include <vector>

typedef BigInt::DataType DataType;

BigInt::BigInt() {
	big_int_.push_back(0);
	size_ = 1;
	signed_ = false;
}

BigInt::BigInt(int val) {
	int temp = val;
	while (temp!=0) {
		big_int_.push_back(temp%10);
		temp = temp/10;
	}
}

BigInt::size() const {
	return size_;
}

BigInt BigInt::operator +(BigInt num) {
	
}

std::istream& operator>> (std::istream& in, BigInt& num) {

}

std::ostream& operator<< (std::ostream& out, const BigInt& num) {
	
}
