
enum Diagonal { diagonal };

template <typename T>
struct Slice {
private:
    T* data_;
    size_t size_;
    size_t stride_;

public:
    Slice(T* data, size_t size, size_t stride = 1)
        : data_(data), size_(size), stride_(stride) {}

    inline T* data() { return data_; }
    inline const T* data() const { return data_; }
    inline size_t size() const { return size_; }
    inline size_t stride() const { return stride_; }

    inline T& operator[](size_t i) { return data_[i * stride_]; }
    inline const T& operator[](size_t i) const { return data_[i * stride_]; }

    template <bool IsConst>
    struct iter {
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using reference = std::conditional_t<IsConst, const T&, T&>;
        using pointer   = std::conditional_t<IsConst, const T*, T*>;
        using iterator_category = std::random_access_iterator_tag;

        pointer ptr;
        size_t stride;

        iter(pointer p, size_t s) : ptr(p), stride(s) {}

        reference operator*() const { return *ptr; }
        pointer operator->() const { return ptr; }

        iter& operator++() { ptr += stride; return *this; }
        iter operator++(int) { auto t = *this; ++(*this); return t; }
        iter& operator--() { ptr -= stride; return *this; }
        iter operator--(int) { auto t = *this; --(*this); return t; }

        iter& operator+=(difference_type n) { ptr += n * stride; return *this; }
        iter& operator-=(difference_type n) { ptr -= n * stride; return *this; }

        friend iter operator+(iter it, difference_type n) { return it += n; }
        friend iter operator-(iter it, difference_type n) { return it -= n; }

        friend difference_type operator-(const iter& a, const iter& b) {
            return (a.ptr - b.ptr) / (difference_type)a.stride;
        }

        friend bool operator==(const iter& a, const iter& b) { return a.ptr == b.ptr; }
        friend bool operator!=(const iter& a, const iter& b) { return a.ptr != b.ptr; }
        friend bool operator<(const iter& a, const iter& b) { return a.ptr < b.ptr; }
    };

    using iterator = iter<false>;
    using const_iterator = iter<true>;

    iterator begin() { return iterator(data_, stride_); }
    iterator end() { return iterator(data_ + size_ * stride_, stride_); }
    const_iterator begin() const { return const_iterator(data_, stride_); }
    const_iterator end() const { return const_iterator(data_ + size_ * stride_, stride_); }
    const_iterator cbegin() const { return begin(); }
    const_iterator cend() const { return end(); }
};

template <typename T>
struct Vector {
private:
    std::vector<T> a_;

public:
    Vector() : a_() {}
    Vector(std::initializer_list<T> a) : a_(a) {}
    Vector(size_t n, T x = T()) : a_(n, x) {}
    Vector(std::vector<T> a) : a_(std::move(a)) {}
    Vector(const Slice<T>& slice) : a_(slice.begin(), slice.end()) {}

    inline T* data() { return a_.data(); }
    inline const T* data() const { return a_.data(); }
    inline size_t size() const { return a_.size(); }

    inline T& operator[](size_t i) { return a_[i]; }
    inline const T& operator[](size_t i) const { return a_[i]; }

    auto begin() { return a_.begin(); }
    auto end() { return a_.end(); }
    auto begin() const { return a_.begin(); }
    auto end() const { return a_.end(); }

    Vector<T> operator+() const { return *this; }
    Vector<T> operator-() const {
        Vector res(size());
        for (size_t i = 0; i < size(); i++) res[i] = -(*this)[i];
        return res;
    }
    Vector<T> operator+(const Vector<T> &v) const {
        assert(size() == v.size());
        Vector res(size());
        for (size_t i = 0; i < size(); i++) res[i] = (*this)[i] + v[i];
        return res;
    }
    Vector<T> operator-(const Vector<T> &v) const {
        assert(size() == v.size());
        Vector res(size());
        for (size_t i = 0; i < size(); i++) res[i] = (*this)[i] - v[i];
        return res;
    }
    Vector<T> operator*(const T &c) const {
        Vector res(size());
        for (size_t i = 0; i < size(); i++) res[i] = (*this)[i] * c;
        return res;
    }
    friend Vector<T> operator*(const T &c, const Vector<T> &v) {
        Vector<T> res(v.size());
        for (size_t i = 0; i < size(); i++) res[i] = c * v[i];
        return res;
    }
    Vector<T> operator/(const T &c) const {
        Vector res(size());
        for (size_t i = 0; i < size(); i++) res[i] = (*this)[i] / c;
        return res;
    }

