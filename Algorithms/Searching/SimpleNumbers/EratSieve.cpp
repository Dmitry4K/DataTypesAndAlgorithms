#include<vector>

//Complexity O(nloglog(n))
//Memory O(n)
void getSimpleNumbers(std::vector<int>& a, int n) {
	std::vector<bool> numbers(n + 1);
	numbers[0] = numbers[1] = true;
	for (int i = 2; i <= n; ++i) {
		if (!numbers[i]) {
			a.push_back(i);
			for (int j = i; j <= n; j += i) {
				numbers[j] = true;
			}
		}
	}
}
