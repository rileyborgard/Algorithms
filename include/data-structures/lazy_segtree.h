
template <typename T, class Compare = std::less<T>>
struct min_op {
    Compare comp;
    inline T operator()(const T& a, const T& b) const { return comp(a, b) ? a : b; }
};
template <typename T, class Compare = std::less<T>>
struct max_op {
    Compare comp;
    inline T operator()(const T& a, const T& b) const { return comp(a, b) ? b : a; }
};
template <typename T>
struct gcd_op {
    inline T operator()(const T& a, const T& b) const { return std::gcd(a, b); }
};
template <typename T, typename Op, typename F, typename Apply, typename Compose>
struct lazy_segtree {
private:
    int n, si, lg;
    Op op;
    Apply apply;
    Compose compose;
    T e;
    F id;
    std::vector<T> d;
    std::vector<F> z;
    void upd(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
    void all_apply(int k, F f) {
        d[k] = apply(f, d[k]);
        if (k < si) z[k] = compose(f, z[k]);
    }
    void push(int k) {
        all_apply(2 * k, z[k]);
        all_apply(2 * k + 1, z[k]);
        z[k] = id;
    }
public:
    explicit lazy_segtree(int n, T e, F id) : lazy_segtree(std::vector<T>(n, e), e, id) {}
    explicit lazy_segtree(const std::vector<T>& v, T e, F id) : n(v.size()), e(e), id(id) {
        si = 1;
        lg = 0;
        while (si < n) {
            lg++;
            si <<= 1;
        }
        d.assign(2 * si, e);
        z.assign(si, id);
        std::copy(v.begin(), v.end(), d.begin() + si);
        for (int i = si - 1; i >= 1; i--) upd(i);
    }
    int size() const { return n; }
    T get(int p) {
        assert(0 <= p && p < n);
        p += si;
        for (int i = lg; i >= 1; i--) push(p >> i);
        return d[p];
    }
    void set(int p, T x) {
        assert(0 <= p && p < n);
        p += si;
        for (int i = lg; i >>= 1; i--) push(p >> i);
        d[p] = x;
        for (int i = 1; i <= lg; i++) upd(p >> i);
    }
    T query(int l, int r) {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) return e;
        l += si; r += si;
        for (int i = lg; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
        T le = e, ri = e;
        while (l < r) {
            if (l & 1) le = op(le, d[l++]);
            if (r & 1) ri = op(d[--r], ri);
            l >>= 1; r >>= 1;
        }
        return op(le, ri);
    }
    T query() const { return d[1]; }
    void update(int p, F f) {
        assert(0 <= p && p < n);
        p += si;
        for (int i = lg; i >= 1; i--) push(p >> i);
        d[p] = apply(f, d[p]);
        for (int i = 1; i <= lg; i++) upd(p >> i);
    }
    void update(int l, int r, F f) {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) return;
        l += si; r += si;
        for (int i = lg; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
        int l2 = l, r2 = r;
        while (l < r) {
            if (l & 1) all_apply(l++, f);
            if (r & 1) all_apply(--r, f);
            l >>= 1; r >>= 1;
        }
        l = l2;
        r = r2;
        for (int i = 1; i <= lg; i++) {
            if (((l >> i) << i) != l) upd(l >> i);
            if (((r >> i) << i) != r) upd((r - 1) >> i);
        }
    }
    template <class G> int max_right(int l, G g) {
        assert(0 <= l && l <= n);
        assert(g(e));
        if (l == n) return n;
        l += si;
        for (int i = lg; i >= 1; i--) push(l >> i);
        T sm = e;
        do {
            while (l % 2 == 0) l >>= 1;
            if (!g(op(sm, d[l]))) {
                while (l < si) {
                    push(l);
                    l = 2 * l;
                    if (g(op(sm, d[l]))) {
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
    template <class G> int min_left(int r, G g) {
        assert(0 <= r && r <= n);
        assert(g(e));
        if (r == 0) return 0;
        r += si;
        for (int i = lg; i >= 1; i--) push((r - 1) >> i);
        T sm = e;
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!g(op(d[r], sm))) {
                while (r < si) {
                    push(r);
                    r = 2 * r + 1;
                    if (g(op(d[r], sm))) {
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
