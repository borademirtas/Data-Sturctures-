ll mod = 1e9+7;
vll invt, inv,fac;
void precalc(ll n){
    invt.resize(n+5); fac.resize(n+5); inv.resize(n+5); invt[1] = 1; fac[0] = 1; inv[0]=1; inv[1]=1;
    for(ll i = 1; i < fac.size(); i++){fac[i] = fac[i-1] * i; fac[i] %= mod;}
    for(ll i=2; i<=n; i++){ invt[i] = (mod - ((mod/i)*invt[mod%i])%mod)%mod;}
    for(ll i = 1; i <= n; i++){inv[i]=invt[i]*inv[i-1]%mod;}
}
ll ncr(ll n, ll k) {if(k>n){return 0;} return fac[n] * inv[n-k] % mod * inv[k] % mod;}
