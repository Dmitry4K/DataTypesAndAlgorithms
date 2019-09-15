#include<iostream>
#include"counting_sort.h"

void print_matrix(int* matrix, int size) {
	for (int i = 0; i < size; i++)
		std::cout << matrix[i]<<' ';
	std::cout << std::endl;
	system("pause");
}

int main() {
	int arr[11] = { 1, 4, 6, 2, 2, 1, 3 ,4 ,5 ,6,7 };
	counting_sort(arr,11, 7);
	print_matrix(arr,11);

	return 0;
}
