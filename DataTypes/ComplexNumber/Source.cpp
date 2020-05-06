#include"ComplexNumber.h"

int main() {
	ComplexNumber a(1, 3);
	ComplexNumber b(4, -5);
	ComplexNumber c = a + b;
	std::cout << a << '+' << b << '=' << c << std::endl;
	ComplexNumber d(1, -1);
	ComplexNumber e(3, 6);
	ComplexNumber f = d * e;
	std::cout << d << '*' << e << '=' << f << std::endl;
	ComplexNumber g(13, 1);
	ComplexNumber h(7, -6);
	ComplexNumber i = g / h;
	std::cout << g << '/' << h << '=' << i << std::endl;
	return 0;
}
