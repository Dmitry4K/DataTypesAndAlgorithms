#include"radix_sort.h"
void counting_sort_bit(unsigned int* a, int size, int point) {//max_el известен
	//std::cout << "iteration: " << point << std::endl;
	unsigned int* c = new unsigned int[PART_MASK];
	for (unsigned int i = 0; i < PART_MASK; i++)
		c[i] = 0;
	for (int i = 0; i < size; i++)
		c[(a[i] & ((PART_MASK - 1) << point)) >> point]++;
	for (unsigned int i = 1; i < PART_MASK; i++)
		c[i] += c[i - 1];
	unsigned int* b = new unsigned int[size];
	for (int i = size - 1; i >= 0; i--) {
		c[(a[i] & ((PART_MASK - 1) << point)) >> point]--;
		b[c[(a[i] & ((PART_MASK - 1) << point)) >> point]] = a[i];
	}
	for (int i = 0; i < size; i++)
		a[i] = b[i];
	delete[] c;
	delete[] b;
}
void radixSort(unsigned int* arr, int size) {

	for (unsigned int i = 0; i < PART_COUNT; ++i) {
		counting_sort_bit(arr, size, i*PART_SIZE);
	}
}
