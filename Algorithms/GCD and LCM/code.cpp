int gcd(int a, int b)
{
	while (a > 0 && b > 0)

		if (a > b)
			a %= b;

		else
			b %= a;

	return a + b;
}

int gcd(std::vector<int>& a)
{
	int k = a[0];
	for (int i = 1; i < a.size(); i++)
		k = gcd(k, a[i]);
	return k;
}

int lcm(int a, int b) {
	return (a * b) / gcd(a, b);
}

int lcm(std::vector<int>& a) {
	int k = a[0];
	for (int i = 1; i < a.size(); i++)
		k = lcm(k, a[i]);
	return k;
}
