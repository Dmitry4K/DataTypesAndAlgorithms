template<class T>
void countingSort(std::vector<T>& a) {
	if (a.size() < 2) {
		return;
	}
	T maxEl = a[0];
	for (size_t i = 1; i < a.size(); ++i) {
		if (maxEl < a[i]) {
			maxEl = a[i];
		}
	}
	std::vector<T> c(maxEl + 1);
	for (T i = 0; i <= maxEl; ++i)
		c[i] = 0;
	for (size_t i = 0; i < a.size(); ++i)
		c[a[i]]++;
	for (T i = 1; i <= maxEl; ++i)
		c[i] += c[i - 1];
	std::vector<T> b(a.size());
	size_t i = a.size();
	do {
		--i;
		--c[a[i]];
		b[c[a[i]]] = a[i];
	} while (i > 0);
	for (size_t i = 0; i < a.size(); i++)
		a[i] = b[i];
}
