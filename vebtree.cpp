//by mangolassi stolen from https://judge.yosupo.jp/submission/76699
template<int N>
class Bitset {
	private:
		constexpr static ull LM = (1ull<<32) - 1;
		constexpr static ull FM = ~0ull;
		constexpr static int H = (N + 63) >> 6;
		array<ull, H> bits;

		static constexpr ull getBit(int i, ull v = 1) { return v << (i & 63); }

		Bitset<N> shiftLeft(int d) {
			Bitset<N> res(-1);
			int s = min(d >> 6, H), r = d & 63;
			for (int i = 0; i < s; ++i) res.bits[i] = 0;
			if (r == 0) for (int i = s; i < H; ++i) res.bits[i] = bits[i - s];
			else {
				if (s < H) res.bits[s] = bits[0] << r;
				for (int i = s + 1; i < H; ++i) res.bits[i] = (bits[i - s] << r) | (bits[i-1 - s] >> (64 - r));
			}
			return res;
		}
		Bitset<N> shiftRight(int d) {
			Bitset<N> res(-1);
			int s = min(d >> 6, H), r = d & 63;
			for (int i = H-1; i >= H - (int)s; --i) res.bits[i] = 0;
			if (r == 0) for (int i = H-1 - (int)s; i >= 0; --i) res.bits[i] = bits[i + s];
			else {
				if (s < H) res.bits[H-1-s] = bits[H-1] >> r;
				for (int i = H-2 - (int)s; i >= 0; --i) res.bits[i] = (bits[i + s] >> r) | (bits[i+1 + s] << (64 - r));
			}
			return res;
		}

		// Lexicographic comparison on bits in bitset
		bool lexCompare(const Bitset<N>& rhs) const {
			for (int i = 0; i < H; ++i) {
				if (bits[i] != rhs.bits[i]) {
					ull tmp = bits[i] ^ rhs.bits[i];
					int j = __builtin_ctzll(tmp);
					if ((N & 63) && ((i << 6) + j >= N)) return false;
					return rhs.bits[i] & (1ull << j);
				}
			}
			return false;
		}
		// Numeric comparison on \sum_i 2^i bit[i]
		bool numCompare(const Bitset<N>& rhs) const {
			for (int i = H-1; i >= 0; --i) {
				if (bits[i] != rhs.bits[i]) {
					if ((N & 63) && (i == H-1)) {
						ull mask = ((1ull << (N & 63)) - 1);
						ull tmp1 = bits[H-1] & mask;
						ull tmp2 = rhs.bits[H-1] & mask;
						if (tmp1 != tmp2) return tmp1 < tmp2;
					} else return bits[i] < rhs.bits[i];
				}
			}
			return false;
		}
	public:
		void clear() { for (ull& v : bits) v = 0; }
		void set() { for (ull& v : bits) v = FM; }
		void flip() { for (ull& v : bits) v = ~v; }
		Bitset(int ini_v = 0) {
			if (ini_v == 0) clear();
			else if (ini_v == 1) set();
		}

		bool get(uint i) const { return bits[i>>6] & getBit(i); }
		void set(uint i, ull v) { bits[i>>6] = (bits[i>>6] & ~getBit(i)) | getBit(i, v); }
		void setZero(uint i) { bits[i>>6] &= ~getBit(i); }
		void setOne(uint i) { bits[i>>6] |= getBit(i); }
		
		// Sets bit[a + i] = ((v >> i) & 1) for 0 <= i <= b-a. MUST HAVE 0 <= v < 2^{b-a+1} AND 0 <= a <= b < min(a + 64, N)
		void setRange(uint a, uint b, ull v) {
			uint j = (a >> 6), r = (a & 63), len = b-a+1;
			ull mask = FM >> (64 - len);
			bits[j] = (bits[j] & ~(mask << r)) | (v << r);
			if ((b >> 6) > j) bits[j + 1] = (bits[j + 1] & ~(mask >> (64 - r))) | (v >> (64 - r));
		}

