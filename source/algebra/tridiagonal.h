
template <typename T>
struct tridiagonal {
    struct row {
        array<T, 3> a;
        T b;
    };
    vector<row> rows;
    void push(const row &r) {
        rows.push_back(r);
    }
    void solve() {
        int n = sz(rows);
        rep(i, 0, n) {
            auto &R = rows[i];
            if (i > 0) {
                // Subtract previous row * rows[i].a[0]
                auto &Pre = rows[i - 1];
                base x = R.a[0];
                R.a[0] -= Pre.a[1] * x;
                R.a[1] -= Pre.a[2] * x;
                R.b -= Pre.b * x;
            }
            // Normalize row
            assert(R.a[1] != 0);
            base inv = R.a[1].inv();
            R.a[0] *= inv;
            R.a[1] *= inv;
            R.a[2] *= inv;
            R.b *= inv;
        }
        for (int i = n - 2; i >= 0; i--) {
            auto &R = rows[i];
            auto &Next = rows[i + 1];
            base x = R.a[2];
            assert(Next.a[1] == 1);
            R.a[0] = 0;
            R.a[1] -= Next.a[0] * x;
            R.a[2] -= Next.a[1] * x;
            R.b -= Next.b * x;
            // Normalize row
            assert(R.a[1] != 0);
            base inv = R.a[1].inv();
            R.a[0] *= inv;
            R.a[1] *= inv;
            R.a[2] *= inv;
            R.b *= inv;
        }
    }
};