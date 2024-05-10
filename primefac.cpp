vp pf(ll x){ll n = x; vp ans;
    while(n % 2 == 0) {
        if(ans.empty()){ans.pb({2,1});}
        else{ans.back().S++;}
        n = n/2;
    }
    for(ll i = 3; i <= sqrt(n); i+=2){
        while(n % i == 0){
            if(ans.empty()||ans.back().F!=i){ans.pb({i,1});}
            else{ans.back().S++;}
            n = n/i;
        }
    }
    if(n>2){if(ans.empty()||ans.back().F!=n){ans.pb({n,1});}else{ans.back().S++;}} 
    return ans;
}
