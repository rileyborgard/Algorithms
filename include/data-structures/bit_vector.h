
inline size_t BLOCK(size_t i) { return i >> 6; }
inline size_t BIT(size_t i) { return i & 63; }
inline uint64_t FLAG(size_t bit) { return 1ull << bit; }
inline uint64_t LAST_MASK(size_t n) { return 0xFFFF'FFFF'FFFF'FFFFull >> (63 - BIT(n - 1)); }

class bit_vector {
private:
    vector<uint64_t> _a;
    size_t _n;
public:
    bit_vector(size_t n = 0) {
        _n = n;
        size_t m = (n + 63) / 64;
        _a.assign(m, 0);
    }
    bit_vector(vector<uint64_t> v) : _a(v) { _n = v.size() * 64; }
    bool test(size_t i) const { return _a[BLOCK(i)] >> BIT(i) & 1; }
    void reset(size_t i) { _a[BLOCK(i)] &= ~FLAG(BIT(i)); }
    void set(size_t i) {  _a[BLOCK(i)] |= FLAG(BIT(i)); }
    void set(size_t i, bool val) {
        size_t k = BLOCK(i);
        size_t bit = BIT(i);
        if (val) _a[k] |= FLAG(bit);
        else _a[k] &= ~FLAG(bit);
    }
    void flip(size_t i) { _a[BLOCK(i)] ^= FLAG(BIT(i)); }
    size_t size() const { return _n; }
    size_t count() const {
        size_t ans = 0;
        for (size_t k = 0; k < _a.size(); k++)
            ans += __builtin_popcountll(_a[k]);
        return ans;
    }
    bool is_all() const {
        if (_n == 0) return true;
        size_t l = _a.size() - 1;
        for (size_t k = 0; k < l; k++)
            if (_a[k] != ~0ull) return false;
        return _a[l] == LAST_MASK(_n);
    }
    bool is_any() const {
        for (size_t k = 0; k < _a.size(); k++)
            if (_a[k] != 0ull) return true;
        return false;
    }
    bool is_none() const {
        for (size_t k = 0; k < _a.size(); k++) {
            if (_a[k] != 0ull) {
                return false;
            }
        }
        return true;
    }
    bit_vector operator~() const {
        bit_vector out(_n);
        if (_n == 0) return out;
        size_t l = _a.size() - 1;
        for (size_t k = 0; k < l; k++) out._a[k] = ~_a[k];
        out._a[l] = ~_a[l] & LAST_MASK(_n);
        return out;
    }
    bit_vector operator|(const bit_vector &b) const {
        bit_vector out(max(_n, b._n));
        size_t m = min(_a.size(), b._a.size());
        for (size_t k = 0; k < m; k++) {
            out._a[k] = _a[k] | b._a[k];
        }
        if (_a.size() > m) {
            copy(_a.begin() + m, _a.end(), out._a.begin() + m);
        } else if (b._a.size() > m) {
            copy(b._a.begin() + m, b._a.end(), out._a.begin() + m);
        }
        return out;
    }
    bit_vector operator&(const bit_vector &b) const {
        bit_vector out(max(_n, b._n));
        size_t m = min(_a.size(), b._a.size());
        for (size_t k = 0; k < m; k++) out._a[k] = _a[k] & b._a[k];
        return out;
    }
    bit_vector operator^(const bit_vector &b) const {
        bit_vector out(max(_n, b._n));
        size_t m = min(_a.size(), b._a.size());
        for (size_t k = 0; k < m; k++) out._a[k] = _a[k] ^ b._a[k];
        return out;
    }
    bit_vector& operator|=(const bit_vector &b) {
        if (_n == 0) return *this;
        size_t m = min(_a.size(), b._a.size());
        for (size_t k = 0; k < m; k++) _a[k] |= b._a[k];
        size_t l = _a.size() - 1;
        _a[l] &= LAST_MASK(_n);
        return *this;
    }
    bit_vector& operator&=(const bit_vector &b) {
        size_t m = min(_a.size(), b._a.size());
        for (size_t k = 0; k < m; k++) _a[k] &= b._a[k];
        fill(_a.begin() + m, _a.end(), 0ull);
        return *this;
    }
    bit_vector& operator^=(const bit_vector &b) {
        size_t m = min(_a.size(), b._a.size());
        for (size_t k = 0; k < m; k++) _a[k] ^= b._a[k];
        return *this;
    }
    bit_vector operator<<(const size_t i) const {
        bit_vector out(_n);
        size_t s = BLOCK(i);
        size_t m = _a.size();
        if (_n == 0 || s >= m) return out;
        size_t t = BIT(i);
        if (t == 0) {
            copy(_a.begin(), _a.begin() + m, out._a.begin() + s);
        } else {
            out._a[s] = _a[0] << t;
            for (size_t k = s + 1; k < m; k++)
                out._a[k] = (_a[k - s] << t) | (_a[k - s - 1] >> (64 - t));
        }
        size_t l = _a.size() - 1;
        out._a[l] &= LAST_MASK(_n);
        return out;
    }
    bit_vector operator>>(size_t i) const {
        bit_vector out(_n);
        size_t s = BLOCK(i);
        size_t m = _a.size();
        if (_n == 0 || s >= m) return out;
        size_t t = BIT(i);
        if (t == 0) {
            copy(_a.begin() + s, _a.end(), out._a.begin());
        } else {
            for (size_t k = 0; k < m - s - 1; k++)
                out._a[k] = (_a[k + s] >> t) | (_a[k + s + 1] << (64 - t));
            out._a[m - s - 1] = _a[m - 1] >> t;
        }
        return out;
    }
    bit_vector& operator<<=(size_t i) { return *this = *this << i; }
    bit_vector& operator>>=(size_t i) { return *this = *this >> i; }
    void resize(size_t n) {
        size_t m = (n + 63) / 64;
        if (n < _n && n > 0) _a[m - 1] &= LAST_MASK(n);
        _n = n;
        _a.resize(m);
    }
    uint64_t block(size_t i) const { return i < _a.size() ? _a[i] : 0; }
    void paste_block(size_t i, uint64_t value) {
        if (i >= _a.size()) return;
        _a[i] = value;
        if (i == _a.size() - 1)  _a[i] &= LAST_MASK(_n);
    }
};