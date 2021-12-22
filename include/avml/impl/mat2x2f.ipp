namespace avml {

    template<>
    class alignas(alignof(float) * 2 * 2) Matrix2x2R<float> {
    public:

        using scalar = float;
        using vector = Vector2R<float>;

        static constexpr unsigned width = 2;
        static constexpr unsigned height = 2;

        //=================================================
        // Creation methods
        //=================================================

        AVML_FINL static Matrix2x2R read(const float* ptr) {
            Matrix2x2R ret;
            ret[0] = vector::read(ptr + 0x0);
            ret[1] = vector::read(ptr + 0x2);
            return ret;
        }

        AVML_FINL static Matrix2x2R read_aligned(const float* ptr) {
            Matrix2x2R ret;
            ret[0] = vector::read_aligned(ptr + 0x0);
            ret[1] = vector::read_aligned(ptr + 0x2);
            return ret;
        }

        //=================================================
        // -ctors
        //=================================================

        AVML_FINL explicit Matrix2x2R(float d) noexcept:
            elements {
                {d, 0.0f},
                {0.0f, d}
        } {}

        AVML_FINL Matrix2x2R(float a, float b, float c, float d):
            elements{
                {a, b},
                {c, d}
            } {}

        AVML_FINL Matrix2x2R(vector a, vector b):
            elements{
                {a[0], a[1]},
                {b[0], b[1]}
        } {}

        Matrix2x2R() = default;
        Matrix2x2R(const Matrix2x2R&) = default;
        Matrix2x2R(Matrix2x2R&&) = default;
        ~Matrix2x2R() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Matrix2x2R& operator=(const Matrix2x2R&) = default;
        Matrix2x2R& operator=(Matrix2x2R&&) = default;

        //=================================================
        // Unary arithmetic operators
        //=================================================

        AVML_FINL Matrix2x2R operator+() const {
            return *this;
        }

        AVML_FINL Matrix2x2R operator-() const {
            return Matrix2x2R{
                -operator[](0),
                -operator[](1)
            };
        }

        //=================================================
        // Arithmetic assignment operators
        //=================================================

        AVML_FINL Matrix2x2R& operator*=(scalar rhs) {
            for (unsigned i = 0; i < height; ++i) {
                operator[](i) *= rhs;
            }
            return *this;
        }

        AVML_FINL Matrix2x2R& operator/=(scalar rhs) {
            for (unsigned i = 0; i < height; ++i) {
                 operator[](i) /= rhs;
            }
            return *this;
        }

        AVML_FINL Matrix2x2R& operator+=(const Matrix2x2R& rhs) {
            for (unsigned i = 0; i < height; ++i) {
                operator[](i) += rhs[i];
            }
            return *this;
        }

        AVML_FINL Matrix2x2R& operator-=(const Matrix2x2R& rhs) {
            for (unsigned i = 0; i < height; ++i) {
                 operator[](i) -= rhs[i];
            }
            return *this;
        }

        AVML_FINL Matrix2x2R& operator*=(const Matrix2x2R& rhs) {
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

        float elements[2][2] {
            {0.0f, 0.0f},
            {0.0f, 0.0f}
        };

    };

    AVML_FINL bool operator==(const Matrix2x2R<float>& lhs, const Matrix2x2R<float>& rhs) {
        bool ret = true;
        for (unsigned i = 0; i < Matrix2x2R<float>::height; ++i) {
            ret &= (lhs[i] == rhs[i]);
        }
        return ret;
    }

    AVML_FINL bool operator!=(const Matrix2x2R<float>& lhs, const Matrix2x2R<float>& rhs) {
        return !(lhs == rhs);
    }

    AVML_FINL Matrix2x2R<float> operator+(Matrix2x2R<float> lhs, Matrix2x2R<float> rhs) {
        lhs += rhs;
        return lhs;
    }

    AVML_FINL Matrix2x2R<float> operator-(Matrix2x2R<float> lhs, Matrix2x2R<float> rhs) {
        lhs -= rhs;
        return lhs;
    }

    AVML_FINL Matrix2x2R<float> operator*(Matrix2x2R<float> lhs, float rhs) {
        lhs *= rhs;
        return lhs;
    }

    AVML_FINL Matrix2x2R<float> operator*(float lhs, Matrix2x2R<float> rhs) {
        rhs *= lhs;
        return rhs;
    }

    AVML_FINL Matrix2x2R<float> operator/(Matrix2x2R<float> lhs, float rhs) {
        lhs /= rhs;
        return lhs;
    }

    AVML_FINL Matrix2x2R<float> operator*(Matrix2x2R<float> lhs, Matrix2x2R<float> rhs) {
        lhs *= rhs;
        return lhs;
    }

    AVML_FINL vec2f operator*(Matrix2x2R<float> lhs, vec2f rhs) {
        vec2f ret{};

        for (unsigned i = 0; i < Matrix2x2R<float>::height; ++i) {
            for (unsigned j = 0; j < Matrix2x2R<float>::width; ++j) {
                ret[i] += lhs[i][j] * rhs[j];
            }
        }

        return ret;
    }

    AVML_FINL Matrix2x2R<float> transpose(const Matrix2x2R<float> m) {
        Matrix2x2R<float> ret;

        for (unsigned i = 0; i < Matrix2x2R<float>::height; ++i) {
            for (unsigned j = 0; j < Matrix2x2R<float>::width; ++j) {
                ret[j][i] = m[i][j];
            }
        }

        return ret;
    }

    AVML_FINL float determinant(const Matrix2x2R<float>& m) {
        return m[0][0] * m[1][1] - m[0][1] * m[1][0];
    }

    AVML_FINL Matrix2x2R<float> inverse(const Matrix2x2R<float>& m) {
        auto det = determinant(m);

        return Matrix2x2R<float> {
             m[1][1],
            -m[1][0],
            -m[0][1],
             m[0][0]
        } / det;
    }

}

