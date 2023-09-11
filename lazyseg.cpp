struct segtree{
    struct node{
        ll value,add;
    };
    ll size;
    vector <node> tree;
 
    void init(ll n){
        size=1;
        while(size<n) size*=2;
        tree.assign(size*2-1,{0LL,0LL});
    }
 
    void propagate(ll x,ll lx,ll rx){
        if(rx-lx>1){
            int m=(lx+rx)/2;
            tree[2*x+1].value+=tree[x].add;
            tree[2*x+1].add+=tree[x].add;
            tree[2*x+2].value+=tree[x].add;
            tree[2*x+2].add+=tree[x].add;
            tree[x].add=0;
        }
    }
 
    void add(ll l,ll r,ll v,ll x,ll lx,ll rx){
        propagate(x,lx,rx);
        if(l<=lx && rx<=r){
            tree[x].value+=v;
            tree[x].add+=v;
            return;
        }
        if(l>=rx || r<=lx){
            return;
        }
        int m=(lx+rx)/2;
        add(l,r,v,2*x+1,lx,m);
        add(l,r,v,2*x+2,m,rx);
        tree[x].value=min(tree[2*x+1].value,tree[2*x+2].value);
    }
 
    void add(ll l,ll r,ll v){
        add(l,r,v,0LL,0LL,size);
    }
 
    ll get(ll l,ll r,ll x,ll lx,ll rx){
        propagate(x,lx,rx);
        if(l<=lx && rx<=r){
            return tree[x].value;
        }
        if(l>=rx || r<=lx){
            return INT_MAX;
        }
        int m=(lx+rx)/2;
        int m1=get(l,r,2*x+1,lx,m);
        int m2=get(l,r,2*x+2,m,rx);
        return min(m1,m2);
    }
 
    ll get(ll l,ll r){
        return get(l,r,0LL,0LL,size);
    }
};
