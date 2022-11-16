template<class T>
class fenwick {
private:
    int size;
    vector<T> bit;
    vector<T> arr;
public:
    fenwick(int size) : size(size), bit(size + 1), arr(size) { }
    void set(int ind, int val) {
        add(ind, val - arr[ind]);
    }
    void add(int ind, int val) {
        arr[ind] += val;
        ind++;
        for (; ind <= size; ind += ind & -ind) {
            bit[ind] += val;
        }
    }
    T pre(int ind) {
        ind++;
        T total = 0;
        for (; ind > 0; ind -= ind & -ind) {
            total += bit[ind];
        }
        return total;
    }
};
