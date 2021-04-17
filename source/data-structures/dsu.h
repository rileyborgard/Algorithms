
struct dsu {
    vector<int> a;
    dsu(size_t n) {
        a.assign(n, -1);
    }
    size_t find(size_t x) {
        return a[x] < 0 ? x : a[x] = find(a[x]);
    }
    size_t size(size_t x) {
        return -a[find(x)];
    }
    bool join(size_t x, size_t y) {
        if((x = find(x)) == (y = find(y))) return false;
        if(a[x] > a[y]) swap(x, y);
        a[x] += a[y];
        a[y] = x;
        return true;
    }
};