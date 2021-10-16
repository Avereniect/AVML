#ifndef AVML_DEF_MATRIX2X2_IPP
#define AVML_DEF_MATRIX2X2_IPP

namespace avml {

    template<class R>
    class alignas(alignof(R) * 2 * 2) Matrix2x2 {
    public:

        using scalar = R;
        using vector = Vector2<R>;

        static constexpr unsigned width = 2;
        static constexpr unsigned height = 2;

        //=================================================
        // Creation methods
        //=================================================

        AVML_FINL static Matrix2x2 read(const R* ptr) {
            Matrix2x2 ret;
            ret[0] = vector::read(ptr + 0x0);
            ret[1] = vector::read(ptr + 0x2);
            return ret;
        }

        AVML_FINL static Matrix2x2 read_aligned(const R* ptr) {
            Matrix2x2 ret;
            ret[0] = vector::read_aligned(ptr + 0x0);
            ret[1] = vector::read_aligned(ptr + 0x2);
            return ret;
        }

        //=================================================
        // -ctors
        //=================================================

        AVML_FINL explicit Matrix2x2(R d) noexcept:
            elements {
                {d, 0.0f},
                {0.0f, d}
        } {}

        AVML_FINL Matrix2x2(R a, R b, R c, R d):
            elements{
                {a, b},
                {c, d}
            } {}

        AVML_FINL Matrix2x2(vector a, vector b):
            elements{
                {a[0], a[1]},
                {b[0], b[1]}
        } {}

        Matrix2x2() = default;
        Matrix2x2(const Matrix2x2&) = default;
        Matrix2x2(Matrix2x2&&) = default;
        ~Matrix2x2() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Matrix2x2& operator=(const Matrix2x2&) = default;
        Matrix2x2& operator=(Matrix2x2&&) = default;

        //=================================================
        // Unary arithmetic operators
        //=================================================

        AVML_FINL Matrix2x2 operator+() const {
            return *this;
        }

        AVML_FINL Matrix2x2 operator-() const {
            return Matrix2x2{
                -operator[](0),
                -operator[](1)
            };
        }

        //=================================================
        // Arithmetic assignment operators
        //=================================================

        AVML_FINL Matrix2x2& operator*=(scalar rhs) {
            for (unsigned i = 0; i < height; ++i) {
                operator[](i) *= rhs;
            }
            return *this;
        }

        AVML_FINL Matrix2x2& operator/=(scalar rhs) {
            for (unsigned i = 0; i < height; ++i) {
                 operator[](i) /= rhs;
            }
            return *this;
        }

        AVML_FINL Matrix2x2& operator+=(const Matrix2x2& rhs) {
            for (unsigned i = 0; i < height; ++i) {
                operator[](i) += rhs[i];
            }
            return *this;
        }

        AVML_FINL Matrix2x2& operator-=(const Matrix2x2& rhs) {
            for (unsigned i = 0; i < height; ++i) {
                 operator[](i) -= rhs[i];
            }
            return *this;
        }

        AVML_FINL Matrix2x2& operator*=(const Matrix2x2& rhs) {
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

        R elements[2][2] {
            {0.0f, 0.0f},
            {0.0f, 0.0f}
        };

    };

    template<class R>
    AVML_FINL bool operator==(const Matrix2x2<R>& lhs, const Matrix2x2<R>& rhs) {
        bool ret = true;
        for (unsigned i = 0; i < Matrix2x2<R>::height; ++i) {
            ret &= (lhs[i] == rhs[i]);
        }
        return ret;
    }

    template<class R>
    AVML_FINL bool operator!=(const Matrix2x2<R>& lhs, const Matrix2x2<R>& rhs) {
        return !(lhs == rhs);
    }

    template<class R>
    AVML_FINL Matrix2x2<R> operator+(Matrix2x2<R> lhs, Matrix2x2<R> rhs) {
        lhs += rhs;
        return lhs;
    }

    template<class R>
    AVML_FINL Matrix2x2<R> operator-(Matrix2x2<R> lhs, Matrix2x2<R> rhs) {
        lhs -= rhs;
        return lhs;
    }

    template<class R>
    AVML_FINL Matrix2x2<R> operator*(Matrix2x2<R> lhs, R rhs) {
        lhs *= rhs;
        return lhs;
    }

    template<class R>
    AVML_FINL Matrix2x2<R> operator*(R lhs, Matrix2x2<R> rhs) {
        rhs *= lhs;
        return rhs;
    }

    template<class R>
    AVML_FINL Matrix2x2<R> operator/(Matrix2x2<R> lhs, R rhs) {
        lhs /= rhs;
        return lhs;
    }

    template<class R>
    AVML_FINL Matrix2x2<R> operator*(Matrix2x2<R> lhs, Matrix2x2<R> rhs) {
        lhs *= rhs;
        return lhs;
    }

    template<class R>
    AVML_FINL Vector2<R> operator*(Matrix2x2<R> lhs, Vector2<R> rhs) {
        Vector2<R> ret{};

        for (unsigned i = 0; i < Matrix2x2<R>::height; ++i) {
            for (unsigned j = 0; j < Matrix2x2<R>::width; ++j) {
                ret[i] += lhs[i][j] * rhs[j];
            }
        }

        return ret;
    }

    template<class R>
    AVML_FINL Matrix2x2<R> transpose(const Matrix2x2<R> m) {
        Matrix2x2<R> ret;

        for (unsigned i = 0; i < Matrix2x2<R>::height; ++i) {
            for (unsigned j = 0; j < Matrix2x2<R>::width; ++j) {
                ret[j][i] = m[i][j];
            }
        }

        return ret;
    }

    template<class R>
    AVML_FINL R determinant(const Matrix2x2<R>& m) {
        return m[0][0] * m[1][1] - m[0][1] * m[1][0];
    }

    template<class R>
    AVML_FINL Matrix2x2<R> inverse(const Matrix2x2<R>& m) {
        auto det = determinant(m);

        if (det < (1.0f / 65536.0f)) {
            return Matrix2x2<R>{NAN, NAN, NAN, NAN};
        }

        return Matrix2x2<R> {
             m[1][1],
            -m[1][0],
            -m[0][1],
             m[0][0]
        } / det;
    }

    template<class R, unsigned I = 0, unsigned J = 0>
    AVML_FINL Matrix2x2<R> extract2x2(const Matrix3x3<R> m) {
        static_assert(I < 2, "");
        static_assert(J < 2, "");

        Matrix2x2<R> ret;

        for (unsigned i = 0; i < Matrix2x2<R>::height; ++i) {
            for (unsigned j = 0; j < Matrix2x2<R>::width; ++j) {
                ret[i][j] = m[i + I][j + J];
            }
        }

        return ret;
    }

    template<class R, unsigned I = 0, unsigned J = 0>
    AVML_FINL Matrix2x2<R> extract2x2(const Matrix4x4<R> m) {
        static_assert(I < 3, "");
        static_assert(J < 3, "");

        Matrix2x2<R> ret;

        for (unsigned i = 0; i < Matrix2x2<R>::height; ++i) {
            for (unsigned j = 0; j < Matrix2x2<R>::width; ++j) {
                ret[i][j] = m[i + I][j + J];
            }
        }

        return ret;
    }

}

#endif
