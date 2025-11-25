// Source: https://github.com/rileyborgard/Algorithms/blob/main/source/template.cpp
#include <bits/stdc++.h>

#ifdef LOCAL
#include <local.h>
#else
#define dbg(...)
#define debug(...)
#define info(...)
#define error(...)
template <typename T>
char _dlim = ' ';
template <typename T>
char _dlim<std::vector<T>> = '\n';
template <typename T>
std::ostream& operator<<(std::ostream &os, const std::vector<T> &ve) {
    int n = ve.size();
    for (int i = 0; i < n; i++) {
        os << ve[i];
        if (i < n - 1) os << _dlim<T>;
    }
    return os;
}
#endif

#define ll long long
#define sz(x) ((int) (x).size())
#define all(x) (x).begin(), (x).end()
#define vi vector<int>
#define pii pair<int, int>
#define rep(i, a, b) for(int i = (a); i < (b); i++)
using namespace std;
template<typename T>
using minpq = priority_queue<T, vector<T>, greater<T>>;

template <typename T, typename... V>
void print(T &&head, V &&... tail) {
    cout << head << ' ';
    if constexpr (sizeof...(tail)) {
        print(tail...);
    }
}
void print() {}
#define println(...) {print(__VA_ARGS__); cout << '\n';}

void pre() {

}

struct TestCase {

    TestCase() {

    }

    void solve() {

    }
};

int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    pre();
    int te = 1;
    // cin >> te;
    int single = -1;
    dbg({ if (argc >= 2) single = atoi(argv[1]); })
    rep(test, 1, te + 1) {
        debug(test);
        TestCase tc;
        if (single == -1 || test == single) tc.solve();
    }
}