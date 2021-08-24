#ifndef AVML_DEF_MATRIX2X2F_IPP
#define AVML_DEF_MATRIX2X2F_IPP

namespace avml {

    template<>
    class Matrix<float, 2, 2> {
    public:

        using scalar = float;
        using vector = Vector<float, 2>;

        static constexpr unsigned width = 2;
        static constexpr unsigned height = 2;

        //=================================================
        // Creation methods
        //=================================================

        AVML_FINL static Matrix read(const float* ptr) {
            Matrix ret;
            ret[0] = vector::read(ptr + 0x0);
            ret[1] = vector::read(ptr + 0x2);
            return ret;
        }

        AVML_FINL static Matrix read_aligned(const float* ptr) {
            Matrix ret;
            ret[0] = vector::read_aligned(ptr + 0x0);
            ret[1] = vector::read_aligned(ptr + 0x2);
            return ret;
        }

        //=================================================
        // -ctors
        //=================================================

        AVML_FINL explicit Matrix(float d) noexcept:
            elements {
                {d, 0.0f},
                {0.0f, d}
        } {}

        AVML_FINL Matrix(float a, float b, float c, float d):
            elements{
                {a, b},
                {c, d}
            } {}

        AVML_FINL Matrix(vector a, vector b):
            elements{
                {a[0], a[1]},
                {b[0], b[1]}
        } {}

        Matrix() = default;
        Matrix(const Matrix&) = default;
        Matrix(Matrix&&) = default;
        ~Matrix() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Matrix& operator=(const Matrix&) = default;
        Matrix& operator=(Matrix&&) = default;

        //=================================================
        // Unary arithmetic operators
        //=================================================

        AVML_FINL Matrix operator+() const {
            return *this;
        }

        AVML_FINL Matrix operator-() const {
            return Matrix{
                -operator[](0),
                -operator[](1)
            };
        }

        //=================================================
        // Arithmetic assignment operators
        //=================================================

        AVML_FINL Matrix& operator*=(scalar rhs) {
            for (unsigned i = 0; i < height; ++i) {
                operator[](i) *= rhs;
            }
            return *this;
        }

        AVML_FINL Matrix& operator/=(scalar rhs) {
            for (unsigned i = 0; i < height; ++i) {
                 operator[](i) /= rhs;
            }
            return *this;
        }

        AVML_FINL Matrix& operator+=(const Matrix& rhs) {
            for (unsigned i = 0; i < height; ++i) {
                operator[](i) += rhs[i];
            }
            return *this;
        }

        AVML_FINL Matrix& operator-=(const Matrix& rhs) {
            for (unsigned i = 0; i < height; ++i) {
                 operator[](i) -= rhs[i];
            }
            return *this;
        }

        AVML_FINL Matrix& operator*=(const Matrix& rhs) {
            auto ret = *this;
            for (unsigned i = 0; i < height; ++i) {
                for (unsigned j = 0; j < width; ++j) {
                    float tmp = 0.0f;
                    for (unsigned k = 0; j < width; ++k) {
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

        AVML_FINL float* data() {
            return elements[0];
        }

        AVML_FINL const float* data() const {
            return elements[0];
        }

    private:

        float elements[2][2] {
            {0.0f, 0.0f},
            {0.0f, 0.0f}
        };

    };

    const Matrix<float, 2, 2> Identity2f{1.0f};

    AVML_FINL bool operator==(const mat2x2f& lhs, const mat2x2f& rhs) {
        bool ret = true;
        for (unsigned i = 0; i < mat2x2f::height; ++i) {
            ret &= (lhs[i] == rhs[i]);
        }
        return ret;
    }

    AVML_FINL bool operator!=(const mat2x2f& lhs, const mat2x2f& rhs) {
        return !(lhs == rhs);
    }

    AVML_FINL mat2x2f operator+(mat2x2f lhs, mat2x2f rhs) {
        lhs += rhs;
        return lhs;
    }

    AVML_FINL mat2x2f operator-(mat2x2f lhs, mat2x2f rhs) {
        lhs -= rhs;
        return lhs;
    }

    AVML_FINL mat2x2f operator*(mat2x2f lhs, float rhs) {
        lhs *= rhs;
        return lhs;
    }

    AVML_FINL mat2x2f operator*(float lhs, mat2x2f rhs) {
        rhs *= lhs;
        return rhs;
    }

    AVML_FINL mat2x2f operator/(mat2x2f lhs, float rhs) {
        lhs /= rhs;
        return lhs;
    }

    AVML_FINL mat2x2f operator*(mat2x2f lhs, mat2x2f rhs) {
        lhs *= rhs;
        return lhs;
    }

    AVML_FINL vec2f operator*(mat2x2f lhs, vec2f rhs) {
        vec2f ret{};

        for (unsigned i = 0; i < mat2x2f::height; ++i) {
            for (unsigned j = 0; j < mat2x2f::width; ++j) {
                ret[i] += lhs[i][j] * rhs[j];
            }
        }

        return ret;
    }

    AVML_FINL mat2x2f transpose(const mat2x2f m) {
        mat2x2f ret;

        for (unsigned i = 0; i < mat2x2f::height; ++i) {
            for (unsigned j = 0; j < mat2x2f::width; ++j) {
                ret[j][i] = m[i][j];
            }
        }

        return ret;
    }

    AVML_FINL float determinant(const mat2x2f& m) {
        return m[0][0] * m[1][1] - m[0][1] * m[1][0];
    }

    AVML_FINL mat2x2f inverse(const mat2x2f& m) {
        auto det = determinant(m);

        if (det < (1.0f / 65536.0f)) {
            return mat2x2f{NAN, NAN, NAN, NAN};
        }

        return mat2x2f {
             m[1][1],
            -m[1][0],
            -m[0][1],
             m[0][0]
        } / det;
    }

}

#endif
