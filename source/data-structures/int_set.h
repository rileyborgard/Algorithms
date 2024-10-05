
template<int N>
struct int_set {
    int lg;
    int n_blocks;
    bitset<N> b;
    vector<uint64_t> a;
    bit() {
        n_blocks = (N + 63) / 64;
        lg = 0;
        while(2 * (1 << lg) < n_blocks) lg++;
        a.assign(n_blocks, 0);
    }
    void build() {

    }
    void _add(int i, int x) {
        while(i < n) {
            a[i] = a[i] + x;
            i += i & -i;
        }
    }
    T _get(int i) const {
        T x = T();
        while(i > 0) {
            x = x + a[i];
            i -= i & -i;
        }
        return x;
    }
    int _lower_bound(int val) {
        int i = 0;
        int sum = 0;
        for(int k = lg; k >= 0; k--) {
            if(i + (1 << k) < n && sum + a[i + (1 << k)] < val) {
                i += (1 << k);
                sum = sum + a[i];
            }
        }
        return i + 1;
    }
};

istream& operator>>(istream& in, int_set s) {
    in >> s.b;
    s.build();
    return in;
}
