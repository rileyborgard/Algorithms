
template<typename T>
struct treapnode {
    T val;
    int y, cnt;
    treapnode *left, *right;
    treapnode(T val = T(), int y = rand()) : val(val), y(y) {
        left = right = NULL;
        cnt = 1;
    }
    void upd() {
        cnt = 1 + (left ? left->cnt : 0) + (right ? right->cnt : 0);
    }
};

template<typename T>
struct treap {
    treapnode<T> *root;
    treap(treapnode<T> *x = NULL) : root(x) {}
    treap(const vector<T> &v) {
        root = build(v, 0, (int) v.size());
    }

    treapnode<T>* build(const vector<T> &v, int l, int r) {
        if(l == r) return NULL;
        int m = (l + r) / 2;
        treapnode<T> *x = new treapnode(v[m]);
        x->left = build(v, l, m);
        x->right = build(v, m + 1, r);
        x->upd();
        return x;
    }
    pair<treapnode<T>*, treapnode<T>*> split(treapnode<T> *x, int k) {
        if(x == NULL) return {NULL, NULL};
        int c = (x->left ? x->left->cnt : 0);
        if(c >= k) {
            pair<treapnode<T>*, treapnode<T>*> pa = split(x->left, k);
            x->left = pa.second;
            x->upd();
            return {pa.first, x};
        }else {
            pair<treapnode<T>*, treapnode<T>*> pa = split(x->right, k - c - 1);
            x->right = pa.first;
            x->upd();
            return {x, pa.second};
        }
    }
    treapnode<T>* merge(treapnode<T> *x, treapnode<T> *y) {
        if(x == NULL) return y;
        if(y == NULL) return x;
        if(x->y > y->y) {
            x->right = merge(x->right, y);
            x->upd();
            return x;
        }else {
            y->left = merge(x, y->left);
            y->upd();
            return y;
        }
    }
    pair<treap<T>, treap<T>> split(int k) {
        pair<treapnode<T>*, treapnode<T>*> p = split(root, k);
        return {treap(p.first), treap(p.second)};
    }
    treap<T> operator+(treap<T> y) {
        return treap<T>(merge(root, y.root));
    }
    void operator+=(treap<T> y) {
        root = merge(root, y.root);
    }
    void insert(int k, T val) {
        pair<treapnode<T>*, treapnode<T>*> pa = split(root, k);
        treapnode<T> *x = new treapnode(val);
        root = merge(pa.first, merge(x, pa.second));
    }
    void erase(int l, int r) {
        pair<treapnode<T>*, treapnode<T>*> pa = split(root, r);
        pair<treapnode<T>*, treapnode<T>*> pb = split(pa.first, l);
        root = merge(pb.first, pa.second);
    }
    T get(treapnode<T> *x, int k) {
        if(x == NULL) return T();
        int c = (x->left ? x->left->cnt : 0);
        if(c > k) {
            return get(x->left, k);
        }else if(k == c) {
            return x->val;
        }else {
            return get(x->right, k - c - 1);
        }
    }
    T get(int k) {
        return get(root, k);
    }
    void array(vector<T> &v, treapnode<T> *x) {
        if(x == NULL) return;
        array(v, x->left);
        v.push_back(x->val);
        array(v, x->right);
    }
    vector<T> array() {
        vector<T> v;
        array(v, root);
        return v;
    }
};
