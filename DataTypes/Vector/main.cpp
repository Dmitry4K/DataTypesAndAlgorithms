
#include<iostream>
#include"vector.h"

template<class T> void print_vector(d4k::vector<T>& a) {
	std::cout << "Vector: " << &a <<" sizeof: "<<sizeof(a)<<" size: " << a.size() << " capacity: " << a.capacity() << std::endl;
	for (int i = 0; i < (int)a.size(); i++)
		std::cout << a[i] << ' ';
	std::cout<<std::endl;
}

int main() {
	d4k::vector<int> a;

	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(10);

	d4k::vector<int> c(3);
	c[0] = 1;
	c[1] = 2;
	c[2] = 3;

	a = c;

	print_vector<int>(a);
	print_vector<int>(c);

	d4k::vector<char> b;
	b.push_back('a');
	b.push_back('b');
	b.push_back('c');

	print_vector<char>(b);

	system("pause");
	return 0;
}
