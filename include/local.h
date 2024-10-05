
template <typename T, typename... V>
void _debug(const char *names, T &&head, V &&... tail) {
    int i = 0;
    while (names[i] != ',' && names[i] != '\0') i++;
    cerr.write(names, i);
    cerr << " = " << head;
    if constexpr (sizeof...(tail)) {
        cerr << ", ";
        _debug(names + i + 2, tail...);
    } else {
        cerr << endl;
    }
}
#define debug(...) {cerr << "\033[30m" "[" << __LINE__ << "] "; _debug(#__VA_ARGS__, __VA_ARGS__); cerr << "\033[0m";}
#define error(x) {cerr << "\033[31m" "[" << __LINE__ << "] "; cerr << (x) << '\n'; cerr << "\033[0m";}
#define log(x) {cerr << "\033[36m" "[" << __LINE__ << "] "; cerr << (x) << '\n'; cerr << "\033[0m";}
