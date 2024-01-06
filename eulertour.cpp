struct euler_tour{

    int timer = 0;
    vll start, end, full;

    void dfs1(int at, int prev, vector<vll> &adj){
        start[at] = timer++;
        for(ll x: adj[at]){
            if(x!=prev){dfs1(x,at, adj);}
        }
        end[at] = timer;
    }

    array<vll,2> subtree(int n, int root, vector<vll> &adj){
        start.resize(n+1); end.resize(n+1);
        dfs1(root,-1,adj);
        return {start,end};
    }
    void dfs2(int at, int prev, vector<vll> &adj){
        start[at] = full.size();  full.pb(at);
        for(ll x: adj[at]){
            if(x!=prev){dfs2(x,at, adj);}
        }
        end[at] = full.size();  full.pb(-at);
    }
    array<vll,3> path(int n,int root, vector<vll> &adj){
        start.resize(n+1); end.resize(n+1);
        dfs2(root,-1,adj);
        return {start,end,full};
    }


};
