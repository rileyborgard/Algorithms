
template<typename Cap, typename Cost>
struct mcmf {
    struct edge {
        int v;
        Cap cap, flow;
        Cost cost;
    };
    int n;
    vector<edge> e;
    vector<vector<int>> g;
    vector<Cost> dist, pot;
    vector<Cap> f;
    vector<bool> vis;
    vector<int> par;
    bool n2dijkstra = false;
    mcmf(int n) : n(n), g(n), dist(n), pot(n), f(n), vis(n), par(n) {}
    void add_edge(int u, int v, Cap cap, Cost cost) {
        int k = e.size();
        e.push_back({v, cap, 0, cost});
        e.push_back({u, cap, cap, -cost});
        g[u].push_back(k);
        g[v].push_back(k ^ 1);
    }
    pair<Cap, Cost> solve(int s, int t) {
        Cap flow = 0;
        Cost cost = 0;
        while(true) {
            fill(dist.begin(), dist.end(), numeric_limits<Cost>::max());
            fill(vis.begin(), vis.end(), false);
            dist[s] = 0;
            f[s] = numeric_limits<Cap>::max();
            if(n2dijkstra) {
                while(true) {
                    int x = -1; Cost d = numeric_limits<Cost>::max();
                    for(int i = 0; i < n; i++) {
                        if(!vis[i] && dist[i] < d) {
                            x = i;
                            d = dist[x];
                        }
                    }
                    if(x == -1) break;
                    vis[x] = true;
                    for(int i : g[x]) {
                        Cost d2 = d + e[i].cost + pot[x] - pot[e[i].v];
                        if(!vis[e[i].v] && e[i].flow < e[i].cap && d2 < dist[e[i].v]) {
                            dist[e[i].v] = d2;
                            f[e[i].v] = min(f[x], e[i].cap - e[i].flow);
                            par[e[i].v] = i;
                        }
                    }
                }
            }else {
                priority_queue<pair<Cost, int>, vector<pair<Cost, int>>, greater<>> Q;
                Q.push({0, s});
                while(!Q.empty()) {
                    Cost d; int x;
                    tie(d, x) = Q.top(); Q.pop();
                    if(vis[x]) continue;
                    vis[x] = true;
                    for(int i : g[x]) {
                        Cost d2 = d + e[i].cost + pot[x] - pot[e[i].v];
                        if(!vis[e[i].v] && e[i].flow < e[i].cap && d2 < dist[e[i].v]) {
                            dist[e[i].v] = d2;
                            f[e[i].v] = min(f[x], e[i].cap - e[i].flow);
                            par[e[i].v] = i;
                            Q.push({d2, e[i].v});
                        }
                    }
                }
            }
            if(!vis[t]) break;
            for(int i = 0; i < n; i++) {
                dist[i] += pot[i] - pot[s];
            }
            cost += dist[t] * f[t];
            flow += f[t];
            int x = t;
            while(x != s) {
                e[par[x]].flow += f[t];
                e[par[x] ^ 1].flow -= f[t];
                x = e[par[x] ^ 1].v;
            }
            dist.swap(pot);
        }
        return {flow, cost};
    }
};