
template <typename IterT, typename T>
bool next_array(IterT begin, IterT end, T mx) {
    IterT it = end;
    while (it != begin) {
        --it;
        T val = *it;
        ++val;
        if (val == mx) {
            *it = T();
        } else {
            *it = val;
            return true;
        }
    }
    return false;
}
