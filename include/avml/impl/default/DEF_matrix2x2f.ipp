namespace avml {

    template<>
    class Matrix<float, 2, 2> {
    public:

        using scalar = float;
        using vector = Vector<float, 2>;

        static constexpr unsigned width = 2;
        static constexpr unsigned height = 2;

        //=================================================
        // -ctors
        //=================================================

        AVML_FINL explicit Matrix(float d) noexcept:
            elements {
            vector{d, 0.0f},
            vector{0.0f, d}
        } {}

        AVML_FINL Matrix(float a, float b, float c, float d):
            elements{
                vector{a, b},
                vector{c, d}
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

        vector elements[height] = {vector{}, vector{}};

    };

    const Matrix<float, 2, 2> Identity2f{1.0f};

    AVML_FINL bool operator==(const mat2x2f& lhs, const mat2x2f& rhs) {
        bool ret = true;
        for (int i = 0; i < mat2x2f::height; ++i) {
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

        for (int i = 0; i < mat2x2f::height; ++i) {
            for (int j = 0; j < mat2x2f::width; ++j) {
                ret[i] += lhs[i][j] * rhs[j];
            }
        }

        return ret;
    }

    AVML_FINL mat2x2f transpose(const mat2x2f m) {
        mat2x2f ret;

        for (int i = 0; i < mat2x2f::height; ++i) {
            for (int j = 0; j < mat2x2f::width; ++j) {
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
