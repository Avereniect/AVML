#ifndef AVML_MATRICES_HPP
#define AVML_MATRICES_HPP

#include "impl/Vector.hpp"

namespace avml {

    template<class T, unsigned N, unsigned M>
    class Matrix {
        static_assert(1 < N && N < 5);
        static_assert(1 < M && M < 5);
    public:

        using Vector = Vector<T, M>;

        //=================================================
        // Constructors
        //=================================================

        Matrix(T t) {
            for (int i = 0; i < std::min(N, M); ++i) {
                elems[i][i] = t;
            }
        }

        Matrix(Vector a, Vector b) {
            std::enable_if_t<M == 2, int> dummy{};

            elems[0] = a;
            elems[1] = b;
        }

        Matrix(Vector a, Vector b, Vector c) {
            std::enable_if_t<M == 3, int> dummy{};

            elems[0] = a;
            elems[1] = b;
            elems[2] = c;
        }

        Matrix(Vector a, Vector b, Vector c, Vector d) {
            std::enable_if_t<M == 4, int> dummy{};

            elems[0] = a;
            elems[1] = b;
            elems[2] = c;
            elems[3] = d;
        }

        Matrix() = default;
        Matrix(const Matrix&) = default;
        Matrix(Matrix&&) noexcept = default;
        ~Matrix() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Matrix& operator=(const Matrix&) = default;

        Matrix& operator=(Matrix&&) noexcept = default;

        //=================================================
        // Arithmetic assignment operators
        //=================================================

        template<unsigned O>
        Matrix& operator*=(const Matrix<T, M, O>& rhs) {}

        template<unsigned O>
        Matrix<T, N, O> operator*=(const Vector rhs) {
            Matrix<T, N, O> matrix{};

            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < O; ++j) {
                    for (int k = 0; k < M; ++k) {
                        matrix[i][j] += elems[i][k] * rhs[k][j];
                    }
                }
            }

            return matrix;
        }

        Matrix& operator*=(T t) {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < M; ++j) {
                    elems[i][j] *= t;
                }
            }

            return *this;
        }

        //=================================================
        // Arithmetic operators
        //=================================================

        Vector operator*(const Vector rhs) {
            Vector ret{};

            for (int i = 0; i < M; ++i) {
                for (int j = 0; j < N; ++j) {
                    ret[i] += (elems[i][j] * rhs[j]);
                }
            }

            return ret;
        }

        Matrix operator*(const T t) {
            auto temp = *this;
            temp *= t;
            return temp;
        }

        friend Matrix operator*(const T lhs, Matrix rhs) {
            return rhs *= lhs;
        }

        //=================================================
        // Comparator
        //=================================================

        bool operator==(const Matrix& rhs) const {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < M; ++j) {
                    if (elems[i][j] != rhs[i][j]) {
                        return false;
                    }
                }
            }
            return true;
        }

        bool operator!=(const Matrix& rhs) const {
            return !(*this == rhs);
        }

        //=================================================
        // Accessors
        //=================================================

        Vector& operator[](unsigned i) {
            return elems[i % M];
        }

        Vector operator[](unsigned i) const {
            return elems[i % M];
        }

        float* data() {
            return elems[0][0];
        }

        const float* data() const {
            return elems[0][0];
        }

        constexpr std::array<std::size_t, 2> dimensions() const {
            return {N, M};
        }

    private:

        Vector elems[M]{};

    };

    using Mat2x2 = Matrix<float, 2, 2>;
    using Mat2x3 = Matrix<float, 2, 3>;
    using Mat2x4 = Matrix<float, 2, 4>;

    using Mat3x2 = Matrix<float, 3, 2>;
    using Mat3x3 = Matrix<float, 3, 3>;
    using Mat3x4 = Matrix<float, 3, 4>;

    using Mat4x2 = Matrix<float, 4, 2>;
    using Mat4x3 = Matrix<float, 4, 3>;
    using Mat4x4 = Matrix<float, 4, 4>;

}

#endif //AVML_MATRICES_HPP
