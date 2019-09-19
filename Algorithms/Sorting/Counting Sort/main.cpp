#include<iostream>
#include"counting_sort.h"

void print_matrix(unsigned int* matrix, int size) {
	for (int i = 0; i < size; i++)
		std::cout << matrix[i]<<' ';
	std::cout << std::endl;
	system("pause");
}

int find_max(unsigned int * arr, int size) {
	int max = arr[1];
	for (int i = 0; i < size; i++)
		if (arr[i] > max)
			max = arr[i];
	return max;
}

int main() {
	unsigned int arr[11] = { 1, 4, 6, 2, 2, 1, 3 ,4 ,5 ,6,7 };
	int size = 11;
	counting_sort(arr,size, find_max(arr, size));
	print_matrix(arr,size);

	return 0;
}
