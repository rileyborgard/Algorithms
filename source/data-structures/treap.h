
template <typename T>
struct treap {
public:
    struct node {
        T value;
        int cnt, y;
        node *l, *r, *p;
        node(T value, int cnt, int y, node* l = nullptr, node* r = nullptr, node* p = nullptr) : value(value), cnt(cnt), y(y), l(l), r(r), p(p) {}
    };
private:
    std::mt19937 rng;
    int rand() {
        std::uniform_int_distribution<int> uni(0, INT_MAX);
        return uni(rng);
    }
    void update(node* a) {
        assert(a);
        a->cnt = 1 + size_of(a->l) + size_of(a->r);
    }
    void split(node* a, node*& l, node*& r, int k) {
        if (!a) return void(l = r = nullptr);
        if (size_of(a->l) < k) {
            split(a->r, a->r, r, k - size_of(a->l) - 1);
            if (a->r) a->r->p = a;
            l = a;
            update(a);
        } else {
            split(a->l, l, a->l, k);
            if (a->l) a->l->p = a;
            r = a;
            update(a);
        }
    }
    node* join(const std::vector<node*>& v, int l, int r) {
        assert(0 <= l && l <= r && r <= (int) v.size());
        if (l == r) return nullptr;
        if (r - l == 1) return v[l];
        int m = l + (r - l) / 2;
        return join(join(v, l, m), join(v, m, r));
    }
public:
    explicit treap(int seed = std::chrono::steady_clock::now().time_since_epoch().count()) : rng(seed) {}
    node* make(T value) { return new node(value, 1, rand()); }
    int size_of(node* a) const {
        return a ? a->cnt : 0;
    }
    node* root(node* a) const {
        if (!a) return nullptr;
        while (a->p) a = a->p;
        return a;
    }
    int index_of(node* a) const {
        assert(a);
        int idx = size_of(a->l);
        while (a->p) {
            node* p = a->p;
            if (p->r == a) idx += 1 + size_of(p->l);
            a = p;
        }
        return idx;
    }
    template <class F> std::pair<node*, int> lower_bound(node* a, F f) {
        int idx = 0;
        node* p = nullptr;
        while (a) {
            if (f(a)) {
                idx += 1 + size_of(a->l);
                a = a->r;
            } else {
                p = a;
                a = a->l;
            }
        }
        return {p, idx};
    }
    node* at(node* a, int k) const {
        while (a) {
            int s = size_of(a->l);
            if (k == s) {
                return a;
            } else if (k < s) {
                a = a->l;
            } else {
                k -= 1 + s;
                a = a->r;
            }
        }
        return nullptr;
    }
    std::pair<node*, node*> split(node* a, int k) {
        node *l, *r;
        split(a, l, r, k);
        if (l) l->p = nullptr;
        if (r) r->p = nullptr;
        return {l, r};
    }
    node* join(node* a, node* b) {
        if (!a) return b;
        if (!b) return a;
        if (a->y > b->y) {
            a->r = join(a->r, b);
            if (a->r) a->r->p = a;
            return update(a), a;
        } else {
            b->l = join(a, b->l);
            if (b->l) b->l->p = b;
            return update(b), b;
        }
    }
    node* join(const std::vector<node*>& v) {
        return join(v, 0, v.size());
    }
    template <class F> void for_each(node* a, F f) const {
        if (!a) return;
        if (a->l) for_each(a->l, f);
        f(a);
        if (a->r) for_each(a->r, f);
    }
    node* insert(node* root, int k, node* u) {
        node *l, *r;
        split(root, l, r, k);
        return join({l, u, r});
    }
    node* erase(node* root, int k) {
        node *l, *m, *r;
        split(root, l, r, k);
        split(r, m, r, 1);
        return join(l, r);
    }
};
