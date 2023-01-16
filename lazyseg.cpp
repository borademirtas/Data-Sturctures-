template<class T> struct LSegTree {

	int N; vector<T> t, lz; T U=-1e18;

	T F(T i, T j) { return max(i,j); } LSegTree() {}

	LSegTree(int N) : N(N), t(4*(N+1),U), lz(4*(N+1),0) {}

	void pull(int i) { t[i] = F(t[i*2],t[i*2+1]); }

	void push(int i, int l, int r) {

		t[i]+=lz[i];

		if(l!=r) lz[i*2]+=lz[i], lz[i*2+1]+=lz[i];

		lz[i]=0; }

	void build(vector<ll> &v) { build(v,1,0,N); }

	void build(vector<ll> &v, int i, int l, int r) {

		if(l==r) { t[i]=v[l]; return; } int m=(l+r)/2;

		build(v,i*2,l,m); build(v,i*2+1,m+1,r); pull(i);

	}

	void upd(int L, int R, T v) { upd(L,R,v,1,0,N); }

	void upd(int L, int R, T v, int i, int l, int r) {

		push(i,l,r); if(R<l || L>r) return;

		if(L<=l && R>=r) { lz[i]+=v; push(i,l,r); return; }

		int m=(l+r)/2; upd(L,R,v,i*2,l,m);

		upd(L,R,v,i*2+1,m+1,r); pull(i);

	}

	T qry(int L, int R) { return qry(L,R,1,0,N); }

	T qry(int L, int R, int i, int l, int r) {

		push(i,l,r); if(R<l || L>r) return U;

		if(L<=l && R>=r) return t[i]; int m=(l+r)/2;

		return F(qry(L,R,i*2,l,m), qry(L,R,i*2+1,m+1,r));

	}

};

