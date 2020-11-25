
/*
 * Fenwick Tree / Binary-Indexed Tree
 * upd(i, x) increments position i of the array to x
 *      Complexity: log(n)
 * operator[](i) returns the sum in the range [1, i]
 *      Complexity: log(n)
 */

template<typename T>
struct bit {
    vector<T> a;
    bit(int n) {
        a.assign(n, {});
    }
    void upd(int i, T x) {
        while(i < (int) a.size()) {
            a[i] = a[i] + x;
            i += i & -i;
        }
    }
    T operator[](int i) {
        T x = {};
        while(i > 0) {
            x = x + a[i];
            i -= i & -i;
        }
        return x;
    }
};
