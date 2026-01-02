
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

template <typename IterT, typename T>
bool next_array_vec(IterT begin, IterT end, const std::vector<T>& mx) {
    IterT it = end;
    auto mxit = mx.end();
    while (it != begin) {
        --it;
        --mxit;
        T val = *it;
        ++val;
        if (val == *mxit) {
            *it = T();
        } else {
            *it = val;
            return true;
        }
    }
    return false;
}
