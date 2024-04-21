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
void PRINT(T &&head, V &&... tail) {
    cout << head << ' ';
    if constexpr (sizeof...(tail)) {
        PRINT(tail...);
    }
}
void PRINT() {}
#define PRINTLN(...) {OUTPUT_PRINT(__VA_ARGS__); cout << '\n';}

#ifndef ONLINE_JUDGE
template <typename T, typename... V>
void DEBUG_PRINT(const char *names, T &&head, V &&... tail) {
    int i = 0;
    while (names[i] != ',' && names[i] != '\0') i++;
    cerr.write(names, i);
    cerr << " = " << head;
    if constexpr (sizeof...(tail)) {
        cerr << ", ";
        DEBUG_PRINT(names + i + 2, tail...);
    } else {
        cerr << endl;
    }
}
#define DEBUG(...) {cerr << "\033[30m" "[" << __LINE__ << "] "; DEBUG_PRINT(#__VA_ARGS__, __VA_ARGS__); cerr << "\033[0m";}
#define ERROR(x) {cerr << "\033[31m" "[" << __LINE__ << "] "; cerr << (x) << '\n'; cerr << "\033[0m";}
#define LOG(x) {cerr << "\033[36m" "[" << __LINE__ << "] "; cerr << (x) << '\n'; cerr << "\033[0m";}
#else
#define DEBUG(...)
#define ERROR(x)
#define LOG(x)
#endif

struct TestCase {
    
    TestCase() {
        parse();
    }
    void parse();
    void solve();
};

void TestCase::parse() {
    
}

void TestCase::solve() {
    
}

int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int te = 1;
    // cin >> te;
    int single = -1;
    #ifndef ONLINE_JUDGE
    if (argc >= 2) single = atoi(argv[1]);
    #endif
    rep(test, 1, te + 1) {
        DEBUG(test);
        TestCase tc;
        if (single == -1 || test == single) tc.solve();
    }
}