		// Returns v = \sum_{i = 0}^{b-a} 2^i * bit[a + i]. MUST HAVE 0 <= a <= b < min(a + 64, N)
		ull getRange(uint a, uint b) const {
			uint j = (a >> 6), r = (a & 63), len = b-a+1;
			ull mask = FM >> (64 - len);
			if ((b >> 6) <= j) return (bits[j] >> r) & mask;
			return ((bits[j] >> r) | (bits[j+1] << (64 - r))) & mask;
		}

		// Returns minimum a <= i <= b such that bit[i] = 1. Returns or b + 1 if none exist
		int findNext(int a, int b = N-1) const {
			int j = (a >> 6);
			ull tmp = bits[j] >> (a & 63);
			if (tmp != 0) return min(b + 1, a + __builtin_ctzll(tmp));
			for (++j; (j << 6) <= b; ++j) {
				if (bits[j]) return min(b + 1, (j << 6) + __builtin_ctzll(bits[j]));
			}
			return b + 1;
		}

		// Returns maximum i \in [a, b] such that bits[i] = 1, or a - 1 if none exist
		int findPrev(int b, int a = 0) const {
			int j = (b >> 6);
			ull tmp = bits[j] << (63 - (b & 63));
			if (tmp != 0) return (int)max(a, b+1 - __builtin_clzll(tmp)) - 1;
			for (--j; ((j + 1) << 6) > a; --j) {
				if (bits[j]) return (int)max(a, ((j + 1) << 6) - __builtin_clzll(bits[j])) - 1;
			}
			return (int)a - 1;
		}
		
		// Counts set bits in range [a, b]
		int count(int a = 0, int b = N-1) const {
			int res = 0;
			if (a & 63) res -= __builtin_popcountll(bits[a >> 6] << (64 - (a & 63)));
			if ((b + 1) & 63) res -= __builtin_popcountll(bits[b >> 6] >> ((b + 1) & 63));
			for (int j = (a >> 6); j <= (b >> 6); ++j) res += __builtin_popcountll(bits[j]);
			return res;
		}

		bool operator==(const Bitset<N>& rhs) const {
			for (int i = 0; i < H; ++i) {
				if (bits[i] != rhs.bits[i]) {
					return !(N & 63) || (i < H-1) || !((bits[i] ^ rhs.bits[i]) & ((1ull << (N & 63)) - 1));
				}
			}
			return false;
		}
		Bitset<N> operator~() const {
			Bitset<N> res(-1);
			for (int i = 0; i < H; ++i) res.bits[i] = ~bits[i];
			return res;
		}
		Bitset<N> operator|(const Bitset& rhs) const {
			Bitset<N> res(-1);
			for (int i = 0; i < H; ++i) res.bits[i] = bits[i] | rhs.bits[i];
			return res;
		}
		Bitset<N> operator&(const Bitset& rhs) const {
			Bitset<N> res(-1);
			for (int i = 0; i < H; ++i) res.bits[i] = bits[i] & rhs.bits[i];
			return res;
		}
		Bitset<N> operator^(const Bitset& rhs) const {
			Bitset<N> res(-1);
			for (int i = 0; i < H; ++i) res.bits[i] = bits[i] ^ rhs.bits[i];
			return res;
		}
		Bitset operator+(const Bitset& rhs) const {
			Bitset<N> res(-1);
			uint8_t carry = 0;
			for (int i = 0; i < H; ++i) carry = _addcarry_u64(carry, bits[i], rhs.bits[i], res.bits[i]);
			return res;
		}
		Bitset operator-(const Bitset& rhs) const {
			Bitset<N> res(-1);
			uint8_t borrow = 0;
			for (int i = 0; i < H; ++i) borrow = _subborrow_u64(borrow, bits[i], rhs.bits[i], res.bits[i]);
			return res;
		}
		
