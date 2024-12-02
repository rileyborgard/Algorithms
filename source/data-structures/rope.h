
template <typename T, typename Op>
struct rope {
public:
    struct node {
        T x;
        int cnt;
        node *l, *r, *p;
        node(T x, int cnt, node* l = nullptr, node* r = nullptr, node* p = nullptr) : x(x), cnt(cnt), l(l), r(r), p(p) {}
        bool leaf() const { return !l && !r; }
    };
private:
    int n;
    Op op;
    T e;
    void update(node* a) {
        a->p = nullptr;
        if (a->leaf()) return;
        if (a->l) a->l->p = a;
        if (a->r) a->r->p = a;
        if (!a->l) {
            a->x = a->r->x;
            a->cnt = a->r->cnt;
            return;
        }
        if (!a->r) {
            a->x = a->l->x;
            a->cnt = a->l->cnt;
            return;
        }
        a->x = op(a->l->x, a->r->x);
        a->cnt = a->l->cnt + a->r->cnt;
    }
    node* make_internal(node* l, node* r) {
        node* res = new node(e, 0, l, r);
        return update(res), res;
    }
    bool balanced(int cnt1, int cnt2) const {
        #warning TODO: Optimize
        const float alpha = 0.2;
        return cnt1 >= alpha * cnt2 && cnt2 >= alpha * cnt1;
    }
    node* rebalance(node* a) {
        if (!a || a->leaf()) return a;
        assert(a->l);
        assert(a->r);
        if (balanced(a->l->cnt, a->r->cnt)) return a;
        if (a->l->cnt < a->r->cnt) {
            // left smaller
            assert(a->r->l);
            assert(a->r->r);

            if (balanced(a->l->cnt, a->r->l->cnt) && balanced(a->l->cnt + a->r->l->cnt, a->r->r->cnt)) {
                // single left rotation
                node* x = a->l;
                node* y = a->r->l;
                node* z = a->r->r;
                node* l = a->r;
                l->l = x;
                l->r = y;
                a->l = l;
                a->r = z;
                update(l);
                update(a);
                return a;
            }

            // double rotation
            assert(!a->r->l->leaf());
            node* x = a->l;
            node* y = a->r->l->l;
            node* z = a->r->l->r;
            node* w = a->r->r;
            assert(x);
            assert(y);
            assert(z);
            assert(w);
            node* l = a->r->l;
            node* r = a->r;
            l->l = x;
            l->r = y;
            r->l = z;
            r->r = w;
            a->l = l;
            a->r = r;
            update(l);
            assert(balanced(l->l->cnt, l->r->cnt));
            update(r);
            assert(balanced(r->l->cnt, r->r->cnt));
            update(a);
            assert(balanced(l->cnt, r->cnt));
            return a;
        } else {
            assert(a->l->l);
            assert(a->l->r);
            if (balanced(a->r->cnt, a->l->r->cnt) && balanced(a->r->cnt + a->l->r->cnt, a->l->l->cnt)) {
                // single right rotation
                node* x = a->l->l;
                node* y = a->l->r;
                node* z = a->r;
                node* r = a->l;
                r->l = y;
                r->r = z;
                a->l = x;
                a->r = r;
                update(r);
                update(a);
                return a;
            }
            // double rotation
            assert(a->l->r);
            assert(!a->l->r->leaf());
            node* x = a->l->l;
            node* y = a->l->r->l;
            node* z = a->l->r->r;
            node* w = a->r;
            assert(x);
            assert(y);
            assert(z);
            assert(w);
            node* l = a->l->r;
            node* r = a->l;
            l->l = x;
            l->r = y;
            r->l = z;
            r->r = w;
            a->l = l;
            a->r = r;
            update(l);
            assert(balanced(l->l->cnt, l->r->cnt));
            update(r);
            assert(balanced(r->l->cnt, r->r->cnt));
            update(a);
            assert(balanced(l->cnt, r->cnt));
            return a;
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
            if (p->r == a && p->l) {
                x = op(x, p->l->x);
            }
            a = p;
        }
        return x;
    }
    int index_of(node* a) const {
        int idx = 0;
        while (a->p) {
            node* p = a->p;
            if (p->r == a && p->l) {
                idx += p->l->cnt;
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
        T xl = a->l ? op(x, a->l->x) : x;
        if (f(xl)) {
            node* ar = nullptr;
            splitf(a->r, ar, r, f, xl);
            l = merge(a->l, ar);
            delete a;
        } else {
            node* al = nullptr;
            splitf(a->l, l, al, f, x);
            r = merge(al, a->r);
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
        int lcnt = a->l ? a->l->cnt : 0;
        if (k >= lcnt) {
            node* ar = nullptr;
            split(a->r, ar, r, k - lcnt);
            l = merge(a->l, ar);
            delete a;
        } else {
            node* al = nullptr;
            split(a->l, l, al, k);
            r = merge(al, a->r);
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
            a->r = merge(a->r, b);
            update(a);
            return rebalance(a);
        } else {
            b->l = merge(a, b->l);
            update(b);
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
        if (a->l) for_each(a->l, f);
        if (a->r) for_each(a->r, f);
    }
};
