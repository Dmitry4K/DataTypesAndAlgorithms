#include<iostream>
#include<vector>
#include<algorithm>

void dfs(int node_num, std::vector<std::vector<int>>& g, std::vector<bool>& used) {
	used[node_num] = true;
	for (int i = 0; i < g[node_num].size(); ++i) {
		if (!used[i]) {
			dfs(i, g, used);
		}
	}
}

void dfs(std::vector<std::vector<int>>& g, int start_point) {
	std::vector<bool> used(std::max(g.size(), g[0].size()));
	dfs(start_point, g, used);
}
