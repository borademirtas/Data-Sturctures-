pair<bool, vll> dicycle(vector<vll> adj){
    ll n = adj.size();
    vll color(n), parent(n,-1), cycle;
    ll cycle_start = -1, cycle_end;

    auto dfs =[&](ll v, auto dfs)->bool{
        color[v] = 1;
        for (ll u : adj[v]) {
            if (color[u] == 0) {
                parent[u] = v;
                if (dfs(u,dfs)){return true;}
            } else if (color[u] == 1) {
                cycle_end = v;
                cycle_start = u;
                return true;
            }
        }
        color[v] = 2;
        return false;
    };

    if(cycle_start==-1){return {false, cycle};}
    else{
        cycle.push_back(cycle_start);
        for (int v = cycle_end; v != cycle_start; v = parent[v])
            cycle.push_back(v);
        cycle.push_back(cycle_start);
        reverse(cycle.begin(), cycle.end());
        return {true, cycle};
    }

}
