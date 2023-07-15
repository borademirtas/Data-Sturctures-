ll N = 1e7;
vll calc(N+1);
 
 vll quick(ll n){
     vll primes;
     while(n >= 2){
         primes.pb(calc[n]);
         n /= calc[n];
     }
     return primes;
 }

 for(ll i = 0; i <= N; i++){calc[i] = i;}
    for(ll i = 2; i <= N; i++){
        if(calc[i] != i){continue;}
        for(ll j = i; j <= N; j += i){
            calc[j] = min(calc[j], i);
        }
    }
