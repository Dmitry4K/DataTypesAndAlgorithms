#include<iostream>
#include<string>
#include"SuffixTree.h"

int main() {
	std::string line, str;
	std::cin >> line;
	SuffixTree myTree(line);
	std::vector<int> res;
	myTree.BuildArray();
	int i = 1;
	while (std::cin >> str) {
		res = myTree.Search(str);
		if (!res.empty()) {
			std::cout << i << ": " << res[0];
			for (int i = 1; i < res.size(); ++i) {
				std::cout << ", " << res[i];
			}
			std::cout << std::endl;
		}
		++i;
	}
}
