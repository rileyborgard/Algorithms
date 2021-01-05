
template<typename T>
T root(int n, bool inv = false);

using ftype = double;
using cd = complex<ftype>;
const ftype pi = acos(-1);

template<>
cd root<>(int n, bool inv) {
    return polar(1.0, 2 * pi / n * (inv ? -1 : 1));
}
template<>
mod<998244353> root<>(int n, bool inv) {
    return mod<998244353>(3).pow(1LL * (998244353 - 1) / n * (inv ? n - 1 : 1));
}

template<typename T>
struct poly {
    vector<T> a;
    size_t deg;
    poly(T a0 = T()) {
        a.assign(1, a0);
        deg = 0;
    }
    poly(vector<T> t) : a(t) {
        assert(!t.empty());
        resize(a.size());
        deg = t.size() - 1;
    }
    void resize(size_t n) {
        deg = min(deg, n - 1);
        size_t s = 1;
        while(s < n) s <<= 1;
        a.resize(s);
    }
    size_t size() const {
        return a.size();
    }
    const T operator[](size_t i) const {
        return i > deg ? T() : a[i];
    }
    void set(size_t i, const T &t) {
        a[i] = t;
        deg = max(deg, i);
    }
    poly operator+(const poly &A) const {
        poly P;
        P.resize(max(size(), A.size()));
        for(size_t i = 0; i < P.size(); i++) {
            P.a[i] = (*this)[i] + A[i];
        }
        P.deg = max(deg, A.deg);
        return P;
    }
    poly operator+=(const poly A) {
        return *this = *this + A;
    }
    poly operator-(const poly A) const {
        poly P;
        P.resize(max(size(), A.size()));
        for(int i = 0; i < (int) P.size(); i++) {
            P.a[i] = (*this)[i] - A[i];
        }
        P.deg = max(deg, A.deg);
        return P;
    }
    poly operator-=(const poly A) {
        return *this = *this - A;
    }
    void fft(bool inv = false) {
        int n = (int) size();
        for(int i = 1, j = 0; i < n; i++) {
            int bit = n >> 1;
            for(; j & bit; bit >>= 1) j ^= bit;
            j ^= bit;
            if(i < j) swap(a[i], a[j]);
        }
        for(int len = 2; len <= n; len <<= 1) {
            T wn = root<T>(len, inv);
            for(int i = 0; i < n; i += len) {
                T w = 1;
                for(int j = 0; j < len / 2; j++) {
                    T u = a[i + j], v = a[i + j + len / 2] * w;
                    a[i + j] = u + v;
                    a[i + j + len / 2] = u - v;
                    w *= wn;
                }
            }
        }
        if(inv) {
            T n_1 = T(1) / T(n);
            for(T &x : a) x *= n_1;
        }
    }
    poly mod_xk(size_t k) const {
        poly P;
        P.resize(k);
        for(size_t i = 0; i < k; i++) P.a[i] = (*this)[i];
        P.deg = min(k - 1, deg);
        return P;
    }
    poly& operator*=(const poly &o) {
        size_t s = 2 * max(size(), o.size());
        resize(s);
        poly B = o;
        B.resize(s);
        fft(); B.fft();
        for(size_t i = 0; i < s; i++) {
            a[i] *= B.a[i];
        }
        fft(true);
        deg = deg + o.deg;
        resize(deg + 1);
        return *this;
    }
    poly operator*(const poly &o) const {
        poly A = *this;
        A *= o;
        return A;
    }
    poly& operator*=(const T &t) {
        for(size_t i = 0; i <= deg; i++) {
            a[i] *= t;
        }
        return *this;
    }
    poly operator*(const T &t) const {
        poly A = *this;
        A *= t;
        return A;
    }
    poly deriv() const {
        poly P;
        P.resize(deg);
        for(int i = 1; i <= (int) deg; i++) {
            P.a[i - 1] = a[i] * T(i);
        }
        P.deg = max(size_t(1), deg) - 1;
        return P;
    }
    poly integ() const {
        poly P;
        P.resize(deg + 2);
        for(size_t i = 0; i <= deg; i++) {
            P.a[i + 1] = a[i] / T(i + 1);
        }
        P.deg = deg + 1;
        return P;
    }
    poly mul_xk(size_t k) const {
        poly P;
        P.resize(deg + k + 1);
        for(size_t i = 0; i <= deg; i++) {
            P.a[i + k] = a[i];
        }
        P.deg = deg + k;
        return P;
    }
    poly div_xk(size_t k) const {
        k = min(k, size());
        poly P;
        P.resize(deg - k + 1);
        for(size_t i = k; i <= deg; i++) {
            P.a[i - k] = a[i];
        }
        P.deg = deg - k;
        return P;
    }
    poly inv(size_t n) const {
        poly Q = T(1) / a[0];
        for(size_t s = 2; s < n * 2; s <<= 1) {
            Q *= (poly(2) - Q * mod_xk(s));
            Q.resize(s);
        }
        Q.deg = n - 1;
        return Q;
    }
    poly log(size_t n) const {
        return (deriv().mod_xk(n) * inv(n)).integ().mod_xk(n);
    }
    poly exp(size_t n) const {
        poly Q = T(1);
        for(size_t s = 2; s < n * 2; s <<= 1) {
            Q *= (poly(1) + mod_xk(s) - Q.log(s));
            Q.resize(s);
        }
        Q.deg = n - 1;
        return Q;
    }
};

template<int m>
void print(const poly<mod<m>> &P) {
    cout << P[0]();
    for(size_t i = 1; i < P.size(); i++) {
        cout << " + " << P[i]() << " x^" << i;
    }
    cout << '\n';
}
void print(const poly<cd> &P) {
    cout << round(P[0].real());
    for(size_t i = 1; i < P.size(); i++) {
        cout << " + " << round(P[i].real()) << " x^" << i;
    }
    cout << '\n';
}
void printreal(const poly<cd> &P) {
    cout << round(P[0].real());
    for(size_t i = 1; i < P.size(); i++) {
        cout << " + " << P[i].real() << " x^" << i;
    }
    cout << '\n';
}