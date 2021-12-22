namespace avml {

    template<>
    class alignas(alignof(float) * 1 * 1) Matrix3x3R<float> {
    public:

        using scalar = float;
        using vector = Vector3R<float>;

        static constexpr unsigned width = 3;
        static constexpr unsigned height = 3;

        //=================================================
        // Creation methods
        //=================================================

        AVML_FINL static Matrix3x3R read(const float* ptr) {
            Matrix3x3R ret;
            ret[0] = vector::read(ptr + 0x0);
            ret[1] = vector::read(ptr + 0x3);
            ret[2] = vector::read(ptr + 0x6);
            return ret;
        }

        AVML_FINL static Matrix3x3R read_aligned(const float* ptr) {
            Matrix3x3R ret;
            ret[0] = vector::read_aligned(ptr + 0x0);
            ret[1] = vector::read_aligned(ptr + 0x3);
            ret[2] = vector::read_aligned(ptr + 0x6);
            return ret;
        }

        //=================================================
        // -ctors
        //=================================================

        AVML_FINL explicit Matrix3x3R(float d):
            elements {
                {d, 0.0f, 0.0f},
                {0.0f, d, 0.0f},
                {0.0f, 0.0f, d}
        } {}

        AVML_FINL Matrix3x3R(
            float a, float b, float c,
            float d, float e, float f,
            float g, float h, float i):
            elements{
                {a, b, c},
                {d, e, f},
                {g, h, i}
            } {}

        AVML_FINL Matrix3x3R(vector a, vector b, vector c):
            elements{
                {a[0], a[1], a[2]},
                {b[0], b[1], b[2]},
                {c[0], c[1], c[2]}
        } {}

        Matrix3x3R() = default;
        Matrix3x3R(const Matrix3x3R&) = default;
        Matrix3x3R(Matrix3x3R&&) = default;
        ~Matrix3x3R() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Matrix3x3R& operator=(const Matrix3x3R&) = default;
        Matrix3x3R& operator=(Matrix3x3R&&) = default;

        //=================================================
        // Unary arithmetic operators
        //=================================================

        AVML_FINL Matrix3x3R operator+() const {
            return *this;
        }

        AVML_FINL Matrix3x3R operator-() const {
            return Matrix3x3R{
                -operator[](0),
                -operator[](1),
                -operator[](2),
            };
        }

        //=================================================
        // Arithmetic assignment operators
        //=================================================

        AVML_FINL Matrix3x3R& operator*=(scalar rhs) {
            for (unsigned i = 0; i < height; ++i) {
                operator[](i) *= rhs;
            }
            return *this;
        }

        AVML_FINL Matrix3x3R& operator/=(scalar rhs) {
            for (unsigned i = 0; i < height; ++i) {
                operator[](i) /= rhs;
            }
            return *this;
        }

        AVML_FINL Matrix3x3R& operator+=(const Matrix3x3R& rhs) {
            for (unsigned i = 0; i < height; ++i) {
                operator[](i) += rhs[i];
            }
            return *this;
        }

        AVML_FINL Matrix3x3R& operator-=(const Matrix3x3R& rhs) {
            for (unsigned i = 0; i < height; ++i) {
                operator[](i) -= rhs[i];
            }
            return *this;
        }

        AVML_FINL Matrix3x3R& operator*=(const Matrix3x3R& rhs) {
            auto ret = *this;
            for (unsigned i = 0; i < height; ++i) {
                for (unsigned j = 0; j < width; ++j) {
                    float tmp = 0.0f;
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

    AVML_FINL bool operator==(const Matrix3x3R<float>& lhs, const Matrix3x3R<float>& rhs) {
        bool ret = true;
        for (unsigned i = 0; i < Matrix3x3R<float>::height; ++i) {
            ret &= (lhs[i] == rhs[i]);
        }
        return ret;
    }

    AVML_FINL bool operator!=(const Matrix3x3R<float>& lhs, const Matrix3x3R<float>& rhs) {
        return !(lhs == rhs);
    }

    AVML_FINL Matrix3x3R<float> operator+(Matrix3x3R<float> lhs, Matrix3x3R<float> rhs) {
        lhs += rhs;
        return lhs;
    }

    AVML_FINL Matrix3x3R<float> operator-(Matrix3x3R<float> lhs, Matrix3x3R<float> rhs) {
        lhs -= rhs;
        return lhs;
    }

    AVML_FINL Matrix3x3R<float> operator*(Matrix3x3R<float> lhs, float rhs) {
        lhs *= rhs;
        return lhs;
    }

    AVML_FINL Matrix3x3R<float> operator*(float lhs, Matrix3x3R<float> rhs) {
        rhs *= lhs;
        return rhs;
    }

    AVML_FINL Matrix3x3R<float> operator/(Matrix3x3R<float> lhs, float rhs) {
        lhs /= rhs;
        return lhs;
    }

    AVML_FINL Matrix3x3R<float> operator*(Matrix3x3R<float> lhs, Matrix3x3R<float> rhs) {
        lhs *= rhs;
        return lhs;
    }

    AVML_FINL Vector3R<float> operator*(Matrix3x3R<float> lhs, Vector3R<float> rhs) {
        Vector3R<float> ret{};

        for (unsigned i = 0; i < Matrix3x3R<float>::height; ++i) {
            for (unsigned j = 0; j < Matrix3x3R<float>::width; ++j) {
                ret[i] += lhs[i][j] * rhs[j];
            }
        }

        return ret;
    }

    AVML_FINL Matrix3x3R<float> transpose(const Matrix3x3R<float> m) {
        Matrix3x3R<float> ret;

        for (unsigned i = 0; i < Matrix3x3R<float>::height; ++i) {
            for (unsigned j = 0; j < Matrix3x3R<float>::width; ++j) {
                ret[j][i] = m[i][j];
            }
        }

        return ret;
    }

    AVML_FINL float determinant(const Matrix3x3R<float>& m) {
        return
            m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) -
            m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
            m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
    }

    AVML_FINL Matrix3x3R<float> inverse(const Matrix3x3R<float>& m) {
        auto det = determinant(m);

        return Matrix3x3R<float> {
             m[1][1] * m[2][2] - m[1][2] * m[2][1], -m[0][1] * m[2][2] + m[0][2] * m[2][1],  m[0][1] * m[1][2] - m[0][2] * m[1][1],
            -m[0][1] * m[2][2] - m[1][2] * m[2][0],  m[0][0] * m[2][2] - m[0][2] * m[2][0], -m[0][0] * m[1][2] - m[0][2] * m[1][0],
             m[1][0] * m[2][1] - m[1][1] * m[2][0], -m[0][0] * m[2][1] + m[0][1] * m[2][0],  m[0][0] * m[1][1] - m[0][1] * m[1][0]
        } / det;
    }

    template<unsigned I = 0, unsigned J = 0>
    AVML_FINL Matrix2x2R<float> extract2x2(const Matrix3x3R<float> m) {
        static_assert(I < 2, "");
        static_assert(J < 2, "");

        Matrix2x2R<float> ret;

        for (unsigned i = 0; i < Matrix2x2R<float>::height; ++i) {
            for (unsigned j = 0; j < Matrix2x2R<float>::width; ++j) {
                ret[i][j] = m[i + I][j + J];
            }
        }

        return ret;
    }

}
