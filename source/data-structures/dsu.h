
/*
 * Disjoint Set Union with path-compression and small-to-large merging.
 * find(x) returns the representative of the set containing x
 *      Complexity: alpha(n)
 * join(x, y) merges the sets containing x and y. Returns true if the
 *      merge took place, and false if they were already in the same set to begin with
 *      Complexity: alpha(n)
 */

struct dsu {
    vector<int> a;
    dsu(int n) {
        a.assign(n, -1);
    }
    int operator[](int x) {
        return a[x] < 0 ? x : a[x] = (*this)[a[x]];
    }
    bool join(int x, int y) {
        if((x = (*this)[x]) == (y = (*this)[y])) return false;
        if(a[x] > a[y]) swap(x, y);
        a[x] += a[y];
        a[y] = x;
        return true;
    }
};