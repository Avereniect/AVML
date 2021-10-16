#ifndef AVML_DEF_MATRIX3X3_IPP
#define AVML_DEF_MATRIX3X3_IPP

namespace avml {

    template<class R>
    class  alignas(alignof(R) * 1 * 1) Matrix3x3 {
    public:

        using scalar = R;
        using vector = Vector3<R>;

        static constexpr unsigned width = 3;
        static constexpr unsigned height = 3;

        //=================================================
        // Creation methods
        //=================================================

        AVML_FINL static Matrix3x3 read(const R* ptr) {
            Matrix3x3 ret;
            ret[0] = vector::read(ptr + 0x0);
            ret[1] = vector::read(ptr + 0x3);
            ret[2] = vector::read(ptr + 0x6);
            return ret;
        }

        AVML_FINL static Matrix3x3 read_aligned(const R* ptr) {
            Matrix3x3 ret;
            ret[0] = vector::read_aligned(ptr + 0x0);
            ret[1] = vector::read_aligned(ptr + 0x3);
            ret[2] = vector::read_aligned(ptr + 0x6);
            return ret;
        }

        //=================================================
        // -ctors
        //=================================================

        AVML_FINL explicit Matrix3x3(R d):
            elements {
                {d, 0.0f, 0.0f},
                {0.0f, d, 0.0f},
                {0.0f, 0.0f, d}
        } {}

        AVML_FINL Matrix3x3(
            R a, R b, R c,
            R d, R e, R f,
            R g, R h, R i):
            elements{
                {a, b, c},
                {d, e, f},
                {g, h, i}
            } {}

        AVML_FINL Matrix3x3(vector a, vector b, vector c):
            elements{
                {a[0], a[1], a[2]},
                {b[0], b[1], b[2]},
                {c[0], c[1], c[2]}
        } {}

        Matrix3x3() = default;
        Matrix3x3(const Matrix3x3&) = default;
        Matrix3x3(Matrix3x3&&) = default;
        ~Matrix3x3() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Matrix3x3& operator=(const Matrix3x3&) = default;
        Matrix3x3& operator=(Matrix3x3&&) = default;

        //=================================================
        // Unary arithmetic operators
        //=================================================

        AVML_FINL Matrix3x3 operator+() const {
            return *this;
        }

        AVML_FINL Matrix3x3 operator-() const {
            return Matrix3x3{
                -operator[](0),
                -operator[](1),
                -operator[](2),
            };
        }

        //=================================================
        // Arithmetic assignment operators
        //=================================================

        AVML_FINL Matrix3x3& operator*=(scalar rhs) {
            for (unsigned i = 0; i < height; ++i) {
                operator[](i) *= rhs;
            }
            return *this;
        }

        AVML_FINL Matrix3x3& operator/=(scalar rhs) {
            for (unsigned i = 0; i < height; ++i) {
                operator[](i) /= rhs;
            }
            return *this;
        }

        AVML_FINL Matrix3x3& operator+=(const Matrix3x3& rhs) {
            for (unsigned i = 0; i < height; ++i) {
                operator[](i) += rhs[i];
            }
            return *this;
        }

        AVML_FINL Matrix3x3& operator-=(const Matrix3x3& rhs) {
            for (unsigned i = 0; i < height; ++i) {
                operator[](i) -= rhs[i];
            }
            return *this;
        }

        AVML_FINL Matrix3x3& operator*=(const Matrix3x3& rhs) {
            auto ret = *this;
            for (unsigned i = 0; i < height; ++i) {
                for (unsigned j = 0; j < width; ++j) {
                    R tmp = 0.0f;
                    for (unsigned k = 0; k < width; ++k) {
                        tmp += elements[i][k] * rhs.elements[k][j];
                    }
                    ret[i][j] = tmp;
                }
            }

            return *this;
        }

        //=================================================
        // Accessors
        //=================================================

        AVML_FINL vector& operator[](unsigned i) {
            return *reinterpret_cast<vector*>(elements[i]);
        }

        AVML_FINL const vector& operator[](unsigned i) const {
            return *reinterpret_cast<const vector*>(elements[i]);
        }

        AVML_FINL R* data() {
            return elements[0];
        }

        AVML_FINL const R* data() const {
            return elements[0];
        }

