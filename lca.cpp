struct lca {
	int lg;
	vector<vector<int>> memo;
	vector<int> depth, subSize;
 
	lca(const vector<vector<int>>& adj, int root) :
		lg(32 - __builtin_clz(adj.size()|1)),
		memo(adj.size(), vector<int>(lg)),
		depth(adj.size()),
		subSize(adj.size()) {
		dfs(root, root, adj);
	}
 
	void dfs(int node, int par, const vector<vector<int>>& adj) {
		memo[node][0] = par;
		subSize[node] = 1;
		for (int i = 1; i < lg; ++i)
			memo[node][i] = memo[memo[node][i - 1]][i - 1];
		for (int to : adj[node]) {
			if (to == par) continue;
			depth[to] = 1 + depth[node];
			dfs(to, node, adj);
			subSize[node] += subSize[to];
		}
	}
 
	int kthPar(int node, int k) const {
		for (int bit = 0; bit < lg; bit++)
			if (k & (1 << bit))
				node = memo[node][bit];
		return node;
	}
 
	int getLca(int x, int y) const {
		if (depth[x] < depth[y]) swap(x, y);
		x = kthPar(x, depth[x] - depth[y]);
		if (x == y) return x;
		for (int bit = lg - 1; bit >= 0; bit--)
			if (memo[x][bit] != memo[y][bit]) {
				x = memo[x][bit];
				y = memo[y][bit];
			}
		assert(x != y && memo[x][0] == memo[y][0]);
		return memo[x][0];
	}
 
	int distEdges(int x, int y) const {
		return depth[x] + depth[y] - 2 * depth[getLca(x, y)];
	}
};
 
