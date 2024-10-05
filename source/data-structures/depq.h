
#include "lazy_pq.h"

template <typename T>
struct depq {
    lazy_pq<T> q_max;
    lazy_pq<T, greater<T>> q_min;

    depq() {}
    depq(const vector<T> &ve) : q_max(ve), q_min(ve) {}

    size_t size() {
        return q_max.size();
    }
    void push(T x) {
        q_max.push(x);
        q_min.push(x);
    }
    T get_min() {
        return q_min.top();
    }
    T get_max() {
        return q_max.top();
    }
    void pop_min() {
        q_max.erase(q_min.top());
        q_min.pop();
    }
    void pop_max() {
        q_min.erase(q_max.top());
        q_max.pop();
    }
    void erase(T x) {
        q_min.erase(x);
        q_max.erase(x);
    }
};