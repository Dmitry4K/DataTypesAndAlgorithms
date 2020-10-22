/* Console view
4
11 44 11 11
9
11 44 11 11 11 44 11 11 32
0 4
*/
int main() {
	std::vector<long long> string;
	std::vector<long long> pattern;
	long long patternSize;
	long long stringSize;

	std::cin >> patternSize;
	pattern.resize(patternSize);
	for (long long i = 0; i < patternSize; ++i) {
		std::cin >> pattern[i];
	}
	std::cin >> stringSize;
	string.resize(stringSize);

	for (long long i = 0; i < stringSize; ++i) {
		std::cin >> string[i];
	}
	std::vector<long long> result;
	BoyerMooreAlgorithm(string, pattern, result);
	for (auto el : result) {
		std::cout << el << ' ';
	}
}
