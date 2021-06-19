#ifndef AVML_DEF_MATRIX_HPP
#define AVML_DEF_MATRIX_HPP

namespace avml {

    //=========================================================================
    // Matrix functions
    //=========================================================================

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

        AVML_FINL Matrix(float d):
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
            vector v{rhs, rhs};
            for (int i = 0; i < height; ++i) {
                elements[i] += v;
            }
            return *this;
        }

        AVML_FINL Matrix& operator+=(const Matrix& rhs) {
            for (int i = 0; i < height; ++i) {
                elements[i] += rhs.elements[i];
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

    private:

        vector elements[height] = {vector{}, vector{}};

    };

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
            vector v{rhs, rhs, rhs};
            for (int i = 0; i < height; ++i) {
                elements[i] += v;
            }
            return *this;
        }

        AVML_FINL Matrix& operator+=(const Matrix& rhs) {
            for (int i = 0; i < height; ++i) {
                elements[i] += rhs.elements[i];
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

    private:

        vector elements[height] = {vector{}, vector{}};

    };

    template<>
    class Matrix<float, 4, 4> {
    public:

        using scalar = float;
        using vector = Vector<float, 4>;

        static constexpr unsigned width = 4;
        static constexpr unsigned height = 4;

        //=================================================
        // -ctors
        //=================================================

        AVML_FINL Matrix(float d):
            elements {
            vector{d, 0.0f, 0.0f, 0.0f},
            vector{0.0f, d, 0.0f, 0.0f},
            vector{0.0f, 0.0f, d, 0.0f},
            vector{0.0f, 0.0f, 0.0f, d}
        } {}

        AVML_FINL Matrix(
            float a, float b, float c, float d,
            float e, float f, float g, float h,
            float i, float j, float k, float l,
            float m, float n, float o, float p):
            elements{
                vector{a, b, c, d},
                vector{e, f, g, h},
                vector{i, j, k, l},
                vector{m, n, o, p}
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
            vector v{rhs, rhs, rhs, rhs};
            for (int i = 0; i < height; ++i) {
                elements[i] += v;
            }
            return *this;
        }

        AVML_FINL Matrix& operator+=(const Matrix& rhs) {
            for (int i = 0; i < height; ++i) {
                elements[i] += rhs.elements[i];
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

    private:

        vector elements[height] = {vector{}, vector{}};

    };

    //=========================================================================
    // Matrix comparison operators
    //=========================================================================

    template<class T, unsigned N, unsigned M>
    AVML_FINL bool operator==(const Matrix<T, N, M>& lhs, const Matrix<T, N, M>& rhs) {
        bool ret = true;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                ret &= (lhs[i][j] == rhs[i][j]);
            }
        }

        return ret;
    }

    template<class T, unsigned N, unsigned M>
    AVML_FINL bool operator!=(const Matrix<T, N, M>& lhs, const Matrix<T, N, M>& rhs) {
        bool ret = true;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                ret &= (lhs[i][j] != rhs[i][j]);
            }
        }

        return ret;
    }

    //=========================================================================
    // Matrix arithmetic operators
    //=========================================================================

    template<class T, unsigned N, unsigned M>
    AVML_FINL Matrix<T, N, M> operator*(Matrix<T, N, M> lhs, T rhs) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                lhs[i][j] *= rhs;
            }
        }

        return lhs;
    }

    template<class T, unsigned N, unsigned M>
    AVML_FINL Matrix<T, N, M> operator*(T lhs, Matrix<T, N, M> rhs) {
        return rhs * lhs;
    }

    template<class T, unsigned N, unsigned M>
    AVML_FINL Vector<T, N> operator*(Matrix<T, N, M> lhs, Vector<T, M> rhs) {
        Vector<T, N> ret{};

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                ret[i] += lhs[i][j] * rhs[j];
            }
        }

        return ret;
    }

    template<class T, unsigned N, unsigned M>
    AVML_FINL Matrix<T, N, M> operator/(Matrix<T, N, M> lhs, T rhs) {
        for (int i = 0; i <N ; ++i) {
            for (int j = 0; j < M; ++j) {
                lhs[i][j] /= rhs;
            }
        }

        return lhs;
    }

    //=========================================================================
    // Matrix functions
    //=========================================================================

    template<class T, unsigned N, unsigned M>
    AVML_FINL Matrix<T, M, N> transpose(const Matrix<T, N, M> m) {
        Matrix<T, M, N> ret;

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                ret[j][i] = m[i][j];
            }
        }

        return ret;
    }

    template<class T>
    AVML_FINL T determinant(const Matrix<T, 2, 2>& m) {
        return m[0][0] * m[1][1] - m[0][1] * m[1][0];
    }

    template<class T>
    AVML_FINL T determinant(const Matrix<T, 3, 3>& m) {
        return
            m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) -
            m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
            m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
    }

    template<class T>
    AVML_FINL T determinant(const Matrix<T, 4, 4>& m) {
        float x = m[0][0] * (
            m[1][1] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) -
            m[1][2] * (m[2][1] * m[3][3] - m[2][3] * m[3][1]) +
            m[1][3] * (m[2][1] * m[3][2] - m[2][2] * m[3][1])
        );

        float y = m[1][0] * (
            m[1][0] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) -
            m[1][2] * (m[2][0] * m[3][3] - m[2][3] * m[3][0]) +
            m[1][3] * (m[2][0] * m[3][2] - m[2][2] * m[3][0])
        );

        float z = m[2][0] * (
            m[1][0] * (m[2][1] * m[3][3] - m[2][3] * m[3][1]) -
            m[1][1] * (m[2][0] * m[3][3] - m[2][3] * m[3][0]) +
            m[1][3] * (m[2][0] * m[3][1] - m[2][1] * m[3][0])
        );

        float w = m[3][0] * (
            m[1][0] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]) -
            m[1][1] * (m[2][0] * m[3][2] - m[2][2] * m[3][0]) +
            m[1][2] * (m[2][0] * m[3][1] - m[2][1] * m[3][0])
        );

        return x - y + z - w;
    }

    template<class T>
    AVML_FINL Matrix<T, 2, 2> inverse(const Matrix<T, 2, 2>& m) {
        auto det = determinant(m);

        if (det < (1.0f / 65536.0f)) {
            return Matrix<T, 2, 2>{NAN, NAN, NAN, NAN};
        }

        return Matrix<T, 2, 2> {
             m[1][1],
            -m[1][0],
            -m[0][1],
             m[0][0]
        } / det;

    }

    template<class T>
    AVML_FINL Matrix<T, 3, 3> inverse(const Matrix<T, 3, 3>& m) {
        auto det = determinant(m);

        if (det < (1.0f / 32768.0f)) {
            return Matrix<T, 3, 3> {
                NAN, NAN, NAN,
                NAN, NAN, NAN,
                NAN, NAN, NAN
            };
        }

        return Matrix<T, 3, 3> {
             m[1][1] * m[2][2] - m[1][2] * m[2][1], -m[0][1] * m[2][2] + m[0][2] * m[2][1],  m[0][1] * m[1][2] - m[0][2] * m[1][1],
            -m[0][1] * m[2][2] - m[1][2] * m[2][0],  m[0][0] * m[2][2] - m[0][2] * m[2][0], -m[0][0] * m[1][2] - m[0][2] * m[1][0],
             m[1][0] * m[2][1] - m[1][1] * m[2][0], -m[0][0] * m[2][1] + m[0][1] * m[2][0],  m[0][0] * m[1][1] - m[0][1] * m[1][0]
        } / det;
    }

    template<class T>
    AVML_FINL Matrix<T, 4, 4> inverse(const Matrix<T, 4, 4>& mat) {
        auto det = determinant(mat);

        float a = mat[0][0];
        float b = mat[0][1];
        float c = mat[0][2];
        float d = mat[0][3];

        float e = mat[1][0];
        float f = mat[1][1];
        float g = mat[1][2];
        float h = mat[1][3];

        float i = mat[2][0];
        float j = mat[2][1];
        float k = mat[2][2];
        float l = mat[2][3];

        float m = mat[3][0];
        float n = mat[3][1];
        float o = mat[3][2];
        float p = mat[3][3];

        float in = i * n;
        float io = i * o;
        float ip = i * p;

        float jm = j * p;
        float jo = j * o;
        float jp = j * p;

        float km = k * m;
        float kn = k * n;
        float kp = k * p;

        float lm = l * m;
        float ln = l * n;
        float lo = l * o;

        float ej = e * j;
        float ek = e * k;
        float el = e * l;
        float en = e * n;
        float eo = e * o;
        float ep = e * p;

        float fi = f * i;
        float fk = f * k;
        float fl = f * l;
        float fm = f * m;
        float fo = f * o;
        float fp = f * p;

        float gi = g * i;
        float gj = g * j;
        float gl = g * l;
        float gm = g * m;
        float gn = g * n;
        float gp = g * p;

        float hi = h * i;
        float hj = h * j;
        float hk = h * k;
        float hm = h * m;
        float hn = h * n;
        float ho = h * o;

        float kp_lo = kp - lo;

        float io_km = io - km;

        float gp_ho = gp - ho;
        float gl_hk = gl - hk;

        float jp_ln = jp - ln;
        float jo_kn = jo - kn;
        float ip_lm = ip - lm;
        float in_jm = in - jm;

        float fp_hn = fp - hn;
        float fo_gn = fo - gn;
        float fl_hj = fl - hj;
        float fk_gj = fk - gj;

        float ep_hm = ep - hm;
        float eo_gm = eo - gm;
        float el_hi = el - hi;
        float ek_gi = ek - gi;
        float en_fm = en - fm;
        float ej_fi = ej - fi;

        float t00 =  f * kp_lo - g * jp_ln + h * jo_kn;
        float t01 = -b * kp_lo + c * jp_ln - d * jo_kn;
        float t02 =  b * gp_ho - c * fp_hn + d * fo_gn;
        float t03 = -b * gl_hk + c * fl_hj - d * fk_gj;

        float t10 = -e * kp_lo + g * jp_ln - h * io_km;
        float t11 =  a * kp_lo - c * ip_lm + d * io_km;
        float t12 = -a * gp_ho + c * ep_hm - d * eo_gm;
        float t13 =  a * gl_hk - c * el_hi + d * ek_gi;

        float t20 =  e * jp_ln - f * ip_lm + h * in_jm;
        float t21 = -a * jp_ln + b * ip_lm - d * in_jm;
        float t22 =  a * fp_hn - b * ep_hm + d * en_fm;
        float t23 = -a * fl_hj + b * el_hi - d * ej_fi;

        float t30 = -e * jo_kn + f * io_km - g * in_jm;
        float t31 =  a * jo_kn - b * io_km + c * in_jm;
        float t32 = -a * fo_gn + b * eo_gm - c * en_fm;
        float t33 =  a * fk_gj - b * ek_gi + c * ej_fi;

        if (det < (1.0 / 65536.0f)) {
            return Matrix<T, 4, 4> {
                NAN, NAN, NAN, NAN,
                NAN, NAN, NAN, NAN,
                NAN, NAN, NAN, NAN,
                NAN, NAN, NAN, NAN
            };
        }

        return Matrix<T, 4, 4> {
            t00, t01, t02, t03,
            t10, t11, t12, t13,
            t20, t21, t22, t23,
            t30, t31, t32, t33
        } / det;
    }

    template<class T, unsigned N>
    Matrix<T, N, N> pow(Matrix<T, N, N> mat, std::uint32_t power) {
        static const Matrix<T, N, N> identity{static_cast<T>(1)};
        Matrix<T, N, N> matrices[32] = {identity, mat};

        if (power == 0) {
            return identity;
        }

        std::uint32_t p = 1;
        while (p < power) {
            matrices[p] = matrices[p - 1] * matrices[p - 1];
            p = p << 1;
        }

        auto ret = mat;
        std::uint32_t mask = 0x2;
        unsigned i = 2;
        while (power) {
            if (power & mask) {
                ret *= matrices[i];
            }

            power &= ~mask;
            mask <<= 1;
            i += 1;
        }

        return mat;
    }

}

#endif //AVML_DEF_MATRIX_HPP
