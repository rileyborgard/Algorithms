
template <typename IterT, typename T = std::iter_value_t<IterT>>
std::vector<std::pair<T, int>> run_length(IterT begin, IterT end) {
    if (begin == end) return {};
    T prev = *begin;
    int cnt = 1;
    std::vector<std::pair<T, int>> res;
    for (IterT it = std::next(begin); it != end; ++it) {
        if (*it == prev) {
            ++cnt;
        } else {
            res.push_back({prev, cnt});
            prev = *it;
            cnt = 1;
        }
    }
    res.push_back({prev, cnt});
    return res;
}
