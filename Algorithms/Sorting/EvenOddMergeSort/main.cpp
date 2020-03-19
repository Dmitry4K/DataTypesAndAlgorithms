#include<iostream>
#include<vector>
#include<Windows.h>
#include"EvenOddSort.h"


int main() {
	//(-, -) (0_0) (^_^) (._.) (\=) (=-=) (p-p) 

	std::cout << "Write size of vector: ";
	int n;
	std::cin >> n;
	std::vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
	}

	std::cout << "Write count of threads: ";
	int l;
	std::cin >> l; 

	OddEvenMergeSort<int>(a,l, 0, n-1);

	for (int i = 0; i < n; ++i) {
		std::cout << a[i] << ' ';
	}
	std::cout << std::endl;
	system("pause");
	return 0;
}