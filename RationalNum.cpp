#include "RationalNum.h"

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <limits.h>
#include <assert.h>
using namespace std;

/**************************************************************/
//////////////////////////////////////////////////////////////
//helper functions
//////////////////////////////////////////////////////////////
/**************************************************************/

////////////////////////////////////////////////////
//function: absInt()--- to get absolute value
//input: x - signed integer
//output: absolute value of the signed integer
////////////////////////////////////////////////////
int absInt(int x) {
	if (x >= 0) {
		return x;
	}
	else {
		return -x;
	}
}

////////////////////////////////////////////////////
//function: getFactors()--- to get divide factor
//input: num - signed integer
//output: factorSet - int vector store the divide factors
////////////////////////////////////////////////////
void getFactors (int num, vector<int>& factorSet) {
	if (num != 1) {
		factorSet.push_back(num);
	}
	for (int i = 2; i <= sqrt( static_cast<double>(num) ); i++) {
		if (num%i == 0) {
			factorSet.push_back(i);
			factorSet.push_back(num/i);
		}
	}
}

////////////////////////////////////////////////////
//function: normalizeFun()---facility function for normalize
//input: a, b - signed integer
//output: a, b - normalized result
////////////////////////////////////////////////////
void normalizeFun(int& a, int& b) {
	int tempN = a;
	int tempD = b;
	int small, temp;
	vector<int> factorSet;
	if (tempN == tempD) {
		a = 1;
		b = 1;
		return ;
	}
	else if (tempN == -tempD) {
		a = -1;
		b = 1;
		return ;
	}
	else if (tempN == 0) {
		b = 1;
		return ;
	}


	if (absInt(tempN) < absInt(tempD)) {
		small = absInt(tempN);
	}
	else {
		small = absInt(tempD);
	}

	getFactors(small, factorSet);
	for (int i = 0; i < factorSet.size(); i++) {
		temp = factorSet[i];
		while (tempN%temp == 0 && tempD%temp == 0) {
			tempN /= temp;
			tempD /= temp;
		}
	}
	a = tempN;
	b = tempD;
}

/**************************************************************/
//////////////////////////////////////////////////////////////
//friend functions, those function can access private and protected members of class RationalNum objects
//////////////////////////////////////////////////////////////
/**************************************************************/

////////////////////////////////////////////////////
//function: operator+()---plus function
//input: left, right - number in RationalNum format
//output: return - result of plus in RationalNum format
////////////////////////////////////////////////////
RationalNum operator+(const RationalNum& left, const RationalNum& right) {
	RationalNum temp;
	int tempLD = left.getDenominator();
	int tempRD = right.getDenominator();
	normalizeFun(tempLD, tempRD);
	temp.setDenominator(left.getDenominator()*tempRD);
	temp.setNumerator(left.getNumerator()*tempRD+right.getNumerator()*tempLD);
	temp.normalize();
	return temp;
}

////////////////////////////////////////////////////
//function: operator-()---minus function
//input: left, right - number in RationalNum format
//output: return - result of minus in RationalNum format
////////////////////////////////////////////////////
RationalNum operator-(const RationalNum& left, const RationalNum& right) {
	return left+(-right);
}

////////////////////////////////////////////////////
//function: operator*()---multiply function
//input: left, right - number in RationalNum format
//output: return - result of multiply in RationalNum format
////////////////////////////////////////////////////
RationalNum operator*(const RationalNum& left, const RationalNum& right) {
	RationalNum temp;
	RationalNum temp_2(right.getNumerator(),left.getDenominator());
	RationalNum temp_3(left.getNumerator(),right.getDenominator());
	int a = temp_2.getDenominator();
	int b = temp_2.getNumerator();
	int c = temp_3.getDenominator();
	int d = temp_3.getNumerator();
	temp.setNumerator(b*d);
	temp.setDenominator(a*c);
	return temp;
}

////////////////////////////////////////////////////
//function: operator*()--- divide function
//input: left, right - number in RationalNum format
//output: return - result of division in RationalNum format
////////////////////////////////////////////////////
RationalNum operator/(const RationalNum& left, const RationalNum& right) {
	RationalNum temp_1(left.getNumerator(),left.getDenominator());
	RationalNum temp_2(right.getDenominator(),right.getNumerator());
	return temp_1*temp_2;
}

////////////////////////////////////////////////////
//function: operator==()--- whether equal function
//input: left, right - number in RationalNum format
//output: return - true, left is equal to right; false, otherwise
////////////////////////////////////////////////////
bool operator==(const RationalNum& left, const RationalNum& right) {
	return (left.numerator == right.numerator && left.denominator == right.denominator);
}

////////////////////////////////////////////////////
//function: operator!=()--- whether NOT equal function
//input: left, right - number in RationalNum format
//output: return - true, left is NOT equal to right; false, otherwise
////////////////////////////////////////////////////
bool operator!=(const RationalNum& left, const RationalNum& right) {
	return !(left == right);
}

////////////////////////////////////////////////////
//function: operator<()--- less than function
//input: left, right - number in RationalNum format
//output: return - true, left is less than right; false, otherwise
////////////////////////////////////////////////////
bool operator<(const RationalNum& left, const RationalNum& right) {
	int lside = left.getNumerator()*right.getDenominator();
	int rside = left.getDenominator()*right.getNumerator();
	return (lside < rside);
}

