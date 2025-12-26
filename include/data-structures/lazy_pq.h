
template <typename T, class Compare = std::less<T>>
struct lazy_pq {
    priority_queue<T, vector<T>, Compare> q, d;
    lazy_pq() {}
    lazy_pq(const vector<T> &ve) : q(Compare(), ve) {}
    size_t size() { return q.size() - d.size(); }
    void push(T x) { q.push(x); }
    void clean() {
        Compare comp;
        while (!q.empty() && !d.empty() && !comp(d.top(), q.top())) {
            q.pop();
            d.pop();
        }
    }
    T top() {
        clean();
        return q.top();
    }
    void pop() {
        clean();
        q.pop();
    }
    void erase(T x) {
        d.push(x);
    }
};
