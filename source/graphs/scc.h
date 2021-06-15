
struct scc {
    int n;
    vector<vector<int>> g, gr;
    vector<int> st, comp;
    vector<bool> vis;
    scc(int n) : n(n) {
        g.resize(n);
        gr.resize(n);
        vis.assign(n, false);
        comp.assign(n, -1);
    }
    void add_edge(int u, int v) {
        g[u].push_back(v);
        gr[v].push_back(u);
    }
    void dfs(int x) {
        vis[x] = true;
        for(int y : g[x]) {
            if(!vis[y]) {
                dfs(y);
            }
        }
        st.push_back(x);
    }
    void dfs2(int x, int c) {
        comp[x] = c;
        for(int y : gr[x]) {
            if(comp[y] == -1) {
                dfs2(y, c);
            }
        }
    }
    void solve() {
        for(int i = 0; i < n; i++) {
            if(!vis[i]) {
                dfs(i);
            }
        }
        while(!st.empty()) {
            int x = st.back(); st.pop_back();
            if(comp[x] == -1) {
                dfs2(x, x);
            }
        }
    }
};
