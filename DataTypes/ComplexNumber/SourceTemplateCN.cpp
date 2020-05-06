#include"TemplateComplexNumber.h"
#include<vector>
int main() {
	using Type = int;//double , float , etc
	ComplexNumber<Type> a(1, 3);
	ComplexNumber<Type> b(4, -5);
	ComplexNumber<Type> c = a + b;
	std::cout << a << '+' << b << '=' << c << std::endl;
	ComplexNumber<Type> d(1, -1);
	ComplexNumber<Type> e(3, 6);
	ComplexNumber<Type> f = d * e;
	std::cout << d << '*' << e << '=' << f << std::endl;
	ComplexNumber<Type> g(13, 1);
	ComplexNumber<Type> h(7, -6);
	ComplexNumber<Type> i = g / h;
	std::cout << g << '/' << h << '=' << i << std::endl;
	return 0;
}