////////////////////////////////////////////////////
//function: operator>()--- greater than function
//input: left, right - number in RationalNum format
//output: return - true, left is greater than right; false, otherwise
////////////////////////////////////////////////////
bool operator>(const RationalNum& left, const RationalNum& right) {
	int lside = left.getNumerator()*right.getDenominator();
	int rside = left.getDenominator()*right.getNumerator();
	return (lside > rside);
}

////////////////////////////////////////////////////
//function: operator<=()--- less than or equal to function
//input: left, right - number in RationalNum format
//output: return - true, left is less than or equal to right; false, otherwise
////////////////////////////////////////////////////
bool operator<=(const RationalNum& left, const RationalNum& right) {
	return ( (left < right) || (left == right) );
}

////////////////////////////////////////////////////
//function: operator>=()--- greater than or equal to function
//input: left, right - number in RationalNum format
//output: return - true, left is greater than or equal to right; false, otherwise
////////////////////////////////////////////////////
bool operator>=(const RationalNum& left, const RationalNum& right) {
	return ( (left > right) || (left == right) );
}

ostream& operator<<(ostream& out, const RationalNum& obj) {
	out << obj.numerator;
	if (obj.numerator != 0 && obj.denominator != 1) {
		out << "/" << obj.denominator;
	}
	return out;
}


/**************************************************************/
//////////////////////////////////////////////////////////////
//member functions
//////////////////////////////////////////////////////////////
/**************************************************************/

RationalNum::RationalNum() {
	setNumerator(0);
	setDenominator(1);
}

RationalNum::RationalNum(double x) {
	int i = 1;
	while (x*i-static_cast<int>(x*i) != 0) {
		if (i > INT_MAX/10) {
			cout << "this frational number : " << x << " can not be transfer to rational number, it's too long, now set it 0." << endl;
			setNumerator(0);
			setDenominator(1);
			return ;
		}
		else {
			i *= 10;
		}
	}
	setNumerator(x*i);
	setDenominator(i);
	normalize();
}

RationalNum::RationalNum(int numerator_, int denominator_) {
	int n = numerator_;
	int d = denominator_;
	if (d==0) {
		setNumerator(0); 
		setDenominator(1);
	} 
	else {
		if (d<0) { // right, we don't want this negative, so
			n = -n;
			d = -d;	// if they were both negative, we want them both positive
			// otherwise, n is now negative
		}
	}

	setNumerator(n);
	setDenominator(d);
	normalize();
}

RationalNum& RationalNum::operator=(const RationalNum& obj) {
	setNumerator(obj.getNumerator());
	setDenominator(obj.getDenominator());
	return *this;
}

//turn negative
RationalNum RationalNum::operator-() const {
	RationalNum temp;
	temp.setNumerator(-getNumerator());
	temp.setDenominator(getDenominator());
	return temp;
}

void RationalNum::setNumerator(int numerator_) {
	numerator = numerator_;
}

int RationalNum::getNumerator() const {
	return numerator;
}

void RationalNum::setDenominator(int denominator_) {
	if (denominator_ == 0) {
		denominator = 1;
		numerator = 0;
		cout << "Denominator is 0! Not good! THe whole is set to 0." << endl;
	}
	else {
		denominator = denominator_;
	}
}

int RationalNum::getDenominator() const {
	return denominator;
}


void RationalNum::normalize() {
	int tempN = numerator;
	int tempD = denominator;
	normalizeFun(tempN,tempD);
	setNumerator(tempN);
	setDenominator(tempD);
}

/**************************************************************/
//////////////////////////////////////////////////////////////
//DEMO function
//////////////////////////////////////////////////////////////
/**************************************************************/

void test(const RationalNum &left, const RationalNum &right) {

	bool isLessThan=false;
	bool isGreaterThan=false;

	cout << "left = " << left << endl;
	cout << "right = " << right << endl;

	//compare
	if(left == right) cout << "left is equal to right" << endl;
	if(left != right) cout << "left is not equal to right" << endl;
	if(left < right) cout << "left is less than right" << endl;
	if(left > right) cout << "left is greater than right" << endl;
	if(left >= right) cout << "left is greater than or euqal to right" << endl;
	if(left <= right) cout << "left is less than or euqal to right" << endl;

	//+, - * /
	cout << "left+right = " << (left+right) << endl;
	cout << "left-right = " << (left-right) << endl;
	cout << "left*right = " << (left*right) << endl;
	cout << "left/right = " << (left/right) << endl;

}



void main() {

	RationalNum half(1,2);
	RationalNum one(1);
	RationalNum two(2);

	// Some basic checks
	assert(half.numerator() == 1);
	assert(half.denominator() == 2);
	assert(half == RationalNum(0.5));
	
	// Sign handling
	RationalNum minus_half(-1,2);
	assert(-half == minus_half);

	// Do we avoid overflow?
	RationalNum big(INT_MAX, 2);
	assert(2 * big == maxint);
    
	// Arithmetic
	assert(half + half == one);
	assert(one - half == half);
	assert(two * half == one);
	assert(one / half == two);

	//various test cases
	test(RationalNum(1,2), RationalNum(3,-4));
	test(RationalNum(1,2), RationalNum(1,3));
	test(RationalNum(1,3), RationalNum(1,2));
	test(RationalNum(-1,3), RationalNum(1,-2));
	test(RationalNum(7), RationalNum(-12,-10));
	test(RationalNum(0.75), RationalNum(0.75));

}
