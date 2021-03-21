using graph = std::vector<std::vector<int>>;

void dfs_divide(graph& g, std::vector<bool>& isUsed, int current, std::vector<int>& f, std::vector<int>& s, int even) {
	isUsed[current] = true;
	if (!even) {
		f.push_back(current);
	}
	else {
		s.push_back(current);
	}
	for (int i = 0; i < g[current].size(); ++i) {
		if (!isUsed[g[current][i]]){
			dfs_divide(g, isUsed, g[current][i], f, s, (even + 1)%2);
		}
	}
}

void divideGraph(graph& g, std::vector<int>& f, std::vector<int>& s) {	
	std::vector<bool> isUsed(g.size(), false);
	for (int i = 0; i < g.size(); ++i) {
		if (!isUsed[i]) {
			dfs_divide(g, isUsed, i, f, s, 0);
		}
	}
}
bool dfs_kun(int v, graph& g, std::vector<bool>& used, std::vector<int>& matching) {
	if (used[v]) {
		return false;
	}
	used[v] = true;
	for (size_t i = 0; i < g[v].size(); ++i) {
		if (matching[g[v][i]] == -1 || dfs_kun(matching[g[v][i]], g, used, matching)) {
			matching[g[v][i]] = v;
			return true;
		}
	}
	return false;
}
std::vector <std::pair<int, int>> KunAlgorithm(graph& g) {
	std::vector<int> matching;
	matching.assign(g.size(), -1);
	std::vector<bool> used;
	for (size_t i = 0; i < g.size(); ++i) {
		used.assign(g.size(), false);
		dfs_kun(i, g, used, matching);
	}
	used.assign(g.size(), false);
	std::vector <std::pair<int, int>> Pairs;
	for (size_t i = 0; i < matching.size(); ++i) {
		if (matching[i] != -1) {
			Pairs.push_back(std::make_pair(i, matching[i]));
		}
	}
	for (size_t i = 0; i < Pairs.size(); ++i) {
		if (Pairs[i].first > Pairs[i].second) {
			std::swap(Pairs[i].first, Pairs[i].second);
		}
	}
	std::set<std::pair<int, int>> sPairs;
	for (int i = 0; i < Pairs.size(); ++i) {
		sPairs.insert(Pairs[i]);
	}
	Pairs.clear();
	Pairs.reserve(sPairs.size());
	for (auto e : sPairs) {
		Pairs.push_back(e);
	}
	return Pairs;
}
void dfs_min_matching(int v, graph& g, std::vector<bool>& used) {
	used[v] = true;
	for (int i = 0; i < g[v].size(); ++i) {
		if(!used[g[v][i]])
			dfs_min_matching(g[v][i], g, used);
	}
}
std::vector<int> minVertexCover(graph& g) {
	std::vector<int> f;
	std::vector<int> s;
	divideGraph(g, f, s);
	graph gn(g.size());
	for (int i = 0; i < f.size(); ++i) {
		for (int j = 0; j < s.size(); ++j) {
			auto it = std::find(g[f[i]].begin(), g[f[i]].end(), s[j]);
			if (it != g[f[i]].end()) {
				gn[f[i]].push_back(s[j]);
			}
		}
	}
	for (int i = 0; i < s.size(); ++i) {
		for (int j = 0; j < f.size(); ++j) {
			auto it = std::find(g[s[i]].begin(), g[s[i]].end(), f[j]);
			if (it != g[s[i]].end()) {
				gn[s[i]].push_back(f[j]);
			}
		}
	}
	std::vector<std::pair<int, int>> maxMatching = KunAlgorithm(gn);
	int a = 1;
	//*
	graph gnn(g.size());
	std::vector<std::vector<bool>> isOnMaxMathcing(g.size(), std::vector<bool>(g.size(), false));
	for (auto e : maxMatching) {
		isOnMaxMathcing[e.first][e.second] = isOnMaxMathcing[e.second][e.first] = true;
	}
	//ориентируем граф
	for (int i = 0; i < g.size(); ++i) {
		for (int j = 0; j < g[i].size(); ++j) {
			auto it = std::find(f.begin(), f.end(), i);
			if (isOnMaxMathcing[i][g[i][j]]) {
				//i j - в максимальном паросочетании
				if (it != f.end()) {
					// i - в левой доле
					gnn[g[i][j]].push_back(i);
				}
				else {
					gnn[i].push_back(g[i][j]);
				}
			}
			else {
				//не макисмальное паросочетание
				if (it != f.end()) {
					// i - в левой доле
					gnn[i].push_back(g[i][j]);
				}
				else {
					gnn[g[i][j]].push_back(i);
				}
			}
		}
	}
	std::vector<bool> used(gnn.size(), false);
	for (int i = 0; i < gnn.size(); ++i) {
		auto it = std::find(isOnMaxMathcing[i].begin(), isOnMaxMathcing[i].end(), true);
		auto itl = std::find(f.begin(), f.end(), i);
		if (it == isOnMaxMathcing[i].end() && !used[i] && itl != f.end()) {
			dfs_min_matching(i, gnn, used);
		}
	}
	std::vector<int> minVertexCover;
	for (int i = 0; i < g.size(); ++i) {
		auto it = std::find(f.begin(), f.end(), i);
		if (it != f.end()) {
			//i - в левой доле
			if (!used[i]) {
				minVertexCover.push_back(i);
			}
		}
		else {
			if (used[i]) {
				minVertexCover.push_back(i);
			}
		}
	}
	return minVertexCover;
	//*/
}