    private:

        R elements[3][3]{
            {0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f}
        };

    };

    template<class R>
    AVML_FINL bool operator==(const Matrix3x3<R>& lhs, const Matrix3x3<R>& rhs) {
        bool ret = true;
        for (unsigned i = 0; i < Matrix3x3<R>::height; ++i) {
            ret &= (lhs[i] == rhs[i]);
        }
        return ret;
    }

    template<class R>
    AVML_FINL bool operator!=(const Matrix3x3<R>& lhs, const Matrix3x3<R>& rhs) {
        return !(lhs == rhs);
    }

    template<class R>
    AVML_FINL Matrix3x3<R> operator+(Matrix3x3<R> lhs, Matrix3x3<R> rhs) {
        lhs += rhs;
        return lhs;
    }

    template<class R>
    AVML_FINL Matrix3x3<R> operator-(Matrix3x3<R> lhs, Matrix3x3<R> rhs) {
        lhs -= rhs;
        return lhs;
    }

    template<class R>
    AVML_FINL Matrix3x3<R> operator*(Matrix3x3<R> lhs, R rhs) {
        lhs *= rhs;
        return lhs;
    }

    template<class R>
    AVML_FINL Matrix3x3<R> operator*(R lhs, Matrix3x3<R> rhs) {
        rhs *= lhs;
        return rhs;
    }

    template<class R>
    AVML_FINL Matrix3x3<R> operator/(Matrix3x3<R> lhs, R rhs) {
        lhs /= rhs;
        return lhs;
    }

    template<class R>
    AVML_FINL Matrix3x3<R> operator*(Matrix3x3<R> lhs, Matrix3x3<R> rhs) {
        lhs *= rhs;
        return lhs;
    }

    template<class R>
    AVML_FINL Vector3<R> operator*(Matrix3x3<R> lhs, Vector3<R> rhs) {
        Vector3<R> ret{};

        for (unsigned i = 0; i < Matrix3x3<R>::height; ++i) {
            for (unsigned j = 0; j < Matrix3x3<R>::width; ++j) {
                ret[i] += lhs[i][j] * rhs[j];
            }
        }

        return ret;
    }

    template<class R>
    AVML_FINL Matrix3x3<R> transpose(const Matrix3x3<R> m) {
        Matrix3x3<R> ret;

        for (unsigned i = 0; i < Matrix3x3<R>::height; ++i) {
            for (unsigned j = 0; j < Matrix3x3<R>::width; ++j) {
                ret[j][i] = m[i][j];
            }
        }

        return ret;
    }

    template<class R>
    AVML_FINL R determinant(const Matrix3x3<R>& m) {
        return
            m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) -
            m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
            m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
    }

    template<class R>
    AVML_FINL Matrix3x3<R> inverse(const Matrix3x3<R>& m) {
        auto det = determinant(m);

        if (det < (1.0f / 32768.0f)) {
            return Matrix3x3<R> {
                NAN, NAN, NAN,
                NAN, NAN, NAN,
                NAN, NAN, NAN
            };
        }

        return Matrix3x3<R> {
             m[1][1] * m[2][2] - m[1][2] * m[2][1], -m[0][1] * m[2][2] + m[0][2] * m[2][1],  m[0][1] * m[1][2] - m[0][2] * m[1][1],
            -m[0][1] * m[2][2] - m[1][2] * m[2][0],  m[0][0] * m[2][2] - m[0][2] * m[2][0], -m[0][0] * m[1][2] - m[0][2] * m[1][0],
             m[1][0] * m[2][1] - m[1][1] * m[2][0], -m[0][0] * m[2][1] + m[0][1] * m[2][0],  m[0][0] * m[1][1] - m[0][1] * m[1][0]
        } / det;
    }

    template<class R, unsigned I = 0, unsigned J = 0>
    AVML_FINL Matrix3x3<R> extract3x3(const mat4x4f m) {
        static_assert(I < 3, "");
        static_assert(J < 3, "");

        Matrix3x3<R> ret;

        for (unsigned i = 0; i < Matrix3x3<R>::height; ++i) {
            for (unsigned j = 0; j < Matrix3x3<R>::width; ++j) {
                ret[i][j] = m[i + I][j + J];
            }
        }

        return ret;
    }

}

#endif
