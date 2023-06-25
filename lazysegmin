struct segtree{
    struct node{
        int value,add;
    };
    int size;
    vector <node> tree;
 
    void init(int n){
        size=1;
        while(size<n) size*=2;
        tree.assign(size*2-1,{0,0});
    }
 
    void propagate(int x,int lx,int rx){
        if(rx-lx>1){
            int m=(lx+rx)/2;
            tree[2*x+1].value+=tree[x].add;
            tree[2*x+1].add+=tree[x].add;
            tree[2*x+2].value+=tree[x].add;
            tree[2*x+2].add+=tree[x].add;
            tree[x].add=0;
        }
    }
 
    void add(int l,int r,int v,int x,int lx,int rx){
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
 
    void add(int l,int r,int v){
        add(l,r,v,0,0,size);
    }
 
    int get(int l,int r,int x,int lx,int rx){
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
 
    int get(int l,int r){
        return get(l,r,0,0,size);
    }
};
