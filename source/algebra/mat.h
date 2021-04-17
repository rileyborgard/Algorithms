
template<typename T, size_t N, size_t M>
struct mat : array<array<T, M>, N> {
    mat(T diag = T()) {
        for(size_t i = 0; i < N; i++) {
            for(size_t j = 0; j < M; j++) {
                if(i == j) {
                    (*this)[i][j] = diag;
                }else {
                    (*this)[i][j] = T();
                }
            }
        }
    }
    mat<T, N, M> operator+(const mat<T, N, M> &o) const {
        mat<T, N, M> X;
        for(size_t i = 0; i < N; i++) {
            for(size_t j = 0; j < M; j++) {
                X[i][j] = (*this)[i][j] + o[i][j];
            }
        }
        return X;
    }
    template<size_t P>
    mat<T, N, P> operator*(const mat<T, M, P> &o) const {
        mat<T, N, P> X;
        for(size_t i = 0; i < N; i++) {
            for(size_t j = 0; j < P; j++) {
                for(size_t k = 0; k < M; k++) {
                    X[i][j] += (*this)[i][k] * o[k][j];
                }
            }
        }
        return X;
    }
    mat<T, N, M> operator*(const T &c) const {
        mat<T, N, M> X;
        for(size_t i = 0; i < N; i++) {
            for(size_t j = 0; j < M; j++) {
                X[i][j] = (*this)[i][j] * c;
            }
        }
        return X;
    }
    array<T, N> operator*(const array<T, M> &x) const {
        array<T, N> y{};
        for(size_t i = 0; i < N; i++) {
            for(size_t j = 0; j < M; j++) {
                y[i] += (*this)[i][j] * x[j];
            }
        }
        return y;
    }
    mat<T, N, N> pow(size_t b) const {
        mat<T, N, N> X(1), A = *this;
        while(b > 0) {
            if(b & 1) {
                X = X * A;
            }
            A = A * A;
            b /= 2;
        }
        return X;
    }
    mat<T, M, N> t() const {
        mat<T, M, N> X;
        for(size_t i = 0; i < N; i++) {
            for(size_t j = 0; j < M; j++) {
                X[j][i] = (*this)[i][j];
            }
        }
        return X;
    }
};

template<typename T, size_t N, size_t M>
ostream& operator<<(ostream &os, const mat<T, N, M> &A) {
    for(size_t i = 0; i < N; i++) {
        for(size_t j = 0; j < M; j++) {
            os << A[i][j] << ' ';
        }
        os << '\n';
    }
    return os;
}

template<typename T, size_t N>
ostream& operator<<(ostream &os, const array<T, N> &v) {
    for(size_t i = 0; i < 2; i++) {
        os << v[i] << ' ';
    }
    return os;
}
