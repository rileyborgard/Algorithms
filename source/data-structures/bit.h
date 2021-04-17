
template<typename T>
struct bit {
    size_t n, lg;
    vector<T> a;
    bit(size_t n) : n(n) {
        a.assign(n, T());
        lg = 0;
        while(2 * (1u << lg) < n) lg++;
    }
    void add(size_t i, T x) {
        while(i < n) {
            a[i] = a[i] + x;
            i += i & -i;
        }
    }
    T get(size_t i) {
        T x = T();
        while(i > 0) {
            x = x + a[i];
            i -= i & -i;
        }
        return x;
    }
    size_t lower_bound(T val) {
        size_t i = 0;
        T sum = T();
        for(size_t k = lg; ; k--) {
            if(i + (1 << k) < n && sum + a[i + (1 << k)] < val) {
                i += (1 << k);
                sum = sum + a[i];
            }
            if(k == 0) return i + 1;
        }
    }
};
