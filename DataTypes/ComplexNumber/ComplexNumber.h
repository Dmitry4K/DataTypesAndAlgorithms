#pragma once
#include<string>
#include<iostream>
class ComplexNumber {
	public:
	using Type = int;
	private:
	Type Re;
	Type Im;
	public:
	ComplexNumber(Type re, Type im);
	//ComplexNumber(const char* str);
	ComplexNumber(ComplexNumber&& a) noexcept;
	ComplexNumber(const ComplexNumber&);
	Type getRe() const;
	Type getIm() const;
	ComplexNumber getСonjugate() const;
	//const char* getAtomicString() const;
	std::string getStdString() const;
	void PrintToStdStream() const;
	void PrintToCustomStream(std::ostream& out) const;
};
ComplexNumber Sum(const ComplexNumber& a, const ComplexNumber& b);
const ComplexNumber operator+(const ComplexNumber& a, const ComplexNumber& b);
ComplexNumber Sub(const ComplexNumber& a, const ComplexNumber& b);
const ComplexNumber operator-(const ComplexNumber& a, const ComplexNumber& b);
ComplexNumber Mul(const ComplexNumber& a, const ComplexNumber& b);
const ComplexNumber operator*(const ComplexNumber& a, const ComplexNumber& b);
ComplexNumber Div(const ComplexNumber& a, const ComplexNumber& b);
const ComplexNumber operator/(const ComplexNumber& a, const ComplexNumber& b);
ComplexNumber Div(const ComplexNumber& a, const ComplexNumber::Type b);
const ComplexNumber operator/(const ComplexNumber& a, const ComplexNumber::Type b);

std::ostream& operator<< (std::ostream& out, const ComplexNumber& point);