    Vector<T>& operator+=(const Vector<T> &v) {
        assert(size() == v.size());
        for (size_t i = 0; i < size(); i++) (*this)[i] += v[i];
        return *this;
    }
    Vector<T>& operator-=(const Vector<T> &v) {
        assert(size() == v.size());
        for (size_t i = 0; i < size(); i++) (*this)[i] -= v[i];
        return *this;
    }
    Vector<T>& operator*=(T c) {
        for (size_t i = 0; i < size(); i++) (*this)[i] *= c;
        return *this;
    }
    Vector<T>& operator/=(T c) {
        for (size_t i = 0; i < size(); i++) (*this)[i] /= c;
        return *this;
    }

    bool operator==(const Vector<T> &v) const {
        if (size() != v.size()) return false;
        for (size_t i = 0; i < size(); i++) {
            if ((*this)[i] != v[i]) return false;
        }
        return true;
    }
    bool operator!=(const Vector<T> &v) const {
        return !(*this == v);
    }

    T dot(const Vector<T> &v) const {
        T res = T();
        for (size_t i = 0; i < size(); i++) res += (*this)[i] * v[i];
        return res;
    }

    template <typename U = T>
    typename std::enable_if<std::is_floating_point<U>::value, U>::type
    norm() const { return std::sqrt(dot(*this)); }

    T norm2() const { return dot(*this); }

    template <typename U = T>
    typename std::enable_if<std::is_floating_point<U>::value, void>::type
    normalize() {
        T len = norm();
        for (auto& x : a_) x /= len;
    }

    template <typename U = T>
    typename std::enable_if<std::is_floating_point<U>::value, Vector<U>>::type
    normalized() const {
        Vector<T> res(*this);
        res.normalize();
        return res;
    }

    template <typename U = T>
    typename std::enable_if<std::is_floating_point<U>::value, U>::type
    distance(const Vector<T> &v) const { return (*this - v).norm(); }

    T distance2(const Vector<T> &v) const { return (*this - v).norm2(); }

    template <typename U = T>
    typename std::enable_if<std::is_floating_point<U>::value, U>::type
    angle(const Vector<T> &v) const { return acos(dot(v)); }

    friend std::ostream& operator<<(std::ostream &out, const Vector<T> &v) {
        for (size_t i = 0; i < v.size(); i++) {
            out << v[i];
            if (i + 1 < v.size()) out << " ";
        }
        return out;
    }

    operator std::span<T>() {
        return std::span<T>(data(), size());
    }

    operator Slice<T>() {
        return Slice<T>(data(), size());
    }
};

template <typename T>
struct Matrix {
private:
    size_t n_;
    size_t m_;
    Vector<T> a_;

public:
    Matrix() : n_(0), m_(0), a_() {}
    Matrix(size_t n, size_t m, T e = T()) : n_(n), m_(m), a_(n * m, e) {}
    Matrix(Diagonal, size_t n, T diag, T zero = T()) : n_(n), m_(n), a_(n * n, zero) {
        for (size_t i = 0, idx = 0; i < n; i++, idx += n + 1) a_[idx] = diag;
    }
    static Matrix identity(size_t n, T one = T(1), T zero = T()) {
        return Matrix(Diagonal{}, n, one, zero);
    }
    Matrix(size_t n, size_t m, Vector<T> a) : n_(n), m_(m), a_(std::move(a)) {
        assert(a_.size() == n_ * m_);
    }
    Matrix(std::initializer_list<std::initializer_list<T>> l) : n_(l.size()), m_(l.begin()->size()), a_(n_ * m_) {
        assert(n_ > 0);
        assert(m_ > 0);
        size_t idx = 0;
        for (auto row_iter = l.begin(); row_iter != l.end(); ++row_iter) {
            assert(row_iter->size() == m_);
            std::copy(row_iter->begin(), row_iter->end(), a_.begin() + idx);
            idx += m_;
        }
    }

