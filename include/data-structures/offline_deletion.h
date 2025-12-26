
// struct ds {
//     void push(U u);
//     void pop();
//     Q query();
// };

template<typename D, typename U, typename Q>
struct offline_deletion : public D {
    vector<Q> ans;
    vector<vector<U>> updates;
    int q;
    offline_deletion(int queries) : q(queries), ans(q) {
        int lg = 0;
        while((1 << lg) < q) lg++;
        updates.resize(1 << (lg + 1));
    }
    void update(int i, int l, int r, int L, int R, U u) {
        if(r < L || R < l) return;
        if(L <= l && r <= R) {
            updates[i].push_back(u);
            return;
        }
        int m = (l + r) / 2;
        update(2 * i + 1, l, m, L, R, u);
        update(2 * i + 2, m + 1, r, L, R, u);
    }
    void insert(U u, int l, int r) {
        update(0, 0, q - 1, l, r, u);
    }
    void insert(U u, int l) {
        insert(u, l, q - 1);
    }
    void solve(int i, int l, int r) {
        for(auto &u : updates[i]) {
            D::push(u);
        }
        if(l == r) {
            ans[l] = D::query();
        }else {
            int m = (l + r) / 2;
            solve(2 * i + 1, l, m);
            solve(2 * i + 2, m + 1, r);
        }
        for(int j = 0; j < (int) updates[i].size(); j++) {
            D::pop();
        }
    }
    void solve() {
        solve(0, 0, q - 1);
    }
};
