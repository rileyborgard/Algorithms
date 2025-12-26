
// struct update {
//     bool type;
//     update() {
//         type = 0;
//     }
// };

template<typename D, typename U>
struct noam : public D {
    vector<U> s;
    void push(const U &u) {
        D::push(u);
        s.push_back(u);
    }
    void pop() {
        auto i = s.end();
        int c = 0;
        do {
            c += (--i)->type ? 1 : -1;
            D::pop();
        }while(c < 0 && i != s.begin());
        auto j = stable_partition(i, s.end(), [](auto &x) { return !x.type; });
        if(i == s.begin()) {
            reverse(i, j);
            for_each(i, j, [](auto &x) { x.type = 1; });
        }
        s.pop_back();
        while(i != s.end()) D::push(*i), i++;
    }
};