
template <typename T, typename D>
struct DPNode {
    T val;
    std::optional<D> data;
    std::vector<int> children;

    static std::vector<DPNode> nodes;
    static int make(const DPNode& node);
    void dfs(std::vector<D> &out) {
        if (data) {
            out.push_back(data.value());
        }
        for (int child : children) {
            nodes[child].dfs(out);
        }
    }
};

template <typename T, typename D>
std::vector<DPNode<T, D>> DPNode<T, D>::nodes;

template<typename T, typename D>
int DPNode<T, D>::make(const DPNode& node) {
    int id = nodes.size();
    nodes.push_back(node);
    return id;
}

template <typename T, typename D>
struct DP {
    using Node = DPNode<T, D>;
    int id;
    DP(T val, std::optional<D> data = std::nullopt, std::vector<int> children = {}) {
        id = Node::make({val, data, children});
    }
    operator T() const {
        return Node::nodes[id].val;
    }
    T operator()() const {
        return Node::nodes[id].val;
    }
    DP operator+(const DP &o) const {
        return DP(Node::nodes[id].val + Node::nodes[o.id].val, std::nullopt, {id, o.id});
    }
    DP operator-(const DP &o) const {
        return DP(Node::nodes[id].val - Node::nodes[o.id].val, std::nullopt, {id, o.id});
    }
    DP operator*(const DP &o) const {
        return DP(Node::nodes[id].val * Node::nodes[o.id].val, std::nullopt, {id, o.id});
    }
    DP operator/(const DP &o) const {
        return DP(Node::nodes[id].val / Node::nodes[o.id].val, std::nullopt, {id, o.id});
    }
    DP operator%(const DP &o) const {
        return DP(Node::nodes[id].val % Node::nodes[o.id].val, std::nullopt, {id, o.id});
    }
    DP operator^(const DP &o) const {
        return DP(Node::nodes[id].val ^ Node::nodes[o.id].val, std::nullopt, {id, o.id});
    }
    DP operator|(const DP &o) const {
        return DP(Node::nodes[id].val | Node::nodes[o.id].val, std::nullopt, {id, o.id});
    }
    DP operator&(const DP &o) const {
        return DP(Node::nodes[id].val & Node::nodes[o.id].val, std::nullopt, {id, o.id});
    }
    bool operator<(const DP &o) const {
        return Node::nodes[id].val < Node::nodes[o.id].val;
    }
    bool operator>(const DP &o) const {
        return Node::nodes[id].val > Node::nodes[o.id].val;
    }
    bool operator<=(const DP &o) const {
        return Node::nodes[id].val <= Node::nodes[o.id].val;
    }
    bool operator>=(const DP &o) const {
        return Node::nodes[id].val >= Node::nodes[o.id].val;
    }
    bool operator==(const DP &o) const {
        return Node::nodes[id].val == Node::nodes[o.id].val;
    }
    bool operator!=(const DP &o) const {
        return Node::nodes[id].val != Node::nodes[o.id].val;
    }
    DP& tag(D data) {
        Node::nodes[id].data = data;
        return *this;
    }
    std::vector<D> trace() const {
        std::vector<D> out;
        Node::nodes[id].dfs(out);
        return out;
    }
};
