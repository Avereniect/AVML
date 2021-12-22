namespace avml {

    template<class R>
    class alignas(alignof(R) * 4 * 4) Matrix4x4R {
    public:

        using scalar = R;
        using vector = Vector4R<R>;

        static constexpr unsigned width = 4;
        static constexpr unsigned height = 4;

        //=================================================
        // Creation methods
        //=================================================

        AVML_FINL static Matrix4x4R read(const R* ptr) {
            Matrix4x4R ret;
            ret[0] = vector::read(ptr + 0x0);
            ret[1] = vector::read(ptr + 0x4);
            ret[2] = vector::read(ptr + 0x8);
            ret[3] = vector::read(ptr + 0xC);
            return ret;
        }

        AVML_FINL static Matrix4x4R read_aligned(const R* ptr) {
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

        AVML_FINL explicit Matrix4x4R(R d):
            elements {
                {d, 0.0f, 0.0f, 0.0f},
                {0.0f, d, 0.0f, 0.0f},
                {0.0f, 0.0f, d, 0.0f},
                {0.0f, 0.0f, 0.0f, d}
        } {}

        AVML_FINL Matrix4x4R(
            R a, R b, R c, R d,
            R e, R f, R g, R h,
            R i, R j, R k, R l,
            R m, R n, R o, R p):
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
                    R tmp{};
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

        AVML_FINL R* data() {
            return elements[0];
        }

        AVML_FINL const R* data() const {
            return elements[0];
        }

    private:

        R elements[4][4];

    };

    template<class R>
    AVML_FINL bool operator==(const Matrix4x4R<R>& lhs, const Matrix4x4R<R>& rhs) {
        bool ret = true;
        for (unsigned i = 0; i < Matrix4x4R<R>::height; ++i) {
            ret &= (lhs[i] == rhs[i]);
        }
        return ret;
    }

    template<class R>
    AVML_FINL bool operator!=(const Matrix4x4R<R>& lhs, const Matrix4x4R<R>& rhs) {
        return !(lhs == rhs);
    }

    template<class R>
    AVML_FINL Matrix4x4R<R> operator+(Matrix4x4R<R> lhs, Matrix4x4R<R> rhs) {
        lhs += rhs;
        return lhs;
    }

    template<class R>
    AVML_FINL Matrix4x4R<R> operator-(Matrix4x4R<R> lhs, Matrix4x4R<R> rhs) {
        lhs -= rhs;
        return lhs;
    }

    template<class R>
    AVML_FINL Matrix4x4R<R> operator*(Matrix4x4R<R> lhs, R rhs) {
        lhs *= rhs;
        return lhs;
    }

    template<class R>
    AVML_FINL Matrix4x4R<R> operator*(R lhs, Matrix4x4R<R> rhs) {
        rhs *= lhs;
        return rhs;
    }

    template<class R>
    AVML_FINL Matrix4x4R<R> operator/(Matrix4x4R<R> lhs, R rhs) {
        lhs /= rhs;
        return lhs;
    }

    template<class R>
    AVML_FINL Matrix4x4R<R> operator*(Matrix4x4R<R> lhs, Matrix4x4R<R> rhs) {
        lhs *= rhs;
        return lhs;
    }

    template<class R>
    AVML_FINL vec4f operator*(Matrix4x4R<R> lhs, vec4f rhs) {
        vec4f ret{};

        for (unsigned i = 0; i < Matrix4x4R<R>::height; ++i) {
            for (unsigned j = 0; j < Matrix4x4R<R>::width; ++j) {
                ret[i] += lhs[i][j] * rhs[j];
            }
        }

        return ret;
    }

    template<class R>
    AVML_FINL Matrix4x4R<R> transpose(const Matrix4x4R<R> m) {
        Matrix4x4R<R> ret;

        for (unsigned i = 0; i < Matrix4x4R<R>::height; ++i) {
            for (unsigned j = 0; j < Matrix4x4R<R>::width; ++j) {
                ret[j][i] = m[i][j];
            }
        }

        return ret;
    }

    template<class R>
    AVML_FINL R determinant(const Matrix4x4R<R>& m) {
        R x = m[0][0] * (
            m[1][1] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) -
            m[1][2] * (m[2][1] * m[3][3] - m[2][3] * m[3][1]) +
            m[1][3] * (m[2][1] * m[3][2] - m[2][2] * m[3][1])
        );

        R y = m[1][0] * (
            m[1][0] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) -
            m[1][2] * (m[2][0] * m[3][3] - m[2][3] * m[3][0]) +
            m[1][3] * (m[2][0] * m[3][2] - m[2][2] * m[3][0])
        );

        R z = m[2][0] * (
            m[1][0] * (m[2][1] * m[3][3] - m[2][3] * m[3][1]) -
            m[1][1] * (m[2][0] * m[3][3] - m[2][3] * m[3][0]) +
            m[1][3] * (m[2][0] * m[3][1] - m[2][1] * m[3][0])
        );

        R w = m[3][0] * (
            m[1][0] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]) -
            m[1][1] * (m[2][0] * m[3][2] - m[2][2] * m[3][0]) +
            m[1][2] * (m[2][0] * m[3][1] - m[2][1] * m[3][0])
        );

        return x - y + z - w;
    }

    template<class R>
    AVML_FINL Matrix4x4R<R> inverse(const Matrix4x4R<R>& mat) {
        auto det = determinant(mat);

        R a = mat[0][0];
        R b = mat[0][1];
        R c = mat[0][2];
        R d = mat[0][3];

        R e = mat[1][0];
        R f = mat[1][1];
        R g = mat[1][2];
        R h = mat[1][3];

        R i = mat[2][0];
        R j = mat[2][1];
        R k = mat[2][2];
        R l = mat[2][3];

        R m = mat[3][0];
        R n = mat[3][1];
        R o = mat[3][2];
        R p = mat[3][3];

        R in = i * n;
        R io = i * o;
        R ip = i * p;

        R jm = j * p;
        R jo = j * o;
        R jp = j * p;

        R km = k * m;
        R kn = k * n;
        R kp = k * p;

        R lm = l * m;
        R ln = l * n;
        R lo = l * o;

        R ej = e * j;
        R ek = e * k;
        R el = e * l;
        R en = e * n;
        R eo = e * o;
        R ep = e * p;

        R fi = f * i;
        R fk = f * k;
        R fl = f * l;
        R fm = f * m;
        R fo = f * o;
        R fp = f * p;

        R gi = g * i;
        R gj = g * j;
        R gl = g * l;
        R gm = g * m;
        R gn = g * n;
        R gp = g * p;

        R hi = h * i;
        R hj = h * j;
        R hk = h * k;
        R hm = h * m;
        R hn = h * n;
        R ho = h * o;

        R kp_lo = kp - lo;

        R io_km = io - km;

        R gp_ho = gp - ho;
        R gl_hk = gl - hk;

        R jp_ln = jp - ln;
        R jo_kn = jo - kn;
        R ip_lm = ip - lm;
        R in_jm = in - jm;

        R fp_hn = fp - hn;
        R fo_gn = fo - gn;
        R fl_hj = fl - hj;
        R fk_gj = fk - gj;

        R ep_hm = ep - hm;
        R eo_gm = eo - gm;
        R el_hi = el - hi;
        R ek_gi = ek - gi;
        R en_fm = en - fm;
        R ej_fi = ej - fi;

        R t00 =  f * kp_lo - g * jp_ln + h * jo_kn;
        R t01 = -b * kp_lo + c * jp_ln - d * jo_kn;
        R t02 =  b * gp_ho - c * fp_hn + d * fo_gn;
        R t03 = -b * gl_hk + c * fl_hj - d * fk_gj;

        R t10 = -e * kp_lo + g * jp_ln - h * io_km;
        R t11 =  a * kp_lo - c * ip_lm + d * io_km;
        R t12 = -a * gp_ho + c * ep_hm - d * eo_gm;
        R t13 =  a * gl_hk - c * el_hi + d * ek_gi;

        R t20 =  e * jp_ln - f * ip_lm + h * in_jm;
        R t21 = -a * jp_ln + b * ip_lm - d * in_jm;
        R t22 =  a * fp_hn - b * ep_hm + d * en_fm;
        R t23 = -a * fl_hj + b * el_hi - d * ej_fi;

        R t30 = -e * jo_kn + f * io_km - g * in_jm;
        R t31 =  a * jo_kn - b * io_km + c * in_jm;
        R t32 = -a * fo_gn + b * eo_gm - c * en_fm;
        R t33 =  a * fk_gj - b * ek_gi + c * ej_fi;

        return Matrix4x4R<R> {
            t00, t01, t02, t03,
            t10, t11, t12, t13,
            t20, t21, t22, t23,
            t30, t31, t32, t33
        } / det;
    }

    template<unsigned I = 0, unsigned J = 0, class R>
    AVML_FINL Matrix2x2R<R> extract2x2(const Matrix4x4R<R> m) {
        static_assert(I < 3, "");
        static_assert(J < 3, "");

        Matrix2x2R<R> ret;

        for (unsigned i = 0; i < Matrix2x2R<R>::height; ++i) {
            for (unsigned j = 0; j < Matrix2x2R<R>::width; ++j) {
                ret[i][j] = m[i + I][j + J];
            }
        }

        return ret;
    }

    template<unsigned I = 0, unsigned J = 0, class R>
    AVML_FINL Matrix3x3R<R> extract3x3(const Matrix4x4R<R> m) {
        static_assert(I < 3, "");
        static_assert(J < 3, "");

        Matrix3x3R<R> ret;

        for (unsigned i = 0; i < Matrix3x3R<R>::height; ++i) {
            for (unsigned j = 0; j < Matrix3x3R<R>::width; ++j) {
                ret[i][j] = m[i + I][j + J];
            }
        }

        return ret;
    }

}
