    auto dfs = [&](ll u, auto&& dfs)->void {
        siz[u]++;
        ll mx = 0;
        for (ll v: adj[u]) {
            if (v==par[u]){continue;}
            dep[v]=dep[u]+1; par[v]=u;
            dfs(v,dfs);
            siz[u]+=siz[v];
            if (siz[v]>mx) {
                mx=siz[v]; heavy[u] = v;
            }
        }
    };
    auto decomp = [&](ll u, ll h, auto&&decomp)->void {

        head[u]=h; pos[u]=cnt; cnt++;
        if (heavy[u]!=-1){decomp(heavy[u],h,decomp);}
        for (ll v: adj[u]) {
            if (v==par[u]||v==heavy[u]){continue;}
            decomp(v,v,decomp);
        }
    };
    dfs(0,dfs); decomp(0,0,decomp);

    auto query = [&](ll u, ll v){
        ll ans = 0;
        while (head[u]!=head[v]) {
            if (dep[head[u]]>dep[head[v]]){swap(u,v);}
            ans += s.query(pos[head[v]], pos[v]);
            v=par[head[v]];
        }
        if (dep[u]>dep[v]){swap(u,v);}
        return ans+s.query(pos[u],pos[v]);
    };
    auto upd = [&](ll u, ll v, ll val) {
        while (head[u]!=head[v]) {
            if (dep[head[u]]>dep[head[v]]){swap(u,v);}
            s.update(pos[head[v]], pos[v], {0,val});
            v=par[head[v]];
        }
        if (dep[u]>dep[v]){swap(u,v);}
        s.update(pos[u],pos[v], {0,val});
    };