		/*
		// To make this work like a bitset
		bool operator<(const Bitset<N>& rhs) { return lexCompare(rhs); }
		Bitset<N> operator<<(int d) const { return leftShift(d); }
		Bitset<N> operator>>(int d) const { return rightShift(d); }
		*/
		
		/*
		// To make this work like a bigint
		bool operator<(const Bitset<N>& rhs) { return numCompare(rhs); }
		Bitset<N> operator<<(int d) const { return rightShift(d); }
		Bitset<N> operator>>(int d) const { return leftShift(d); }
		*/
};

// van Emde Boas tree. Maintains a set of integers in range [0, 2^B) and supports operations
//	findNext(i): returns minimum j >= i in set, or 2^B if none exist
// 	findPrev(i): returns maximum j <= i in set, or -1 if none exist
//	insert(i), erase(i): insert/erase i into the set
//	empty(): returns TRUE if the set is empty
//	clear(): empties the set
//	init(bts): inits the set, after the call i will be in the set if bts[i] = 1. bts should be a bitset, but can be a vector of 0/1
// All operations except empty, clear and init are O(log B) = O(log log 2^B) with good constants
template<int B, typename ENABLE = void>
class VEBTree {
	private:
		const static int K = B / 2, R = (B + 1) / 2, M = (1 << B);
		const static int S = 1 << K, MASK = (1 << R) - 1;
		array<VEBTree<R>, S> ch;
		VEBTree<K> act;
		int mi, ma;
	public:
		bool empty() const { return ma < mi; }
		
		int findNext(int i) const {
			if (i <= mi) return mi;
			if (i > ma) return M;
			
			int j = i >> R, x = i & MASK;
			int res = ch[j].findNext(x);
			if (res <= MASK) return (j << R) + res;
			
			j = act.findNext(j + 1);
			return (j >= S) ? ma : ((j << R) + ch[j].findNext(0));
		}
		int findPrev(int i) const {
			if (i >= ma) return ma;
			if (i < mi) return -1;
			
			int j = i >> R, x = i & MASK;
			int res = ch[j].findPrev(x);
			if (res >= 0) return (j << R) + res;
			
			j = act.findPrev(j - 1);
			return (j < 0) ? mi : ((j << R) + ch[j].findPrev(MASK));
		}
		void insert(int i) {
			if (i <= mi) {
				if (i == mi) return;
				swap(mi, i);
				if (i == M) ma = mi; // we were empty
				if (i >= ma) return; // we had mi == ma
			} else if (i >= ma) {
				if (i == ma) return;
				swap(ma, i);
				if (i <= mi) return; // we had mi == ma
			}
			int j = i >> R;
			if (ch[j].empty()) act.insert(j);
			ch[j].insert(i & MASK);
		}
		void erase(int i) {
			if (i <= mi) {
				if (i < mi) return;
				i = mi = findNext(mi + 1);
				if (i >= ma) {
					if (i > ma) ma = -1; // we had mi == ma
					return; // after erase we have mi == ma
				}
			} else if (i >= ma) {
				if (i > ma) return;
				i = ma = findPrev(ma - 1);
				if (i <= mi) return; // after erase we have mi == ma
			}
			int j = i >> R;
			ch[j].erase(i & MASK);
			if (ch[j].empty()) act.erase(j);
		}

		void clear() {
			mi = M, ma = -1;
			act.clear();
			for (int i = 0; i < S; ++i) ch[i].clear();
		}
		template<class T>
		void init(const T& bts, int shift = 0, int s0 = 0, int s1 = 0) {
			s0 = -shift + bts.findNext(shift + s0, shift + M-1 - s1);
			s1 = M-1 - (-shift + bts.findPrev(shift + M-1-s1, shift + s0));
			if (s0 + s1 >= M) clear();
			else {
				act.clear();
				mi = s0, ma = M-1 - s1;
				++s0; ++s1;
				for (int j = 0; j < S; ++j) {
					ch[j].init(bts, shift + (j << R), max(0, s0 - (j << R)), max(0, s1 - ((S-1-j) << R)));
					if (! ch[j].empty()) act.insert(j);
				}
			}
		}
};

