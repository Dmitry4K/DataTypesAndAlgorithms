using graph = std::vector<std::vector<int>>;
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
//g - must be bipartite graph
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
