
template <typename T>
struct segtree_4ary {
private:
    int n, si, lg;
    T e;
    std::vector<T> d;
    void update(int k) {
        d[k] = std::min({d[4 * k + 1], d[4 * k + 2], d[4 * k + 3], d[4 * k + 4]});
    }
public:
    explicit segtree_4ary(int n) : segtree(std::vector<T>(n, std::numeric_limits<T>::max())) {}
    explicit segtree_4ary(const std::vector<T>& v) : n(v.size()) {
        e = std::numeric_limits<T>::max();
        si = 1;
        lg = 0;
        while (si < n) {
            lg++;
            si <<= 2;
        }
        d.assign(2 * si, e);
        std::copy(v.begin(), v.end(), d.begin() + si - 1);
        for (int i = si - 2; i >= 0; i--) update(i);
    }
    int size() const { return n; }
    T get(int p) const {
        assert(0 <= p && p < n);
        return d[si - 1 + p];
    }
    void decrease_key(int p, T x) {
        assert(0 <= p && p < n);
        p += si - 1;
        while (true) {
            if (d[p] <= x) break;
            d[p] = x;
            if (p == 0) break;
            p = (p - 1) >> 2;
        }
    }
    void set(int p, T x) {
        assert(0 <= p && p < n);
        p += si - 1;
        d[p] = x;
        while (p > 0) {
            p = (p - 1) >> 2;
            update(p);
        }
    }
    // T query(int l, int r) {
    //     assert(0 <= l && l <= r && r <= n);
    //     T le = e, ri = e;
    //     l += si; r += si;
    //     while (l < r) {
    //         if (l & 1) le = op(le, d[l++]);
    //         if (r & 1) ri = op(d[--r], ri);
    //         l >>= 1; r >>= 1;
    //     }
    //     return op(le, ri);
    // }
    T query() const { return d[0]; }
};
