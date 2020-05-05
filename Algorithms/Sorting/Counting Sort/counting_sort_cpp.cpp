template<class T>//only indexed types : int , long int , unsigned int , etc
void countingSort(std::vector<T>&a) {
	if (a.size() == 0) {
		return;
	}
	T maxEl = a[0];
	for (size_t i = 1; i < a.size(); ++i) {
		if (maxEl < a[i]) {
			maxEl = a[i];
		}
	}
	std::vector<T> c(maxEl + 1);
	for (size_t i = 0; i <= maxEl; ++i)
		c[i] = 0;
	for (size_t i = 0; i < a.size(); ++i)
		c[a[i]]++;
	for (size_t i = 1; i <= maxEl; ++i)
		c[i] += c[i - 1];
	std::vector<T> b(a.size());
	for (size_t i = a.size() - 1; i >= 0; i--) {
		c[a[i]]--;
		b[c[a[i]]] = a[i];
	}
	for (size_t i = 0; i < a.size(); i++)
		a[i] = b[i];
}
