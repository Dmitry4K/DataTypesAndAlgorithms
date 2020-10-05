//d[i] - max length of subsequence from i elment
//p[i] - index in a to prev element of max subsequence in a
void MaxAscendingSubsequence(std::vector<int>& a, int n, std::vector<int>& d, std::vector<int>& p){
  d.resize(n);
  p.resize(n);
	p[0] = -1;
	for (int i = 0; i < n; ++i) {
		d[i] = 1;
		p[i] = -1;
		for (int j = 0; j < i; ++j)
			if (a[j] < a[i] ) {
				if (1 + d[j] > d[i]) {
					p[i] = j;
					d[i] = 1 + d[j];
				}
			}
	}
}
