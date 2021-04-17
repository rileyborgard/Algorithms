
template<int m>
struct mod {
    long long x;
    mod() : x(0) {}
    mod(long long xx) : x(xx) {
        if(abs(x) >= m) x %= m;
        if(x < 0) x += m;
    }
    mod operator+(const mod &a) const {
        mod n;
        n.x = x + a.x;
        if(n.x >= m) n.x -= m;
        return n;
    }
    mod operator-(const mod &a) const {
        mod n;
        n.x = x - a.x;
        if(n.x < 0) n.x += m;
        return n;
    }
    mod operator*(const mod &a) const {
        return x * a.x;
    }
    mod operator+=(const mod &a) {
        x += a.x;
        if(x >= m) x -= m;
        return *this;
    }
    mod operator-=(const mod &a) {
        x -= a.x;
        if(x < 0) x += m;
        return *this;
    }
    mod operator*=(const mod &a) {
        x = (x * a.x) % m;
        return *this;
    }
    mod pow(long long b) const {
        mod ans = 1;
        mod a = *this;
        while(b > 0) {
            if(b & 1) ans *= a;
            a *= a;
            b /= 2;
        }
        return ans;
    }
    mod inv() const {
        return pow(m - 2);
    }
    mod operator/(const mod &a) const {
        return (*this) * a.inv();
    }
    mod operator/=(const mod &a) {
        return (*this) *= a.inv();
    }
    bool operator==(const mod &o) const {
        return x == o.x;
    }
    bool operator!=(const mod &o) const {
        return x != o.x;
    }
    long long operator()() const {
        return x;
    }
};

template<int m>
istream &operator>>(istream &is, mod<m> &n) {
    long long x;
    is >> x;
    n = x;
    return is;
}

template<int m>
ostream &operator<<(ostream &os, const mod<m> &n) {
    return os << n();
}
