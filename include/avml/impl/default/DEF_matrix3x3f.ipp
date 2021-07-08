namespace avml {

    template<>
    class Matrix<float, 3, 3> {
    public:

        using scalar = float;
        using vector = Vector<float, 3>;

        static constexpr unsigned width = 3;
        static constexpr unsigned height = 3;

        //=================================================
        // -ctors
        //=================================================

        AVML_FINL Matrix(float d):
            elements {
            vector{d, 0.0f, 0.0f},
            vector{0.0f, d, 0.0f},
            vector{0.0f, 0.0f, d}
        } {}

        AVML_FINL Matrix(
            float a, float b, float c,
            float d, float e, float f,
            float g, float h, float i):
            elements{
                vector{a, b, c},
                vector{d, e, f},
                vector{g, h, i}
            } {}

        AVML_FINL Matrix(vector a, vector b):
            elements{a, b} {}

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
        // Arithmetic assignment operators
        //=================================================

        AVML_FINL Matrix& operator*=(scalar rhs) {
            for (int i = 0; i < height; ++i) {
                elements[i] *= rhs;
            }
            return *this;
        }

        AVML_FINL Matrix& operator/=(scalar rhs) {
            for (int i = 0; i < height; ++i) {
                elements[i] /= rhs;
            }
            return *this;
        }

        AVML_FINL Matrix& operator+=(const Matrix& rhs) {
            for (int i = 0; i < height; ++i) {
                elements[i] += rhs.elements[i];
            }
            return *this;
        }

        AVML_FINL Matrix& operator-=(const Matrix& rhs) {
            for (int i = 0; i < height; ++i) {
                elements[i] -= rhs.elements[i];
            }
            return *this;
        }

        AVML_FINL Matrix& operator*=(const Matrix& rhs) {
            auto ret = *this;
            for (int i = 0; i < height; ++i) {
                for (int j = 0; j < width; ++j) {
                    float tmp = 0.0f;
                    for (int k = 0; j < width; ++k) {
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
            return elements[i];
        }

        AVML_FINL const vector& operator[](unsigned i) const {
            return elements[i];
        }

        float* data() {
            return elements[0].data();
        }

        const float* data() const {
            return elements[0].data();
        }

    private:

        vector elements[height] = {vector{}, vector{}, vector{}};

    };

    const Matrix<float, 3, 3> Identity3f{1.0f};

    AVML_FINL bool operator==(const mat3x3f& lhs, const mat3x3f& rhs) {
        bool ret = true;
        for (int i = 0; i < mat3x3f::height; ++i) {
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

        for (int i = 0; i < mat3x3f::height; ++i) {
            for (int j = 0; j < mat3x3f::width; ++j) {
                ret[i] += lhs[i][j] * rhs[j];
            }
        }

        return ret;
    }

    AVML_FINL mat3x3f transpose(const mat3x3f m) {
        mat3x3f ret;

        for (int i = 0; i < mat3x3f::height; ++i) {
            for (int j = 0; j < mat3x3f::width; ++j) {
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
