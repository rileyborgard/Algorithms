
template<typename C>
struct dinic {
    struct edge {
        int v;
        C cap, flow;
    };
    int n;
    vector<edge> e;
    vector<vector<int>> g;
    vector<int> level, p;
    dinic(int n) {
        g.resize(n);
        p.resize(n);
        level.resize(n);
    }
    void add_edge(int u, int v, C c) {
        int k = (int) e.size();
        e.push_back({v, c, 0});
        e.push_back({u, c, c});
        g[u].push_back(k);
        g[v].push_back(k ^ 1);
    }
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> Q;
        Q.push(s);
        level[s] = 0;
        while(!Q.empty()) {
            int x = Q.front(); Q.pop();
            for(int i : g[x]) {
                if(level[e[i].v] == -1 && e[i].flow < e[i].cap) {
                    level[e[i].v] = level[x] + 1;
                    Q.push(e[i].v);
                }
            }
        }
        return level[t] != -1;
    }
    C dfs(int x, int t, C amt) {
        if(x == t) return amt;
        for(int &i = p[x]; i < (int) g[x].size(); i++) {
            int idx = g[x][i];
            if(level[e[idx].v] == level[x] + 1 && e[idx].flow < e[idx].cap) {
                C a = dfs(e[idx].v, t, min(amt, e[idx].cap - e[idx].flow));
                if(a > 0) {
                    e[idx].flow += a;
                    e[idx ^ 1].flow -= a;
                    return a;
                }
            }
        }
        return 0;
    }
    C flow(int s, int t, C mx) {
        C f = 0;
        while(bfs(s, t)) {
            fill(p.begin(), p.end(), 0);
            while(true) {
                C d = dfs(s, t, mx - f);
                if(d == 0) break;
                f += d;
            }
        }
        return f;
    }
};
