
// template <typename T, class Compare = std::less<T>>
// struct min_op {
//     Compare comp;
//     inline T operator()(const T& a, const T& b) const { return comp(a, b) ? a : b; }
// };
// template <typename T, class Compare = std::less<T>>
// struct max_op {
//     Compare comp;
//     inline T operator()(const T& a, const T& b) const { return comp(a, b) ? b : a; }
// };
// template <typename T>
// struct gcd_op {
//     inline T operator()(const T& a, const T& b) const { return std::gcd(a, b); }
// };
template <typename T, typename Op>
struct Segtree {
private:
    int n, si, lg;
    Op op;
    T e;
    std::vector<T> d;
    void update(int k) {
        d[k] = op(d[2 * k], d[2 * k + 1]);
    }
public:
    explicit Segtree(int n, T e) : Segtree(std::vector<T>(n, e), e) {}
    explicit Segtree(const std::vector<T>& v, T e) : n(v.size()), op(Op()), e(e) {
        si = 1;
        lg = 0;
        while (si < n) {
            lg++;
            si <<= 1;
        }
        d.assign(2 * si, e);
        std::copy(v.begin(), v.end(), d.begin() + si);
        for (int i = si - 1; i > 0; i--) update(i);
    }
    int size() const { return n; }
    T get(int p) const {
        assert(0 <= p && p < n);
        return d[si + p];
    }
    void set(int p, T x) {
        assert(0 <= p && p < n);
        p += si;
        d[p] = x;
        for (int i = 1; i <= lg; i++) {
            update(p >> i);
        }
    }
    T query(int l, int r) {
        assert(0 <= l && l <= r && r <= n);
        T le = e, ri = e;
        l += si; r += si;
        while (l < r) {
            if (l & 1) {
                le = op(le, d[l++]);
            }
            if (r & 1) {
                ri = op(d[--r], ri);
            }
            l >>= 1; r >>= 1;
        }
        return op(le, ri);
    }
    T query() const { return d[1]; }
    template <class F> int max_right(int l, F f) const {
        assert(0 <= l && l <= n);
        assert(f(e));
        if (l == n) return n;
        l += si;
        T sm = e;
        do {
            while (l % 2 == 0) l >>= 1;
            if (!f(op(sm, d[l]))) {
                while (l < si) {
                    l = 2 * l;
                    if (f(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - si;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return n;
    }
    template <class F> int min_left(int r, F f) const {
        assert(0 <= r && r <= n);
        assert(f(e));
        if (r == 0) return 0;
        r += si;
        T sm = e;
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!f(op(d[r], sm))) {
                while (r < si) {
                    r = 2 * r + 1;
                    if (f(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - si;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }
};
