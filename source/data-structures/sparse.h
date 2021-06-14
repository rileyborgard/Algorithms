
template<typename T, class Compare = std::less<T>>
struct sparse {
    vector<vector<T>> st;
    vector<int> log;
    int n;
    sparse(vector<T> a) {
        n = a.size();
        log.assign(n + 1, 0);
        log[1] = 0;
        for(int i = 2; i <= n; i++) {
            log[i] = log[i / 2] + 1;
        }
        int lg = log[n] + 1;
        st.assign(n, vector<T>(lg));
        for(int i = 0; i < n; i++) {
            st[i][0] = a[i];
        }
        for(int j = 1; j < lg; j++) {
            for(int i = 0; i + (1 << j) <= n; i++) {
                st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1], Compare{});
            }
        }
    }
    int query(int l, int r) {
        int j = log[r - l + 1];
        return min(st[l][j], st[r - (1 << j) + 1][j], Compare{});
    }
};
