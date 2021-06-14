
struct suffix_array {
    int n;
    string s;
    vector<int> p, rank, lcp;
    suffix_array(string s) : s(s) {
        const int A = 256;
        s.push_back('$');
        n = s.length();
        int cl = 1;
        vector<int> c(n), pn(n), cn(n), cnt(max(A, n), 0);
        p.assign(n, 0);
        for(int i = 0; i < n; i++) {
            cnt[s[i]]++;
        }
        for(int i = 1; i < A; i++) {
            cnt[i] += cnt[i - 1];
        }
        for(int i = 0; i < n; i++) {
            p[--cnt[s[i]]] = i;
        }
        c[p[0]] = 0;
        for(int i = 1; i < n; i++) {
            if(s[p[i]] != s[p[i - 1]]) {
                cl++;
            }
            c[p[i]] = cl - 1;
        }
        for(int h = 0; (1 << h) < n; h++) {
            for(int i = 0; i < n; i++) {
                pn[i] = p[i] - (1 << h);
                if(pn[i] < 0) {
                    pn[i] += n;
                }
            }
            fill(cnt.begin(), cnt.begin() + cl, 0);
            for(int i = 0; i < n; i++) {
                cnt[c[pn[i]]]++;
            }
            for(int i = 1; i < cl; i++) {
                cnt[i] += cnt[i - 1];
            }
            for(int i = n - 1; i >= 0; i--) {
                p[--cnt[c[pn[i]]]] = pn[i];
            }
            cn[p[0]] = 0;
            cl = 1;
            for(int i = 1; i < n; i++) {
                pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
                pair<int, int> prv = {c[p[i - 1]], c[(p[i - 1] + (1 << h)) % n]};
                if(cur != prv) {
                    cl++;
                }
                cn[p[i]] = cl - 1;
            }
            c.swap(cn);
        }
        rank.assign(n, 0);
        for(int i = 0; i < n; i++) {
            rank[p[i]] = i;
        }
        int k = 0;
        lcp.assign(n - 1, 0);
        for(int i = 0; i < n; i++) {
            if(rank[i] == n - 1) {
                k = 0;
                continue;
            }
            int j = p[rank[i] + 1];
            while(i + k < n && j + k < n && s[i + k] == s[j + k]) {
                k++;
            }
            lcp[rank[i]] = k;
            if(k > 0) {
                k--;
            }
        }
    }
};
