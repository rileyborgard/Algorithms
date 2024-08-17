
template<typename T>
int sgn(T x) {
    return (x > 0 ? 1 : x < 0 ? -1 : 0);
}

template<typename T>
struct pt {
    T x, y;
    pt(T x = T(), T y = T()) : x(x), y(y) {}
    pt operator+(const pt &o) const {
        return pt(x + o.x, y + o.y);
    }
    pt& operator+=(const pt &o) {
        x += o.x;
        y += o.y;
        return *this;
    }
    pt operator-(const pt &o) const {
        return pt(x - o.x, y - o.y);
    }
    pt& operator-=(const pt &o) {
        x -= o.x;
        y -= o.y;
        return *this;
    }
    pt operator*(const T &c) const {
        return pt(x * c, y * c);
    }
    pt& operator*=(const T &c) {
        x *= c;
        y *= c;
        return *this;
    }
    T dot(const pt &o) const {
        return x * o.x + y * o.y;
    }
    T cross(const pt &o) const {
        return x * o.y - y * o.x;
    }
};

template<typename T>
int o(const pt<T> &a, const pt<T> &b, const pt<T> &c) {
    return sgn((b - a).cross(c - a));
}

template<typename T>
istream& operator>>(istream &is, pt<T> &p) {
    T x, y;
    is >> x >> y;
    p = pt(x, y);
    return is;
}

template<typename T>
ostream& operator<<(ostream &os, const pt<T> &p) {
    return os << p.x << ' ' << p.y;
}

template<typename T>
bool segseg1(T l, T r, T L, T R) {
    if(l > r) swap(l, r);
    if(L > R) swap(L, R);
    return r < L || R < l;
}

template<typename T>
bool segseg(pt<T> a, pt<T> b, pt<T> c, pt<T> d) {
    return segseg1(a.x, b.x, c.x, d.x) && segseg1(a.y, b.y, c.y, d.y) &&
        o(a, b, c) * o(a, b, d) <= 0 && o(c, d, a) * o(c, d, b) <= 0;
}

template<typename T>
T signed_area2(const vector<pt<T>> &p) {
    int n = (int) p.size();
    T ans = 0;
    for(int i = 0; i < n; i++) {
        ans += p[i].cross(p[(i + 1) % n]);
    }
    return ans;
}

template<typename T>
T area2(const vector<pt<T>> &p) {
    return abs(signed_area2(p));
}
