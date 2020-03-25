#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<cmath>
#include<algorithm>
#include<iomanip>


const unsigned long long DEFAULT_BASE_FOR_LONG_NUMBER = 1000000;

class LongNumber {
private:
	long long Base = DEFAULT_BASE_FOR_LONG_NUMBER;
	std::vector<long long> Container;
public:
	LongNumber();
	LongNumber(const std::string& str);
	LongNumber(long long a);
	void Clear();
	void Print(std::ostream& out) const;
	friend int Cmp(const LongNumber& a, const LongNumber& b);
	friend bool operator>(const LongNumber& a, const LongNumber& b);
	friend bool operator<(const LongNumber& a, const LongNumber& b);
	friend bool operator>=(const LongNumber& a, const LongNumber& b);
	friend bool operator<=(const LongNumber& a, const LongNumber& b);
	friend bool operator==(const LongNumber& a, const LongNumber& b);
	friend bool operator!=(const LongNumber& a, const LongNumber& b);

	friend LongNumber Sum(const LongNumber& a, const LongNumber& b);//a > 0 , b > 0
	friend LongNumber Sub(const LongNumber& a, const LongNumber& b);// a - b > 0
	friend LongNumber Mult(const LongNumber& a, const LongNumber& b);
	friend LongNumber Div(const LongNumber& a, const LongNumber& b);
	friend LongNumber SmallDiv(const LongNumber& a, const int& b);
	friend LongNumber SmallMult(const LongNumber& a, const int& b);
	friend std::ostream& operator<< (std::ostream& out, const LongNumber& a);
	friend LongNumber Exp(const LongNumber& a, const LongNumber&);
	friend LongNumber SmallExp(const LongNumber& a, const LongNumber& b);
};
LongNumber SmallMult(const LongNumber& a, const int& b);
LongNumber Exp(const LongNumber& a, const LongNumber&);
LongNumber SmallDiv(const LongNumber& a, const int& b);
int Cmp(const LongNumber& a, const LongNumber& b);
LongNumber Sum(const LongNumber& a, const LongNumber& b);
LongNumber Sub(const LongNumber& a, const LongNumber& b);
LongNumber Mult(const LongNumber& a, const LongNumber& b);
LongNumber Div(const LongNumber& a, const LongNumber& b);
std::ostream& operator<< (std::ostream& out, const LongNumber& a);
