
template<typename T>
struct sos {
    int n;
    vector<T> a;
    sos(size_t n) : n(n) {
        a.assign((1 << n), T());
    }
    void clear() {
        fill(a.begin(), a.end(), T());
    }
    void flip() {
        for(int i = 0; i < (1 << (n - 1)); i++) {
            swap(a[i], a[i ^ ((1 << n) - 1)]);
        }
    }
    void zeta() {
        for(int i = 0; i < n; i++) {
            for(int s = 0; s < (1 << n); s++) {
                if(s >> i & 1) {
                    a[s] = a[s] + a[s ^ (1 << i)];
                }
            }
        }
    }
    void supzeta() {
        for(int i = n - 1; i >= 0; i--) {
            for(int s = (1 << n) - 1; s >= 0; s--) {
                if(~s >> i & 1) {
                    a[s] = a[s] + a[s ^ (1 << i)];
                }
            }
        }
    }
    void mobius() {
        for(int i = n - 1; i >= 0; i--) {
            for(int s = (1 << n) - 1; s >= 0; s--) {
                if(s >> i & 1) {
                    a[s] = a[s] - a[s ^ (1 << i)];
                }
            }
        }
    }
    void supmobius() {
        for(int i = 0; i < n; i++) {
            for(int s = 0; s < n; s++) {
                if(~s >> i & 1) {
                    a[s] = a[s] - a[s ^ (1 << i)];
                }
            }
        }
    }
};