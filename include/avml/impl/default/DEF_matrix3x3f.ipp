#ifndef AVML_DEF_MATRIX3X3F_IPP
#define AVML_DEF_MATRIX3X3F_IPP

namespace avml {

    template<>
    class Matrix<float, 3, 3> {
    public:

        using scalar = float;
        using vector = Vector<float, 3>;

        static constexpr unsigned width = 3;
        static constexpr unsigned height = 3;

        //=================================================
        // Creation methods
        //=================================================

        AVML_FINL static Matrix read(const float* ptr) {
            Matrix ret;
            ret[0] = vector::read(ptr + 0x0);
            ret[1] = vector::read(ptr + 0x3);
            ret[2] = vector::read(ptr + 0x6);
            return ret;
        }

        AVML_FINL static Matrix read_aligned(const float* ptr) {
            Matrix ret;
            ret[0] = vector::read_aligned(ptr + 0x0);
            ret[1] = vector::read_aligned(ptr + 0x3);
            ret[2] = vector::read_aligned(ptr + 0x6);
            return ret;
        }

        //=================================================
        // -ctors
        //=================================================

        AVML_FINL Matrix(float d):
            elements {
                {d, 0.0f, 0.0f},
                {0.0f, d, 0.0f},
                {0.0f, 0.0f, d}
        } {}

        AVML_FINL Matrix(
            float a, float b, float c,
            float d, float e, float f,
            float g, float h, float i):
            elements{
                {a, b, c},
                {d, e, f},
                {g, h, i}
            } {}

        AVML_FINL Matrix(vector a, vector b, vector c):
            elements{
                {a[0], a[1], a[2]},
                {b[0], b[1], b[2]},
                {c[0], c[1], c[2]}
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
                -operator[](1),
                -operator[](2),
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

        float elements[3][3]{
            {0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f}
        };

    };

    const Matrix<float, 3, 3> Identity3f{1.0f};

    AVML_FINL bool operator==(const mat3x3f& lhs, const mat3x3f& rhs) {
        bool ret = true;
        for (unsigned i = 0; i < mat3x3f::height; ++i) {
            ret &= (lhs[i] == rhs[i]);
        }
        return ret;
    }

    AVML_FINL bool operator!=(const mat3x3f& lhs, const mat3x3f& rhs) {
        return !(lhs == rhs);
    }

    AVML_FINL mat3x3f operator+(mat3x3f lhs, mat3x3f rhs) {
        lhs += rhs;
        return lhs;
    }

    AVML_FINL mat3x3f operator-(mat3x3f lhs, mat3x3f rhs) {
        lhs -= rhs;
        return lhs;
    }

    AVML_FINL mat3x3f operator*(mat3x3f lhs, float rhs) {
        lhs *= rhs;
        return lhs;
    }

    AVML_FINL mat3x3f operator*(float lhs, mat3x3f rhs) {
        rhs *= lhs;
        return rhs;
    }

    AVML_FINL mat3x3f operator/(mat3x3f lhs, float rhs) {
        lhs /= rhs;
        return lhs;
    }

    AVML_FINL mat3x3f operator*(mat3x3f lhs, mat3x3f rhs) {
        lhs *= rhs;
        return lhs;
    }

    AVML_FINL vec3f operator*(mat3x3f lhs, vec3f rhs) {
        vec3f ret{};

        for (unsigned i = 0; i < mat3x3f::height; ++i) {
            for (unsigned j = 0; j < mat3x3f::width; ++j) {
                ret[i] += lhs[i][j] * rhs[j];
            }
        }

        return ret;
    }

    AVML_FINL mat3x3f transpose(const mat3x3f m) {
        mat3x3f ret;

        for (unsigned i = 0; i < mat3x3f::height; ++i) {
            for (unsigned j = 0; j < mat3x3f::width; ++j) {
                ret[j][i] = m[i][j];
            }
        }

        return ret;
    }

    AVML_FINL float determinant(const mat3x3f& m) {
        return
            m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) -
            m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
            m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
    }

    AVML_FINL mat3x3f inverse(const mat3x3f& m) {
        auto det = determinant(m);

        if (det < (1.0f / 32768.0f)) {
            return mat3x3f {
                NAN, NAN, NAN,
                NAN, NAN, NAN,
                NAN, NAN, NAN
            };
        }

        return mat3x3f {
             m[1][1] * m[2][2] - m[1][2] * m[2][1], -m[0][1] * m[2][2] + m[0][2] * m[2][1],  m[0][1] * m[1][2] - m[0][2] * m[1][1],
            -m[0][1] * m[2][2] - m[1][2] * m[2][0],  m[0][0] * m[2][2] - m[0][2] * m[2][0], -m[0][0] * m[1][2] - m[0][2] * m[1][0],
             m[1][0] * m[2][1] - m[1][1] * m[2][0], -m[0][0] * m[2][1] + m[0][1] * m[2][0],  m[0][0] * m[1][1] - m[0][1] * m[1][0]
        } / det;
    }

}

#endif
