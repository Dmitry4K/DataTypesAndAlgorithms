//getted from wikipedia
#pragma once
#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include<utility>
#include<set>
template<class T>
void GoodSuffix(const std::vector<T>& s, std::vector<long long>& gs) {
	long long m = s.size();
	gs.resize(m + 1);
	std::fill(gs.begin(), gs.end(), m);
	std::vector<long long> z(m, 0);
	for (long long j = 1, maxZidx = 0, maxZ = 0; j < m; ++j) {
		if (j <= maxZ) z[j] = std::min(maxZ - j + 1, z[j - maxZidx]);
		while (j + z[j] < m && s[m - 1 - z[j]] == s[m - 1 - (j + z[j])]) z[j]++;
		if (j + z[j] - 1 > maxZ) {
			maxZidx = j;
			maxZ = j + z[j] - 1;
		}
	}
	for (long long j = m - 1; j > 0; j--) gs[m - z[j]] = j; //цикл №1
	for (long long j = 1, r = 0; j <= m - 1; j++) //цикл №2
		if (j + z[j] == m)
			for (; r <= j; r++)
				if (gs[r] == m) gs[r] = j;
}

template<class T>
void BadSymbolsTableHashMap(const std::vector<T>& pattern, std::unordered_map<T, long long>& table) {
	for (long long i = 0; i < pattern.size()-1; ++i) {
		table[pattern[i]] = i;
	}
}

template<class T>
void PatternToSymbolsSet(const std::vector<T>& pattern, std::set<T>& symbols) {
	for (long long i = 0; i < pattern.size(); ++i) {
		symbols.insert(pattern[i]);
	}
}

template<class T>
void BoyerMooreAlgorithm(const std::vector<T>& string, const std::vector<T>& pattern, std::vector <long long>& result) {
	std::unordered_map<T, long long> bs;
	std::vector<long long> ss;
	GoodSuffix(pattern, ss);
	BadSymbolsTableHashMap(pattern, bs);
	long long m = pattern.size();
	long long n = string.size();
	long long j, bound = 0; //всегда либо bound = 0, либо bound = m - suffshift[0]
	for (long long i = 0; i <= n - m;i += (j < bound ? ss[j + 1] : std::max(ss[j + 1], j - (bs.find(string[i+j]) != bs.end() ? bs.find(string[i + j])->second : (long long)0)))) {
		for (j = m - 1; j >= bound && pattern[j] == string[i + j]; j--);
		if (j < bound) {
			result.push_back(i);
			bound = m - ss[0];
			j = -1; //установить j так, как будто мы прочитали весь шаблон s, а не только до границы bound
		}
		else {
			bound = 0;
		}
	}
}
