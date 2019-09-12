#include<iostream>
#include"bubble_sort.h"

void print_matrix(int* matrix, int size) {
	for (int i = 0; i < size; i++)
		std::cout << matrix[i] << ' ';
	std::cout << std::endl;
}

int main() {
	int size;
	std::cin >> size;
	int* matrix = new int[size];

	for (int i = 0; i < size; i++)
		std::cin >> matrix[i];

	bubble_sort(matrix, size);

	print_matrix(matrix, size);
	delete[] matrix;
	system("pause");
	return 0;
}
