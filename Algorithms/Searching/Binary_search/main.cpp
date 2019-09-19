#include<iostream>
#include"binary_search.h"

int main() {
	int arr[5] = { 1,2,3,4,5 };
	int size = 5;
	int result = binary_search(arr,size, 3);
	std::cout << result << std::endl;

	double darr[7] = { 1.0, 2.4, 5.432, 6.0, 7.0, 8.567, 10.0 };
	result = binary_search(darr, 6.0);
	std::cout << result << std::endl;

	char carr[4] = { 'a','b','c','d' };
	result = binary_search(carr, 'e');
	std::cout << result << std::endl;
	system("pause");
	return 0;

}
