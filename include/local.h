
#define dbg(...) __VA_ARGS__

template <typename T, typename U>
std::ostream& operator<<(std::ostream &os, const std::pair<T, U>& p) {
    return os << "(" << p.first << ", " << p.second << ")";
}

template <typename T>
std::ostream& operator<<(std::ostream &os, const std::vector<T> &ve) {
    if (os.rdbuf() == std::cerr.rdbuf()) {
        int n = std::min((int) ve.size(), 50);
        os << "[ ";
        for (int i = 0; i < n; i++) {
            os << ve[i];
            if (i < n - 1) os << ", ";
        }
        if (n < (int) ve.size()) os << "...";
        os << " ]";
    } else {
        int n = ve.size();
        for (int i = 0; i < n; i++) {
            os << ve[i];
            if (i < n - 1) os << ' ';
        }
    }
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream &os, const std::vector<std::vector<T>> &ve) {
    if (os.rdbuf() == std::cerr.rdbuf()) {
        int n = std::min((int) ve.size(), 50);
        os << "[ ";
        for (int i = 0; i < n; i++) {
            os << ve[i];
            if (i < n - 1) os << ", ";
        }
        if (n < (int) ve.size()) os << "...";
        os << " ]";
    } else {
        int n = ve.size();
        for (int i = 0; i < n; i++) {
            os << ve[i];
            if (i < n - 1) os << '\n';
        }
    }
    return os;
}

template <typename T, typename... V>
void _debug(const char *names, T &&head, V &&... tail) {
    int i = 0;
    while (names[i] != ',' && names[i] != '\0') i++;
    std::cerr.write(names, i);
    std::cerr << " = " << head;
    if constexpr (sizeof...(tail)) {
        std::cerr << ", ";
        _debug(names + i + 2, tail...);
    } else {
        std::cerr << std::endl;
    }
}

template <typename T, typename... V>
void _log(T &&head, V &&... tail) {
    std::cerr << head << ' ';
    if constexpr (sizeof...(tail)) {
        _log(tail...);
    }
}
void _log() {}

#define debug(...) {std::cerr << "\033[30m" "[" << __LINE__ << "] "; _debug(#__VA_ARGS__, __VA_ARGS__); std::cerr << "\033[0m";}
#define error(...) {std::cerr << "\033[31m" "[" << __LINE__ << "] "; _log(__VA_ARGS__); std::cerr << "\033[0m";}
#define info(...) {std::cerr << "\033[36m" "[" << __LINE__ << "] "; _log(__VA_ARGS__); std::cerr << "\n\033[0m";}
