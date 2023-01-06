struct dsu{
    vll parent;
 
    void init(ll n){
        parent.resize(n+1);
        for(ll i = 1; i <= n; i++){parent[i] = i;}
    }
 
    void make_set(int v) {
        parent[v] = v;
    }
 
    int find_set(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]);
    }
 
    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b)
            parent[b] = a;
    }
 
};
