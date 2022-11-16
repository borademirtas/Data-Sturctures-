struct st{
    vector<vll> st;
    vll lg;
    void init(ll n, vll a){
        st.resize(n+2);
        for(ll i = 0; i < st.size(); i++){st[i].resize(26);}
        for(ll i = 0; i < a.size(); i++){st[i][0] = a[i];}
        for (int j = 1; j <= 25; j++){
            for (int i = 0; i + (1 << j) < n+2; i++){
                st[i][j] = min(st[i][j-1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
        lg.resize(n+2);
        lg[1] = 0;
        for (ll i = 2; i <= n + 1; i++){lg[i] = lg[i/2] + 1;}
    }
    ll calc(ll l, ll r){
        ll j = lg[r-l+1];
        ll mx = min(st[l][j], st[r - (1 << j) + 1][j]);
        return mx;
    }
};
