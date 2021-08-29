
/*
struct edge {
	information for a matroid element
};
struct matroid {
	void clear(); -> remove all edges from the independent set
	void add(const edge &e); -> add an edge to the independent set
	void prepare(); -> prepare the added edges for queries
	bool free(const edge &e); -> can we add e and still be independent?
	bool exchange(const edge &x, const edge &y); -> can we remove x, add y, and still be independent?
};
*/

struct color {
	int c;
	color(int c) : c(c) {}
};

struct color_matroid {
	vector<int> cnt, a;
	color_matroid(vector<int> cnt) : cnt(cnt.begin(), cnt.end()), a(cnt.size()) {}
	void clear() {
		fill(a.begin(), a.end(), 0);
	}
	void add(const color &x) {
		a[x.c]++;
	}
	void prepare() {}
	bool free(const color &x) {
		return a[x.c] < cnt[x.c];
	}
	bool exchange(const color &x, const color &y) {
		a[x.c]--;
		bool ans = (a[y.c] < cnt[y.c]);
		a[x.c]++;
		return ans;
	}
};

struct edge {
	int u, v;
	edge(int u, int v) : u(u), v(v) {}
};

struct graph_matroid {
	int n;
	vector<vector<int>> g;
	vector<int> tin, tout, comp;
	int ti;
	graph_matroid(int n) : n(n), g(n), tin(n), tout(n), comp(n) {}
	void clear() {
		for(int i = 0; i < n; i++) {
			g[i].clear();
		}
	}
	void add(const edge &x) {
		g[x.u].push_back(x.v);
		g[x.v].push_back(x.u);
	}
	void dfs(int x) {
		tin[x] = ti++;
		for(int y : g[x]) {
			if(tin[y] == 0) {
				comp[y] = comp[x];
				dfs(y);
			}
		}
		tout[x] = ti++;
	}
	void prepare() {
		fill(tin.begin(), tin.end(), 0);
		ti = 1;
		for(int i = 0; i < n; i++) {
			if(tin[i] == 0) {
				comp[i] = i;
				dfs(i);
			}
		}
	}
	bool anc(int x, int y) {
		return tin[x] <= tin[y] && tout[y] <= tout[x];
	}
	bool free(const edge &x) {
		return comp[x.u] != comp[x.v];
	}
	bool exchange(const edge &x, const edge &y) {
		int u = (tin[x.u] < tin[x.v] ? x.v : x.u);
		return anc(u, y.u) ^ anc(u, y.v);
	}
};

template<typename M1, typename E1, typename M2, typename E2>
struct matroid_intersection {
	M1 m1;
	M2 m2;
	matroid_intersection(M1 m1, M2 m2) : m1(m1), m2(m2) {}
	vector<int> solve(const vector<pair<E1, E2>> &e) {
		int rank = 0, n = (int) e.size();
		vector<int> par(n, -1);
		vector<bool> used(n, false);
		vector<int> basis;
		while(true) {
			queue<int> Q;
			m1.clear(); m2.clear(); basis.clear();
			fill(par.begin(), par.end(), -1);
			for(int i = 0; i < n; i++) {
				if(used[i]) {
					basis.push_back(i);
					m1.add(e[i].first);
					m2.add(e[i].second);
				}
			}
			m1.prepare(); m2.prepare();
			
			bool aug = false;
			auto enqueue = [&](int i, int j) {
				par[j] = i;
				Q.push(j);
				if(!used[j] && m2.free(e[j].second)) {
					do {
						used[j] = !used[j];
						j = par[j];
					}while(j != par[j]);
					aug = true;
				}
				return aug;
			};
			for(int i = 0; i < n; i++) {
				if(!used[i] && m1.free(e[i].first)) {
					if(enqueue(i, i)) break;
				}
			}
			while(!Q.empty() && !aug) {
				int i = Q.front(); Q.pop();
				if(used[i]) {
					for(int j = 0; j < n; j++) {
						if(!used[j] && par[j] == -1 && m1.exchange(e[i].first, e[j].first)) {
							if(enqueue(i, j)) break;
						}
					}
				}else {
					for(int j : basis) {
						if(par[j] == -1 && m2.exchange(e[j].second, e[i].second)) {
							if(enqueue(i, j)) break;
						}
					}
				}
			}
			if(aug) rank++;
			else break;
		}
		return basis;
	}
};
