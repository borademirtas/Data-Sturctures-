struct centroid{
    vector<set<ll>> adj; vll sub, par; ll nn;
    void init(ll n){adj.resize(n+1); sub.resize(n+1); par.resize(n+1);}
    void dfs1(ll u, ll p){nn++; sub[u] = 1; for(ll v: adj[u]){if(v!=p){dfs1(v,u); sub[u]+=sub[v];}}}
    ll dfs2(ll u, ll p){for(ll v: adj[u]){if(v!=p && sub[v]>nn/2){return dfs2(v,u);}} return u;}
    void decomp(ll root, ll p){
        nn = 0;
        dfs1(root, root);
        ll cent = dfs2(root,root);
        if(p==-1){p=cent;}
        par[cent]=p;
        for(auto it = adj[cent].begin(); it!= adj[cent].end(); it++){
            adj[*it].erase(cent);
            decomp(*it, cent);
        }
        adj[cent].clear();
    }
    ll query(){
        
    }
    void update(){
        
    }
};