template<int B>
class VEBTree<B, enable_if_t<(B <= 6)>> {
	private:
		const static int M = (1 << B);
		ull act;
	public:
		bool empty() const { return !act; }
		void clear() { act = 0; }

		int findNext(int i) const {
			return ((i < M) && (act >> i)) ? i + __builtin_ctzll(act >> i) : M;
		}
		int findPrev(int i) const {
			return ((i != -1) && (act << (63 - i))) ? i - __builtin_clzll(act << (63 - i)) : -1;
		}
		void insert(int i) { act |= 1ull << i; }
		void erase(int i) { act &= ~(1ull << i); }
		
		template<class T>
		void init(const T& bts, int shift = 0, int s0 = 0, int s1 = 0) {
			if (s0 + s1 >= M) act = 0;
			else act = bts.getRange(shift + s0, shift + M-1-s1) << s0;
		}
};

struct FastIO {
	private:
		const static int K = 1 << 15;
		array<array<char, 4>, 10000> num_strs;
		array<int, 10000> skip_chs;
		array<char, K> in_buf, out_buf;
		int in_fd, out_fd, in_x = K, out_x = 0;

		void refillBuffer() {
			if (in_x < K) {
				memmove(in_buf.data(), in_buf.data() + in_x, K - in_x);
				in_x = K - in_x;
			} else in_x = 0;
			read(in_fd, in_buf.data() + in_x, K - in_x);
			in_x = 0;
		}
		void flush() {
			if (out_x) write(out_fd, out_buf.data(), out_x);
			out_x = 0;
		}
	public:
		FastIO(FILE* in = stdin, FILE* out = stdout) : in_fd(fileno(in)), out_fd(fileno(out)) {
			for (int x = 0; x < num_strs.size(); ++x) {
				skip_chs[x] = 0;
				for (int i = 0, tmp = x; i < 4; ++i, tmp /= 10) {
					if (tmp == 0 && (x > 0 || i > 0)) skip_chs[x] = max(skip_chs[x], 4-i);
					num_strs[x][3-i] = ('0' + (tmp % 10));
				}
			}
		}
		~FastIO() { flush(); close(out_fd); }

		int readInt() {
			if (in_x >= K / 2) refillBuffer();
			while(in_buf[in_x] < '-') ++in_x;

			int res = 0, sg = 1;
			if (in_buf[in_x] == '-') sg = -1, ++in_x;
			for (; in_buf[in_x] > '-'; ++in_x) res = (10 * res + (in_buf[in_x] - '0'));
			return sg * res;
		}
		template<int N>
		Bitset<N> readBinaryString() {
			if (in_x >= K / 2) refillBuffer();
			while(in_buf[in_x] < '0' || in_buf[in_x] > '1') ++in_x;

			int j = 0;
			Bitset<N> res;
			while('0' <= in_buf[in_x] && in_buf[in_x] <= '1') {
				res.set(j, in_buf[in_x] == '1');
				++in_x, ++j;
				if (in_x >= K / 2) refillBuffer();
			}
			return res;
		}
		void printChar(char c) {
			out_buf[out_x] = c;
			++out_x;
			if (out_x >= K / 2) flush();
		}
		// Works for |num| < 1e8. Add additional ifs for larger |num|
		void printInt(int num) {
			if (num < 0) {
				out_buf[out_x] = '-';
				++out_x;
				num *= -1;
			}
			if (num >= 10000) {
				int hi = num / 10000;
				int lo = num % 10000;
				for (int i = skip_chs[hi]; i < 4; ++i, ++out_x) out_buf[out_x] = num_strs[hi][i];
				for (int i = 0; i < 4; ++i, ++out_x) out_buf[out_x] = num_strs[lo][i];
			} else {
				for (int i = skip_chs[num]; i < 4; ++i, ++out_x) out_buf[out_x] = num_strs[num][i];
			}
			if (out_x >= K / 2) flush();
		}
};
