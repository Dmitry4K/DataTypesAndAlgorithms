#include<iostream>
#include"radix_sort.h"
void print_matrix(unsigned int* arr, int size) {
	for (int i = 0; i < size; i++) std::cout << arr[i] << ' '; std::cout << std::endl;
}

void test(unsigned int *arr, int size) {
	std::cout << "raw arr: ";
	print_matrix(arr, size);
	radixSort(arr, size);
	std::cout << "sort arr: ";
	print_matrix(arr, size);
	std::cout<<std::endl;
	//system("pause");
}

int main() {
	int test1_size = 5;
	unsigned int test1[5] = { 0, 10, 10010, 0, 1022};

	int test2_size = 1;
	unsigned int test2[1] = { 1 };

	int test3_size = 10;
	unsigned int test3[10] = { 0, 0, 1002, 120, 20, 19999, 4566, 1003, 0, 1 };

	int test4_size = 100;
	unsigned int * test4 = new unsigned int[test4_size];
	for (int i = 0; i < test4_size; i++)
		test4[i] = (unsigned int)rand() % 100000;

	std::cout << "BIT_SIZE: " << BIT_SIZE << " PART_COUNT: " << PART_COUNT << " PART_MASK: " << PART_MASK << " PART_SIZE: " << PART_SIZE << std::endl << std::endl;
	
	test(test1, test1_size);
	test(test2, test2_size);
	test(test3, test3_size);
	test(test4, test4_size);

	system("pause");
}
