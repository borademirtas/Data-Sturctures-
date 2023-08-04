struct lca {
	ll lg;
	vector<vector<ll>> memo;
	vector<ll> depth, subSize;
 
	lca(const vector<vector<ll>>& adj, ll root) :
		lg(32 - __builtin_clzll(adj.size()|1LL)),
		memo(adj.size(), vector<ll>(lg)),
		depth(adj.size()),
		subSize(adj.size()) {
		dfs(root, root, adj);
	}
 
	void dfs(ll node, ll par, const vector<vector<ll>>& adj) {
		memo[node][0] = par;
		subSize[node] = 1;
		for (ll i = 1; i < lg; ++i)
			memo[node][i] = memo[memo[node][i - 1]][i - 1];
		for (ll to : adj[node]) {
			if (to == par) continue;
			depth[to] = 1 + depth[node];
			dfs(to, node, adj);
			subSize[node] += subSize[to];
		}
	}
 
	ll kthPar(ll node, int k) const {
		for (ll bit = 0; bit < lg; bit++)
			if (k & (1 << bit))
				node = memo[node][bit];
		return node;
	}
 
	ll getLca(ll x, ll y) const {
		if (depth[x] < depth[y]) swap(x, y);
		x = kthPar(x, depth[x] - depth[y]);
		if (x == y) return x;
		for (ll bit = lg - 1; bit >= 0; bit--)
			if (memo[x][bit] != memo[y][bit]) {
				x = memo[x][bit];
				y = memo[y][bit];
			}
		assert(x != y && memo[x][0] == memo[y][0]);
		return memo[x][0];
	}
 
	ll distEdges(ll x, ll y) const {
		return depth[x] + depth[y] - 2 * depth[getLca(x, y)];
	}
};
 
