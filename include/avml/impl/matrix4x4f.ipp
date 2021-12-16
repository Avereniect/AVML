namespace avml {

    template<>
    class alignas(alignof(float) * 4 * 4) Matrix4x4R<float> {
    public:

        using scalar = float;
        using vector = Vector4R<float>;

        static constexpr unsigned width = 4;
        static constexpr unsigned height = 4;

        //=================================================
        // Creation methods
        //=================================================

        AVML_FINL static Matrix4x4R read(const float* ptr) {
            Matrix4x4R ret;
            ret[0] = vector::read(ptr + 0x0);
            ret[1] = vector::read(ptr + 0x4);
            ret[2] = vector::read(ptr + 0x8);
            ret[3] = vector::read(ptr + 0xC);
            return ret;
        }

        AVML_FINL static Matrix4x4R read_aligned(const float* ptr) {
            Matrix4x4R ret;
            ret[0] = vector::read_aligned(ptr + 0x0);
            ret[1] = vector::read_aligned(ptr + 0x4);
            ret[2] = vector::read_aligned(ptr + 0x8);
            ret[3] = vector::read_aligned(ptr + 0xC);
            return ret;
        }

        //=================================================
        // -ctors
        //=================================================

        AVML_FINL explicit Matrix4x4R(float d):
            elements {
                {d, 0.0f, 0.0f, 0.0f},
                {0.0f, d, 0.0f, 0.0f},
                {0.0f, 0.0f, d, 0.0f},
                {0.0f, 0.0f, 0.0f, d}
        } {}

        AVML_FINL Matrix4x4R(
            float a, float b, float c, float d,
            float e, float f, float g, float h,
            float i, float j, float k, float l,
            float m, float n, float o, float p):
            elements{
                {a, b, c, d},
                {e, f, g, h},
                {i, j, k, l},
                {m, n, o, p}
            } {}

        AVML_FINL Matrix4x4R(vector a, vector b, vector c, vector d):
            elements{
                {a[0], a[1], a[2], a[3]},
                {b[0], b[1], b[2], b[3]},
                {c[0], c[1], c[2], c[3]},
                {d[0], d[1], d[2], d[3]}
        } {}

        Matrix4x4R() = default;
        Matrix4x4R(const Matrix4x4R&) = default;
        Matrix4x4R(Matrix4x4R&&) = default;
        ~Matrix4x4R() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Matrix4x4R& operator=(const Matrix4x4R&) = default;
        Matrix4x4R& operator=(Matrix4x4R&&) = default;

        //=================================================
        // Unary arithmetic operators
        //=================================================

        AVML_FINL Matrix4x4R operator+() const {
            return *this;
        }

        AVML_FINL Matrix4x4R operator-() const {
            return Matrix4x4R{
                -operator[](0),
                -operator[](1),
                -operator[](2),
                -operator[](3)
            };
        }

        //=================================================
        // Arithmetic assignment operators
        //=================================================

        AVML_FINL Matrix4x4R& operator*=(scalar rhs) {
            for (unsigned i = 0; i < height; ++i) {
                operator[](i) *= rhs;
            }
            return *this;
        }

        AVML_FINL Matrix4x4R& operator/=(scalar rhs) {
            for (unsigned i = 0; i < height; ++i) {
                operator[](i) /= rhs;
            }
            return *this;
        }

        AVML_FINL Matrix4x4R& operator+=(const Matrix4x4R& rhs) {
            for (unsigned i = 0; i < height; ++i) {
                operator[](i) += rhs.operator[](i);
            }
            return *this;
        }

        AVML_FINL Matrix4x4R& operator-=(const Matrix4x4R& rhs) {
            for (unsigned i = 0; i < height; ++i) {
                operator[](i) -= rhs.operator[](i);
            }
            return *this;
        }

        AVML_FINL Matrix4x4R& operator*=(const Matrix4x4R& rhs) {
            Matrix4x4R result{};
            for (unsigned i = 0; i < height; ++i) {
                for (unsigned j = 0; j < width; ++j) {
                    float tmp = 0.0f;
                    for (unsigned k = 0; k < width; ++k) {
                        tmp += elements[i][k] * rhs.elements[k][j];
                    }
                    result[i][j] = tmp;
                }
            }

            *this = result;

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

        float elements[4][4]{
            {0.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 0.0f}
        };

    };

    AVML_FINL bool operator==(const Matrix4x4R<float>& lhs, const Matrix4x4R<float>& rhs) {
        bool ret = true;
        for (unsigned i = 0; i < Matrix4x4R<float>::height; ++i) {
            ret &= (lhs[i] == rhs[i]);
        }
        return ret;
    }

    AVML_FINL bool operator!=(const Matrix4x4R<float>& lhs, const Matrix4x4R<float>& rhs) {
        return !(lhs == rhs);
    }

    AVML_FINL Matrix4x4R<float> operator+(Matrix4x4R<float> lhs, Matrix4x4R<float> rhs) {
        lhs += rhs;
        return lhs;
    }

    AVML_FINL Matrix4x4R<float> operator-(Matrix4x4R<float> lhs, Matrix4x4R<float> rhs) {
        lhs -= rhs;
        return lhs;
    }

    AVML_FINL Matrix4x4R<float> operator*(Matrix4x4R<float> lhs, float rhs) {
        lhs *= rhs;
        return lhs;
    }

    AVML_FINL Matrix4x4R<float> operator*(float lhs, Matrix4x4R<float> rhs) {
        rhs *= lhs;
        return rhs;
    }

    AVML_FINL Matrix4x4R<float> operator/(Matrix4x4R<float> lhs, float rhs) {
        lhs /= rhs;
        return lhs;
    }

    AVML_FINL Matrix4x4R<float> operator*(Matrix4x4R<float> lhs, Matrix4x4R<float> rhs) {
        lhs *= rhs;
        return lhs;
    }

    AVML_FINL vec4f operator*(Matrix4x4R<float> lhs, vec4f rhs) {
        vec4f ret{};

        for (unsigned i = 0; i < Matrix4x4R<float>::height; ++i) {
            for (unsigned j = 0; j < Matrix4x4R<float>::width; ++j) {
                ret[i] += lhs[i][j] * rhs[j];
            }
        }

        return ret;
    }

    AVML_FINL Matrix4x4R<float> transpose(const Matrix4x4R<float> m) {
        Matrix4x4R<float> ret;

        for (unsigned i = 0; i < Matrix4x4R<float>::height; ++i) {
            for (unsigned j = 0; j < Matrix4x4R<float>::width; ++j) {
                ret[j][i] = m[i][j];
            }
        }

        return ret;
    }

    AVML_FINL float determinant(const Matrix4x4R<float>& m) {
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

    AVML_FINL Matrix4x4R<float> inverse(const Matrix4x4R<float>& mat) {
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
            return Matrix4x4R<float> {
                NAN, NAN, NAN, NAN,
                NAN, NAN, NAN, NAN,
                NAN, NAN, NAN, NAN,
                NAN, NAN, NAN, NAN
            };
        }

        return Matrix4x4R<float> {
            t00, t01, t02, t03,
            t10, t11, t12, t13,
            t20, t21, t22, t23,
            t30, t31, t32, t33
        } / det;
    }

    template<unsigned I = 0, unsigned J = 0>
    AVML_FINL Matrix2x2R<float> extract2x2(const Matrix4x4R<float> m) {
        static_assert(I < 3, "");
        static_assert(J < 3, "");

        Matrix2x2R<float> ret;

        for (unsigned i = 0; i < Matrix2x2R<float>::height; ++i) {
            for (unsigned j = 0; j < Matrix2x2R<float>::width; ++j) {
                ret[i][j] = m[i + I][j + J];
            }
        }

        return ret;
    }

    template<unsigned I = 0, unsigned J = 0>
    AVML_FINL Matrix3x3R<float> extract3x3(const Matrix4x4R<float> m) {
        static_assert(I < 3, "");
        static_assert(J < 3, "");

        Matrix3x3R<float> ret;

        for (unsigned i = 0; i < Matrix3x3R<float>::height; ++i) {
            for (unsigned j = 0; j < Matrix3x3R<float>::width; ++j) {
                ret[i][j] = m[i + I][j + J];
            }
        }

        return ret;
    }

}
