struct DSU {
    vll time, par; vector<vll> version, sz;
    DSU(int N) {
        time.resize(N); par.resize(N); version.resize(N); sz.resize(N);
        for(ll i = 0; i < N; i++){par[i]=i; version[i].pb(0); sz[i].pb(1);}
    }
    int get(int x, int t) {
         if(par[x]==x||time[x]>t){return x;}
         else{return get(par[x], t);}
    }
    int size(int x, int t) {x = get(x,t); int pos = upper_bound(version[x].begin(),version[x].end(),t) - version[x].begin(); return sz[x][pos-1]; }
    void unite(int x, int y, int t ) {
        x = get(x,t); y = get(y,t);
        if(x==y){return;}
        if(sz[x]>sz[y]){swap(x,y);}
        par[x]=y;
        time[x]=t;
        version[y].pb(t);
        sz[y].pb(sz[x].back()+sz[y].back());
    }
};
