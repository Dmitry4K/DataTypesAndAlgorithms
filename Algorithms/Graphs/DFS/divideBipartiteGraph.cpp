using graph = std::vector<std::vector<int>>; //vector of incident vertexes

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
