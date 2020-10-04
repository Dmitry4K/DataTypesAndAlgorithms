//O(sqrt(n))

bool isSimple(unsigned long long n) {
	for (unsigned long long i = 2; i * i <= n; ++i) {
		if (n % i == 0) {
			return false;
		}
	}
	return true;
}
