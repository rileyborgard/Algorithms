
template<typename T>
std::vector<T> gauss(std::vector<std::vector<T>> a) {
    int n = a.size();
    int m = a[0].size() - 1;

    std::vector<int> where(m, -1);
    for (int col = 0, row = 0; col < m && row < n; ++col) {
        int sel = row;
        for (int i = row; i < n; ++i) {
            if (a[i][col] != T()) {
                sel = i;
                break;
            }
        }
        if (a[sel][col] == T()) continue;
        for (int i = col; i <= m; ++i) {
            std::swap(a[sel][i], a[row][i]);
        }
        where[col] = row;

        for (int i = 0; i < n; ++i) {
            if (i != row) {
                T c = a[i][col] / a[row][col];
                for (int j = col; j <= m; ++j) {
                    a[i][j] -= a[row][j] * c;
                }
            }
        }
        ++row;
    }

    std::vector<T> ans(m, T());
    for (int i = 0; i < m; ++i) {
        if (where[i] != -1) {
            ans[i] = a[where[i]][m] / a[where[i]][i];
        }
    }
    return ans;
}

template<typename T>
struct LinearRegression {
    std::vector<std::vector<T>> A;
    std::vector<T> B;
    void push(std::vector<T> a, T b) {
        A.push_back(a);
        B.push_back(b);
    }
    std::vector<T> solve() {
        int n = A.size();
        int m = A[0].size();
        std::vector<std::vector<T>> ATA(m, std::vector(m, T()));
        std::vector<T> ATB(m);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                ATB[i] += A[j][i] * B[j];
            }
            for (int j = 0; j < m; j++) {
                for (int k = 0; k < n; k++) {
                    ATA[i][j] += A[k][i] * A[k][j];
                }
            }
        }
        for (int i = 0; i < m; i++) {
            ATA[i].push_back(ATB[i]);
        }
        std::vector<T> c = gauss(ATA);
        for (int i = 0; i < n; i++) {
            T sum = T();
            for (int j = 0; j < m; j++) {
                sum += A[i][j] * c[j];
            }
            if (sum != B[i]) {
                return {};
            }
        }
        return c;
    }
};

template<typename T>
void printCoef(T c) {
    std::cout << c;
}

template<int P>
void printCoef(mod<P> c) {
    const int MX = 100;
    if (c.x <= MX) {
        std::cout << c;
        return;
    } else if (P - c.x <= MX) {
        std::cout << "(-" << -c << ")";
        return;
    }
    for (int denom = 2; denom <= MX; denom++) {
        mod<P> numer = mod<P>(denom) * c;
        if (numer.x <= MX) {
            std::cout << "(" << numer << "/" << denom << ")";
            return;
        } else if (P - numer.x <= MX) {
            std::cout << "(-" << -numer << "/" << denom << ")";
            return;
        }
    }
    std::cout << c;
}

template<typename T>
struct SequenceAnalysis {
    struct Group {
        std::vector<std::string> keys;
        int deg;
    };
    std::map<std::string, std::vector<T>> a;
    std::vector<Group> groups;
    int n = 0;
    void add_group(std::vector<std::string> keys, int deg) {
        groups.push_back({keys, deg});
    }
    void push(std::map<std::string, T> entry) {
        n++;
        for (auto &pa : entry) {
            a[pa.first].push_back(pa.second);
        }
        a["1"].push_back(1);
    }
    void solve(std::string solveKey) {
        // Populate "a" with remaining keys from the groups
        for (auto &G : groups) {
            int nKeys = sz(G.keys);
            vi mask(nKeys + G.deg - 1, 1);
            for (int i = 0; i < G.deg; i++) {
                mask[i] = 0;
            }
            do {
                std::vector<std::string> comb;
                int i_key = 0;
                for (int i = 0; i < sz(mask); i++) {
                    if (mask[i] == 0) {
                        comb.push_back(G.keys[i_key]);
                    } else {
                        i_key++;
                    }
                }
                std::string combineKey = "";
                for (int i = 0; i < G.deg; i++) {
                    combineKey += comb[i];
                    if (i < G.deg - 1) {
                        combineKey += " * ";
                    }
                }
                if (a.find(combineKey) != a.end()) {
                    continue;
                }
                std::vector<T> combineVals;
                for (int i = 0; i < n; i++) {
                    T val = 1;
                    for (const std::string& key : comb) {
                        val *= a[key][i];
                    }
                    combineVals.push_back(val);
                }
                a[combineKey] = combineVals;
            } while (next_permutation(all(mask)));
        }
        LinearRegression<T> LR;
        std::vector<std::string> keys;
        for (auto &pa : a) {
            if (pa.first == solveKey) continue;
            keys.push_back(pa.first);
        }
        for (int i = 0; i < n; i++) {
            std::vector<T> ve;
            T b = T();
            for (auto &pa : a) {
                if (pa.first == solveKey) {
                    b = pa.second[i];
                    continue;
                }
                ve.push_back(pa.second[i]);
            }
            LR.push(ve, b);
        }
        auto c = LR.solve();
        int nK = keys.size();
        if ((int) c.size() != nK) {
            std::cout << "No solution\n";
            return;
        }
        bool first = true;
        std::string ans;
        std::cout << solveKey << " = ";
        for (int i = 0; i < nK; i++) {
            if (c[i] == T()) {
                continue;
            }
            if (!first) {
                std::cout << " + ";
            }
            first = false;
            printCoef(c[i]);
            std::cout << " (" << keys[i] << ")";
        }
        if (first) {
            std::cout << 0;
        }
        std::cout << '\n';
    }
};
