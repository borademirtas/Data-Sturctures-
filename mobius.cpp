    vll mob(mx+1), lpf(mx+1);
    for(ll i = 2; i <= mx; i++){
        if(!lpf[i]){for(ll j = i; j <= mx; j+=i){if(!lpf[j]){lpf[j]=i;}}}
    }
    for(ll i = 1; i <= mx; i++){
        if(i==1){mob[i]=1;}
        else{
            if(lpf[i/lpf[i]]==lpf[i]){mob[i]=0;}
            else{mob[i]=-1*mob[i/lpf[i]]};
        }
    }
