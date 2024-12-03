
template <typename T, typename Op>
struct rope {
public:
    struct node {
        T x;
        int cnt;
        node *c[2], *p;
        node(T x, int cnt, node* l = nullptr, node* r = nullptr, node* p = nullptr) : x(x), cnt(cnt), p(p) { c[0] = l; c[1] = r; }
        inline bool leaf() const { return !c[0] && !c[1]; }
    };
private:
    int n;
    Op op;
    T e;
    void update(node* a) {
        a->p = nullptr;
        if (a->leaf()) return;
        a->c[0]->p = a->c[1]->p = a;
        a->x = op(a->c[0]->x, a->c[1]->x);
        a->cnt = a->c[0]->cnt + a->c[1]->cnt;
    }
    node* make_internal(node* l, node* r) {
        node* res = new node(e, 0, l, r);
        return update(res), res;
    }
    bool balanced(int cnt1, int cnt2) const {
        const float alpha = 0.2;
        return cnt1 >= alpha * cnt2 && cnt2 >= alpha * cnt1;
    }
    template <bool b> node* zig(node* a) {
        node* r = a->c[b];
        a->c[b] = r->c[!b];
        r->c[!b] = a;
        return update(a), update(r), r;
    }
    template <bool b> node* zigzag(node* a) {
        node* r = a->c[b], *l = r->c[!b];
        a->c[b] = l->c[!b];
        r->c[!b] = l->c[b];
        l->c[!b] = a;
        l->c[b] = r;
        return update(a), update(r), update(l), l;
    }
    node* rebalance(node* a) {
        if (!a || a->leaf()) return a;
        node *l = a->c[0], *r = a->c[1];
        if (balanced(l->cnt, r->cnt)) return update(a), a;
        if (l->cnt < r->cnt) {
            if (balanced(l->cnt, r->c[0]->cnt) && balanced(l->cnt + r->c[0]->cnt, r->c[1]->cnt)) {
                return zig<1>(a);
            } else {
                return zigzag<1>(a);
            }
        } else {
            if (balanced(r->cnt, l->c[1]->cnt) && balanced(r->cnt + l->c[1]->cnt, l->c[0]->cnt)) {
                return zig<0>(a);
            } else {
                return zigzag<0>(a);
            }
        }
    }
public:
    explicit rope(T e) : n(0), op(Op()), e(e) {}
    int size() const { return n; }
    node* make(T x) { return new node(x, 1); }
    T get(node* a) const { return a ? a->x : e; }
    node* root(node* a) const {
        if (!a) return nullptr;
        while (a->p) a = a->p;
        return a;
    }
    T pref(node* a) const {
        T x = e;
        while (a->p) {
            node* p = a->p;
            if (p->c[1] == a && p->c[0]) {
                x = op(x, p->c[0]->x);
            }
            a = p;
        }
        return x;
    }
    int index_of(node* a) const {
        int idx = 0;
        while (a->p) {
            node* p = a->p;
            if (p->c[1] == a && p->c[0]) {
                idx += p->c[0]->cnt;
            }
            a = p;
        }
        return idx;
    }
    template <class F> void splitf(node* a, node*& l, node*& r, F f) {
        return splitf(a, l, r, f, e);
    }
    template <class F> void splitf(node* a, node*& l, node*& r, F f, T x) {
        l = r = nullptr;
        if (!a) return;
        if (a->leaf()) {
            (f(op(x, a->x)) ? l : r) = a;
            return;
        }
        T xl = a->c[0] ? op(x, a->c[0]->x) : x;
        if (f(xl)) {
            node* ar = nullptr;
            splitf(a->c[1], ar, r, f, xl);
            l = merge(a->c[0], ar);
            delete a;
        } else {
            node* al = nullptr;
            splitf(a->c[0], l, al, f, x);
            r = merge(al, a->c[1]);
            delete a;
        }
    }
    void split(node* a, node*& l, node*& r, int k) {
        l = r = nullptr;
        if (!a) return;
        if (a->leaf()) {
            (k > 0 ? l : r) = a;
            return;
        }
        int lcnt = a->c[0] ? a->c[0]->cnt : 0;
        if (k >= lcnt) {
            node* ar = nullptr;
            split(a->c[1], ar, r, k - lcnt);
            l = merge(a->c[0], ar);
            delete a;
        } else {
            node* al = nullptr;
            split(a->c[0], l, al, k);
            r = merge(al, a->c[1]);
            delete a;
        }
    }
    node* merge(node* a, node* b) {
        if (!a) return b;
        if (!b) return a;
        if (balanced(a->cnt, b->cnt)) {
            return make_internal(a, b);
        }
        if (a->cnt > b->cnt) {
            a->c[1] = merge(a->c[1], b);
            return rebalance(a);
        } else {
            b->c[0] = merge(a, b->c[0]);
            return rebalance(b);
        }
    }
    node* merge(const std::vector<node*>& v) {
        return merge(v, 0, v.size());
    }
    node* merge(const std::vector<node*>& v, int l, int r) {
        assert(0 <= l && l <= r && r <= (int) v.size());
        if (l == r) return nullptr;
        if (r - l == 1) return v[l];
        int m = l + (r - l) / 2;
        return merge(merge(v, l, m), merge(v, m, r));
    }
    template <class F> void for_each(node* a, F f) {
        if (!a) return;
        if (a->leaf()) f(a->x);
        if (a->c[0]) for_each(a->c[0], f);
        if (a->c[1]) for_each(a->c[1], f);
    }
};
