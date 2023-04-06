#include"bubble_sort.h"

void bubble_sort(int* matrix, int size) {
	int temp;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size - 1; j++)
			if (matrix[j] > matrix[j + 1]) {
				temp = matrix[j];
				matrix[j] = matrix[j + 1];
				matrix[j + 1] = temp;
			}
}

void bubble_sort(double* matrix, int size) {
	double temp;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size - 1; j++)
			if (matrix[j] > matrix[j + 1]) {
				temp = matrix[j];
				matrix[j] = matrix[j + 1];
				matrix[j + 1] = temp;
			}
}

void bubble_sort(char* matrix, int size) {
	char temp;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size - 1; j++)
			if (matrix[j] > matrix[j + 1]) {
				temp = matrix[j];
				matrix[j] = matrix[j + 1];
				matrix[j + 1] = temp;
			}
}
