
template<typename T>
struct bit {
    int n, lg;
    vector<T> a;
    bit(int n) : n(n) {
        a.assign(n, T());
        lg = 0;
        while(2 * (1u << lg) < n) lg++;
    }
    void add(int i, T x) {
        while(i < n) {
            a[i] = a[i] + x;
            i += i & -i;
        }
    }
    T get(int i) {
        T x = T();
        while(i > 0) {
            x = x + a[i];
            i -= i & -i;
        }
        return x;
    }
    int lower_bound(T val) {
        int i = 0;
        T sum = T();
        for(int k = lg; ; k--) {
            if(i + (1 << k) < n && sum + a[i + (1 << k)] < val) {
                i += (1 << k);
                sum = sum + a[i];
            }
            if(k == 0) return i + 1;
        }
    }
};
