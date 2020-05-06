#include"ComplexNumber.h"

ComplexNumber::Type ComplexNumber::getRe() const {
	return Re;
}

ComplexNumber::Type ComplexNumber::getIm() const {
	return Im;
}

ComplexNumber ComplexNumber::getСonjugate() const {
	return ComplexNumber(getRe(), -getIm());
}

ComplexNumber::ComplexNumber(ComplexNumber::Type re, ComplexNumber::Type im) : Re(re), Im(im) {}

ComplexNumber::ComplexNumber(ComplexNumber&& a) noexcept : Re(a.Re), Im(a.Im) {}

ComplexNumber::ComplexNumber(const ComplexNumber& a) : Re(a.Re), Im(a.Im) {}

ComplexNumber Sum(const ComplexNumber& a, const  ComplexNumber& b) {
	return ComplexNumber(a.getRe() + b.getRe(), a.getIm() + b.getIm());
}

const ComplexNumber operator+(const ComplexNumber& a, const ComplexNumber& b) {
	return Sum(a, b);
}

ComplexNumber Sub(const ComplexNumber& a, const ComplexNumber& b) {
	return ComplexNumber(a.getRe() - b.getRe(), a.getIm() - b.getIm());
}

const ComplexNumber operator-(const ComplexNumber& a, const ComplexNumber& b) {
	return Sub(a, b);
}

ComplexNumber Mul(const ComplexNumber& a, const ComplexNumber& b) {
	return ComplexNumber(a.getRe() * b.getRe() - a.getIm() * b.getIm(), a.getRe() * b.getIm() + a.getIm() * b.getRe());
}

const ComplexNumber operator*(const ComplexNumber& a, const ComplexNumber& b) {
	return Mul(a, b);
}

ComplexNumber Div(const ComplexNumber& a, const ComplexNumber& b) {
	return Div(Mul(a, b.getСonjugate()), Mul(b, b.getСonjugate()).getRe());
}

const ComplexNumber operator/(const ComplexNumber& a, const ComplexNumber& b) {
	return Div(a, b);
}

ComplexNumber Div(const ComplexNumber& a, const ComplexNumber::Type b) {
	return ComplexNumber(a.getRe() / b, a.getIm() / b);
}

const ComplexNumber operator/(const ComplexNumber& a, const ComplexNumber::Type b) {
	return Div(a, b);
}

/*const char* ComplexNumber::getAtomicString() const {

}*/

std::string ComplexNumber::getStdString() const {
	std::string res ='('+ std::to_string(Re);
	if (Im < 0) {
		res += std::to_string(Im) + 'i';
	}
	else {
		res += '+' + std::to_string(Im) + 'i';
	}
	res += ')';
	return res;
}

void ComplexNumber::PrintToStdStream() const {
	std::cout << getStdString();
}

void ComplexNumber::PrintToCustomStream(std::ostream& out) const {
	out << getStdString();
}

std::ostream& operator<< (std::ostream& out, const ComplexNumber& point) {
	out << point.getStdString();
	return out;
}
