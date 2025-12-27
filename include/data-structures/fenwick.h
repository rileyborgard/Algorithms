
template<typename T, typename Op = std::plus<T>>
struct Fenwick {
    int n, lg;
    T e;
    std::vector<T> a;
    Op op;
    Fenwick(int n, T e = T()) : n(n), e(e), a(n, e), op(Op()) {
        lg = 0;
        while(2 * (1 << lg) < n) lg++;
    }
    void add(int i, T x) {
        assert(i > 0);
        while(i < n) {
            a[i] = op(a[i], x);
            i += i & -i;
        }
    }
    T get(int i) {
        T x = e;
        while(i > 0) {
            x = op(x, a[i]);
            i -= i & -i;
        }
        return x;
    }
    int lower_bound(T val) {
        int i = 0;
        T sum = e;
        for(int k = lg; k >= 0; k--) {
            if(i + (1 << k) < n && sum + a[i + (1 << k)] < val) {
                i += (1 << k);
                sum = op(sum, a[i]);
            }
        }
        return i + 1;
    }
};
