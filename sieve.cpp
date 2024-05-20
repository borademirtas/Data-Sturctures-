vector<bool> ok(n+1,1); ok[0]=ok[1]=0;
for(ll i = 2; i <= n; i++){
    if(!ok[i]){continue;}
    for(ll j = 2*i; j <= n; j+=i){
        ok[j]=false;
    }
}
