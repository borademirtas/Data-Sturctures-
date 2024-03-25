struct lazy_segment_tree{
    using T = ll;
    using U = array<ll, 2>;
    T value_identity = 0;
    U update_identity = array<ll, 2>({1, 0});
    T join(T x, T y){
        return x + y;
    }
    void assign(int length, U u, T& x){
        auto& [a, b] = u;
        x = a * x + b * length;
    }
    void lazy_assign(U u1, U& u2){
        auto &[a, b] = u1; // new update
        auto [c, d] = u2; // old update;
        u2 = array<ll, 2>({a * c, a * d + b});
    }
    vector<T> st;
    vector<U> lazy;
    int n;
    lazy_segment_tree(int _n) : st(4 * _n, value_identity), lazy(4 * _n, update_identity), n(_n) {}
    int ql = -1, qr = -1;
    T query(int l, int r){
        ql = l, qr = r;
        return query_impl(1, 0, n - 1);
    }
    void push(int v, int length){
        if(v >= 2 * n) return;
        int left_length = (length + 1) / 2;
        int right_length = length / 2;
        lazy_assign(lazy[v], lazy[2 * v]);
        assign(left_length, lazy[v], st[2 * v]);
        lazy_assign(lazy[v], lazy[2 * v + 1]);
        assign(right_length, lazy[v], st[2 * v + 1]);
        lazy[v] = update_identity;
        //assert(st[v] == join(st[2 * v], st[2 * v + 1]));
    }
    T query_impl(int v, int l, int r){
        int length = r - l + 1;
        push(v, length);
        int mid = (l + r) / 2;
        if(qr < l || ql > r) return value_identity;
        if(ql <= l && r <= qr) return st[v];
        return join(query_impl(2 * v, l, mid), query_impl(2 * v + 1, mid + 1, r));
    }
    U qu;
    void update(int l, int r, U u){
        ql = l, qr = r, qu = u;
        update_impl(1, 0, n - 1);
    }
    void update_impl(int v, int l, int r){
        int length = r - l + 1;
        push(v, length);
        if(qr < l || ql > r) return;
        if(ql <= l && r <= qr){
            lazy[v] = qu;
            assign(length, lazy[v], st[v]);
            return;
        }
        int mid = (l + r) / 2;
        update_impl(2 * v, l, mid);
        update_impl(2 * v + 1, mid + 1, r);
        st[v] = join(st[2 * v], st[2 * v + 1]);
    }
};
// 1 = increment, 0 = set

