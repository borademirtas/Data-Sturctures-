vll factorial(SET+1); ll mod = SET;
void calc(){factorial[0] = 1; for(ll i = 1; i < factorial.size(); i++){factorial[i] = factorial[i-1] * i; factorial[i] %= mod;}}
ll inverse(ll a, ll m){ll m0 = m; ll y = 0, x = 1;  while (a > 1) { ll q = a / m; ll t = m; m = a % m, a = t; t = y; y = x - q * y; x = t;} if (x < 0){x += m0;}return x;}
ll nCr(ll n, ll k, ll m) {return factorial[n] * inverse(factorial[k] * factorial[n - k] % m, m) % m;}
