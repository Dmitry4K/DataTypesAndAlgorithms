#pragma once
void counting_sort(unsigned int* a, int size, int max_el) {
	int* c = new int[max_el+1];
	for (int i = 0; i <= max_el; i++)
		c[i] = 0;
	for (int i = 0; i < size; i++)
		c[a[i]]++;
	for (int i = 1; i <= max_el; i++)
		c[i] += c[i - 1];
	unsigned int* b = new int[size];
	for (int i = size - 1; i >= 0; i--) {
		c[a[i]]--;
		b[c[a[i]]] = a[i];
	}
	for (int i = 0; i < size; i++)
		a[i] = b[i];
}