    inline const T* data() const { return a_.data(); }
    inline T* data() { return a_.data(); }
    inline size_t height() const { return n_; }
    inline size_t width() const { return m_; }

    inline T& at(size_t i, size_t j) { return a_[i * width() + j]; }
    inline const T& at(size_t i, size_t j) const { return a_[i * width() + j]; }
    inline T& operator()(size_t i, size_t j) { return a_[i * width() + j]; }
    inline const T& operator()(size_t i, size_t j) const { return a_[i * width() + j]; }

    inline Slice<T> operator[](size_t i) { return { &a_[i * width()], width(), 1 }; }
    inline const Slice<T> operator[](size_t i) const { return { &a_[i * width()], width(), 1 }; }
    inline Slice<T> row(size_t i) { return { &a_[i * width()], width(), 1 }; }
    inline const Slice<T> row(size_t i) const { return { &a_[i * width()], width(), 1 }; }
    inline Slice<T> col(size_t j) { return { &a_[j], height(), width() }; }
    inline const Slice<T> col(size_t j) const { return { &a_[j], height(), width() }; }

    Matrix<T> operator+() const { return *this; }
    Matrix<T> operator-() const { return Matrix<T>(n_, m_, -a_); }
    Matrix operator+(const Matrix& m) const {
        assert(n_ == m.n_ && m_ == m.m_);
        return Matrix(n_, m_, a_ + m.a_);
    }
    Matrix operator-(const Matrix& m) const {
        assert(n_ == m.n_ && m_ == m.m_);
        return Matrix(n_, m_, a_ - m.a_);
    }
    Matrix<T> operator*(const T &c) const { return Matrix<T>(n_, m_, a_ * c); }
    friend Matrix<T> operator*(const T &c, const Matrix<T> &m) { return Matrix<T>(m.n_, m.m_, c * m.a_); }
    Matrix<T> operator/(const T &c) const { return Matrix<T>(n_, m_, a_ / c); }

    Matrix<T>& operator+=(const Matrix<T> &m) {
        assert(n_ == m.n_ && m_ == m.m_);
        a_ += m.a_;
        return *this;
    }
    Matrix<T>& operator-=(const Matrix<T> &m) {
        assert(n_ == m.n_ && m_ == m.m_);
        a_ -= m.a_;
        return *this;
    }
    Matrix<T>& operator*=(const T& c) {
        a_ *= c;
        return *this;
    }
    Matrix<T>& operator/=(const T& c) {
        a_ /= c;
        return *this;
    }

    Vector<T> operator*(const Slice<T> &v) const {
        assert(width() == v.size());
        Vector<T> res(height());
        for (size_t i = 0; i < height(); i++)
            for (size_t j = 0; j < width(); j++)
                res[i] += at(i, j) * v[j];
        return res;
    }

    friend Vector<T> operator*(const Slice<T> &v, const Matrix<T> &m) {
        assert(v.size() == m.height());
        Vector<T> res(m.width());
        for (size_t i = 0; i < m.height(); i++)
            for (size_t j = 0; j < m.width(); j++)
                res[j] += v[i] * m(i, j);
        return res;
    }

    Matrix<T> operator*(const Matrix<T> &m) const {
        assert(width() == m.height());
        Matrix<T> res(height(), m.width());
        for (size_t i = 0; i < height(); i++)
            for (size_t k = 0; k < width(); k++)
                for (size_t j = 0; j < m.width(); j++)
                    res(i, j) += at(i, k) * m(k, j);
        return res;
    }
    Matrix<T> transpose() const {
        Matrix<T> res(m_, n_);
        for (size_t i = 0; i < n_; i++)
            for (size_t j = 0; j < m_; j++)
                res(j, i) = at(i, j);
        return res;
    }

    friend std::ostream& operator<<(std::ostream &out, const Matrix<T> &m) {
        for (size_t i = 0; i < m.height(); i++) {
            for (size_t j = 0; j < m.width(); j++) {
                out << m(i, j);
                if (j + 1 < m.width()) out << " ";
            }
            if (i + 1 < m.height()) out << '\n';
        }
        return out;
    }

};
