template<class T>
void countingSort(std::vector<T>&a) {
	T maxEl = a[0];
	for (int i = 1; i < a.size(); ++i) {
		if (maxEl < a[i]) {
			maxEl = a[i];
		}
	}
	std::vector<T> c(maxEl + 1);
	for (int i = 0; i <= maxEl; ++i)
		c[i] = 0;
	for (int i = 0; i < a.size(); ++i)
		c[a[i]]++;
	for (int i = 1; i <= maxEl; ++i)
		c[i] += c[i - 1];
	std::vector<T> b(a.size());
	for (int i = a.size() - 1; i >= 0; i--) {
		c[a[i]]--;
		b[c[a[i]]] = a[i];
	}
	for (int i = 0; i < a.size(); i++)
		a[i] = b[i];
}
