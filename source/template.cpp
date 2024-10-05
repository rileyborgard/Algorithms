// Source: https://github.com/rileyborgard/Algorithms/blob/main/source/template.cpp
#include <bits/stdc++.h>

#define ll long long
#define sz(x) ((int) (x).size())
#define all(x) (x).begin(), (x).end()
#define vi vector<int>
#define pii pair<int, int>
#define rep(i, a, b) for(int i = (a); i < (b); i++)
using namespace std;
template<typename T>
using minpq = priority_queue<T, vector<T>, greater<T>>;

template<typename>
struct is_vector : std::false_type {};
template<typename T, typename A>
struct is_vector<std::vector<T,A>> : std::true_type {};
template<typename T>
ostream &operator<<(ostream &os, const vector<T> &ve) {
    if (os.rdbuf() == std::cerr.rdbuf()) {
        int n = min(sz(ve), 50);
        os << "[ ";
        rep(i, 0, n) {
            os << ve[i];
            if (i != n - 1) os << ", ";
        }
        if (n < sz(ve)) os << "...";
        os << " ]";
    } else {
        int n = sz(ve);
        rep(i, 0, n) {
            os << ve[i] << ' ';
            if constexpr(is_vector<T>::value) {
                os << '\n';
            }
        }
    }
    return os;
}
template <typename T, typename... V>
void print(T &&head, V &&... tail) {
    cout << head << ' ';
    if constexpr (sizeof...(tail)) {
        print(tail...);
    }
}
void print() {}
#define println(...) {print(__VA_ARGS__); cout << '\n';}

#ifdef LOCAL
#include <local.h>
#else
#define debug(...)
#define error(x)
#define log(x)
#endif

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
    #ifdef LOCAL
    if (argc >= 2) single = atoi(argv[1]);
    #endif
    rep(test, 1, te + 1) {
        debug(test);
        TestCase tc;
        if (single == -1 || test == single) tc.solve();
    }
}