bfs(std::vector<std::vector<int>> g, int s){
  queue<int> q;
  q.push (s);
  vector<bool> used (n);
  used[s] = true;
  while (!q.empty()) {
  	int v = q.front();
  	q.pop();
  	for (size_t i=0; i<g[v].size(); ++i) {
  		int to = g[v][i];
  		if (!used[to]) {
  			used[to] = true;
  			q.push (to);
  		}
  	}
  }
}
