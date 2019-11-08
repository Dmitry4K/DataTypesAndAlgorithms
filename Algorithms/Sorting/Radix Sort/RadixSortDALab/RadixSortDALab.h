#pragma once
//This type of sort uses for sorting key-value strings where keys is car numbers and values is 2048's string
//This key-value string holds in TVector (can can be replaced with std::vector)

int c[256];

void RadixSort(TVector<Element>& arr, TVector<Element>& b) {
	for (int j = 7; j >= 0; j--) {
		if (j == 1 || j == 5)
			continue;
		for (int i = '0'; i < 'Z' + 1; i++) {
			c[i] = 0;
		}
		for (int i = 0; i < (int)arr.Size(); i++) {
			c[(int)arr[i].key[j]]++;
		}
		for (int i = '0' + 1; i < 'Z' + 1; i++) {
			c[i] += c[i - 1];
		}
		for (int i = arr.Size() - 1; i >= 0; i--) {
			b[--c[(int)arr[i].key[j]]] = arr[i];
		}
		arr = b;
	}
}
