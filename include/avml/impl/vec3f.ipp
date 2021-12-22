namespace avml_impl {

    struct vec3fw {

        vec3fw(__m128 t):
            reg(t) {}

        //=================================================
        // Instance members
        //=================================================

        __m128 reg;
    };



}

namespace avml {

    AVML_FINL avml_impl::vec3fw broadcast3f(float x) {
        return {_mm_load1_ps(&x)};
    }

    AVML_FINL avml_impl::vec3fw broadcast3f(float* x) {
        return {_mm_load1_ps(x)};
    }

    AVML_FINL avml_impl::vec3fw load3f(float* p) {
        return {_mm_load_ps(p)};
    }

    AVML_FINL avml_impl::vec3fw load3f(float x, float y, float z);



    AVML_FINL avml_impl::vec3fw operator+(const avml_impl::vec3fw& x, const avml_impl::vec3fw& y) {
        return {_mm_add_ps(x.reg, y.reg)};
    }

    AVML_FINL avml_impl::vec3fw operator-(const avml_impl::vec3fw& x, const avml_impl::vec3fw& y) {
        return {_mm_sub_ps(x.reg, y.reg)};
    }

    AVML_FINL avml_impl::vec3fw operator*(const avml_impl::vec3fw& x, const avml_impl::vec3fw& y) {
        return {_mm_mul_ps(x.reg, y.reg)};
    }

    AVML_FINL avml_impl::vec3fw operator*(const avml_impl::vec3fw& x, float y) {
        return {_mm_mul_ps(x.reg, _mm_load1_ps(&y))};
    }

}

namespace avml {

    template<>
    class alignas(alignof(float) * 1) Vector3R<float> {
    public:

        using scalar = float;

        static constexpr unsigned width = 3;

        //=================================================
        // Creation functions
        //=================================================

        AVML_FINL static Vector3R read(const float* p) {
            Vector3R ret;
            #if defined(AVML_SSE)
            avml_impl::store3f(ret.elements, avml_impl::load3f(p));
            #else
            ret.elements[0] = p[0];
            ret.elements[1] = p[1];
            ret.elements[2] = p[2];
            #endif
            return ret;
        }

        AVML_FINL static Vector3R read_aligned(const float* p) {
            return read(p);
        }

        //=================================================
        // -ctors
        //=================================================

        explicit AVML_FINL Vector3R(float v):
            elements{} {

            #if defined(AVML_AVX)
            __m128 t0 = _mm_set1_ps(v);
            __m128 t1 = _mm_permute_ps(t0, 0x00);
            avml_impl::store3f(elements, t1);

            #elif defined(AVML_SSE)
            __m128 t0 = _mm_set_ss(v);
            __m128 t1 = _mm_shuffle_ps(t0, t0, 0x00);
            avml_impl::store3f(elements, t1);

            #else
            elements[0] = v;
            elements[1] = v;
            elements[2] = v;

            #endif
        }

        AVML_FINL Vector3R(float x, float y, float z):
            elements{} {

            #if defined(AVML_SSE)
            __m128 t0 = _mm_set_ss(x);
            __m128 t1 = _mm_set_ss(y);
            __m128 t2 = _mm_set_ss(z);

            __m128 t3 = _mm_unpacklo_ps(t0, t1);
            __m128 t4 = _mm_movelh_ps(t3, t2);
            avml_impl::store3f(elements, t4);

            #else
            elements[0] = x;
            elements[1] = y;
            elements[2] = z;

            #endif
        }

        AVML_FINL Vector3R(const Unit_vector3R<float>& v):
            elements{v[0], v[1], v[2]} {}

        AVML_FINL Vector3R(const Unit_vector2R<float>& v, float z):
            elements{} {

        #if defined(AVML_SSE)
            __m128 t0 = avml_impl::load2f(v.data());
            __m128 t1 = _mm_set_ss(z);
            __m128 t2 = _mm_movelh_ps(t0, t1);
            avml_impl::store3f(elements, t2);
        #else
            elements[0] = v[0];
            elements[1] = v[1];
            elements[2] = z;
        #endif
        }

        AVML_FINL Vector3R(float w, const Unit_vector2R<float> v):
            elements{} {

        #if defined(AVML_SSE)
            __m128 t0 = _mm_set_ss(w);
            __m128 t1 = _mm_loadh_pi(t0, reinterpret_cast<const __m64*>(v.data()));
            __m128 t2 = _mm_shuffle_ps(t1, t1, 0x78);
            avml_impl::store3f(elements, t2);
        #else
            elements[0] = w;
            elements[1] = v[0];
            elements[2] = v[1];
        #endif
        }

        Vector3R() = default;
        Vector3R(const Vector3R&) = default;
        Vector3R(Vector3R&&) = default;
        ~Vector3R() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Vector3R& operator=(const Vector3R&) = default;
        Vector3R& operator=(Vector3R&&) = default;

        //=================================================
        // Unary arithmetic operators
        //=================================================

        AVML_FINL Vector3R operator+() const {
            return *this;
        }

        AVML_FINL Vector3R operator-() const {
        #if defined(AVML_SSE)
            Vector3R ret{};
            __m128 t0 = _mm_sub_ps(_mm_setzero_ps(), avml_impl::load3f(elements));
            avml_impl::store3f(ret.data(), t0);
            return ret;
        #else
            return Vector3R{
                -elements[0],
                -elements[1],
                -elements[2],
            };
        #endif
        }

        //=================================================
        // Arithmetic assignment operators
        //=================================================

        AVML_FINL Vector3R& operator+=(const Vector3R& rhs) {
        #if defined(AVML_SSE)
            __m128 a = avml_impl::load3f(elements);
            __m128 b = avml_impl::load3f(rhs.data());
            avml_impl::store3f(elements, _mm_add_ps(a, b));
        #else
            for (unsigned i = 0; i < width; ++i) {
                elements[i] += rhs[i];
            }
        #endif
            return *this;
        }

        AVML_FINL Vector3R& operator-=(const Vector3R& rhs) {
        #if defined(AVML_SSE)
            __m128 a = avml_impl::load3f(elements);
            __m128 b = avml_impl::load3f(rhs.data());
            avml_impl::store3f(elements, _mm_sub_ps(a, b));
        #else
            for (unsigned i = 0; i < width; ++i) {
                elements[i] -= rhs[i];
            }
        #endif
            return *this;
        }

        AVML_FINL Vector3R& operator*=(const Vector3R& rhs) {
        #if defined(AVML_SSE)
            __m128 a = avml_impl::load3f(elements);
            __m128 b = avml_impl::load3f(rhs.data());
            avml_impl::store3f(elements, _mm_mul_ps(a, b));
        #else
            for (unsigned i = 0; i < width; ++i) {
                elements[i] *= rhs[i];
            }
        #endif
            return *this;
        }

        AVML_FINL Vector3R& operator*=(const scalar rhs) {
            this->operator*=(Vector3R{rhs});
            return *this;
        }

        AVML_FINL Vector3R& operator/=(const Vector3R& rhs) {
        #if defined(AVML_SSE)
            __m128 a = avml_impl::load3f(elements);
            __m128 b = avml_impl::load3f(rhs.data());
            avml_impl::store3f(elements, _mm_div_ps(a, b));
        #else
            for (unsigned i = 0; i < width; ++i) {
                elements[i] /= rhs[i];
            }
        #endif
            return *this;
        }

        AVML_FINL Vector3R& operator/=(const scalar rhs) {
            this->operator/=(Vector3R{rhs});
            return *this;
        }

        //=================================================
        // Accessors
        //=================================================

        AVML_FINL float& operator[](unsigned i) {
            return elements[i];
        }

        AVML_FINL const float& operator[](unsigned i) const {
            return elements[i];
        }

        AVML_FINL float* data() {
            return elements;
        }

        AVML_FINL const float* data() const {
            return elements;
        }

    private:

        //=================================================
        // Instance members
        //=================================================

        float elements[width];

    };

    //=====================================================
    // Comparison operators
    //=====================================================

    AVML_FINL bool operator==(const Vector3R<float>& lhs, const Vector3R<float>& rhs) {
    #if defined(AVML_SSE)
        __m128 a = avml_impl::load3f(lhs.data());
        __m128 b = avml_impl::load3f(rhs.data());

        __m128 t0 = _mm_cmpeq_ps(a, b);
        int t1 = _mm_movemask_ps(t0);
        return (t1 == 0x0F);
    #else
        return
            (lhs[0] == rhs[0]) &&
            (lhs[1] == rhs[1]) &&
            (lhs[2] == rhs[2]);
    #endif
    }

    AVML_FINL bool operator!=(const Vector3R<float>& lhs, const Vector3R<float>& rhs) {
    #if defined(AVML_SSE)
        __m128 a = avml_impl::load3f(lhs.data());
        __m128 b = avml_impl::load3f(rhs.data());

        __m128 t0 = _mm_cmpeq_ps(a, b);
        int t1 = _mm_movemask_ps(t0);
        return (t1 == 0x0E);
    #else
        return
            (lhs[0] != rhs[0]) ||
            (lhs[1] != rhs[1]) ||
            (lhs[2] != rhs[2]);
    #endif
    }

    //=====================================================
    // Arithmetic operators
    //=====================================================

    AVML_FINL Vector3R<float> operator+(const Vector3R<float>& lhs, const Vector3R<float> rhs) {
    #if defined(AVML_SSE)
        Vector3R<float> ret;
        __m128 a = avml_impl::load3f(lhs.data());
        __m128 b = avml_impl::load3f(rhs.data());
        __m128 t = _mm_add_ps(a, b);
        avml_impl::store3f(ret.data(), t);
        return ret;
    #else
        Vector3R<float> ret = lhs;
        ret += rhs;
        return ret;
    #endif
    }

    AVML_FINL Vector3R<float> operator-(const Vector3R<float>& lhs, const Vector3R<float>& rhs) {
    #if defined(AVML_SSE)
        Vector3R<float> ret;
        __m128 a = avml_impl::load3f(lhs.data());
        __m128 b = avml_impl::load3f(rhs.data());
        __m128 t = _mm_sub_ps(a, b);
        avml_impl::store3f(ret.data(), t);
        return ret;
    #else
        Vector3R<float> ret = lhs;
        ret -= rhs;
        return ret;
    #endif
    }

    AVML_FINL Vector3R<float> operator*(const Vector3R<float>& lhs, const Vector3R<float>& rhs) {
    #if defined(AVML_SSE)
        Vector3R<float> ret;
        __m128 a = avml_impl::load3f(lhs.data());
        __m128 b = avml_impl::load3f(rhs.data());
        __m128 t = _mm_mul_ps(a, b);
        avml_impl::store3f(ret.data(), t);
        return ret;
    #else
        Vector3R<float> ret = lhs;
        ret *= rhs;
        return lhs;
    #endif
    }

    AVML_FINL Vector3R<float> operator*(Vector3R<float> lhs, float rhs) {
        #if defined(AVML_AVX)

        #elif defined(AVML_SSE)

        #endif
        return lhs * Vector3R<float>(rhs);
    }

    AVML_FINL Vector3R<float> operator*(float lhs, Vector3R<float> rhs) {
        rhs *= lhs;
        return rhs;
    }

    AVML_FINL Vector3R<float> operator/(Vector3R<float> lhs, float rhs) {
        lhs /= rhs;
        return lhs;
    }

    AVML_FINL Vector3R<float> operator/(Vector3R<float> lhs, Vector3R<float> rhs) {
        lhs /= rhs;
        return lhs;
    }

    //=====================================================
    // Vector math
    //=====================================================

    AVML_FINL float dot(Vector3R<float> lhs, Vector3R<float> rhs) {
        #if defined(AVML_AVX)
        __m128 a = avml_impl::load3f(lhs.data());
        __m128 b = avml_impl::load3f(rhs.data());

        __m128 t0 = _mm_mul_ps(a, b);
        __m128 t1 = _mm_movehl_ps(t0, t0);
        __m128 t2 = _mm_add_ps(t0, t1);
        __m128 t3 = _mm_permute_ps(t2, 0xFD);
        __m128 t4 = _mm_add_ss(t3, t2);
        return _mm_cvtss_f32(t4);

        #elif defined(AVML_SSE)
        __m128 a = avml_impl::load3f(lhs.data());
        __m128 b = avml_impl::load3f(rhs.data());

        __m128 t0 = _mm_mul_ps(a, b);
        __m128 t1 = _mm_movehl_ps(t0, t0);
        __m128 t2 = _mm_add_ps(t0, t1);
        __m128 t3 = _mm_shuffle_ps(t2, t2, 0xFD);
        __m128 t4 = _mm_add_ss(t3, t2);
        return _mm_cvtss_f32(t4);

        #else
        return
            lhs[0] * rhs[0] +
            lhs[1] * rhs[1] +
            lhs[2] * rhs[2];

        #endif
    }

    AVML_FINL float length2(Unit_vector3R<float>) = delete;

    AVML_FINL float length2(Vector3R<float> v) {
        return dot(v, v);
    }

    AVML_FINL float length(Unit_vector3R<float>) = delete;

    AVML_FINL float length(Vector3R<float> v) {
        __m128 t0 = _mm_set_ss(length2(v));
        __m128 t1 = _mm_sqrt_ss(t0);
        return _mm_cvtss_f32(t1);
    }

    AVML_FINL Unit_vector3R<float> assume_normalized(Vector3R<float> v) {
        return Unit_vector3R<float>::read_aligned(v.data());
    }

    AVML_FINL Unit_vector3R<float> normalize(Vector3R<float> v) {
        v /= length(v);
        return assume_normalized(v);
    }

    AVML_FINL Vector3R<float> cross(Vector3R<float> lhs, Vector3R<float> rhs) {
        return Vector3R<float> {
            lhs[1] * rhs[2] - lhs[2] * rhs[1],
            lhs[2] * rhs[0] - lhs[0] * rhs[2],
            lhs[0] * rhs[1] - lhs[1] * rhs[0]
        };
    }

    AVML_FINL Vector3R<float> project(Vector3R<float> a, Vector3R<float> b) {
        return (dot(a, b) / dot(b, b)) * b;
    }

    AVML_FINL Vector3R<float> project(Vector3R<float> a, Unit_vector3R<float> b) {
        return dot(a, b) * b;
    }

    AVML_FINL Vector3R<float> project_onto_plane(Vector3R<float> v, Unit_vector3R<float> normal) {
        return (v - project(v, normal));
    }

    AVML_FINL Vector3R<float> rotate(Vector3R<float> v, float angle, Unit_vector3R<float> axis) {
        float s = std::sin(angle);
        float c = std::cos(angle);

        return (v * c) + (cross(axis, v) * s) + (axis * dot(axis, v) * (1 - c));
    }

    AVML_FINL Unit_vector3R<float> rotate(Unit_vector3R<float> v, float angle, Unit_vector3R<float> axis) {
        return Unit_vector3R<float>::read_aligned(rotate(static_cast<Vector3R<float>>(v), angle, axis).data());
    }

    AVML_FINL Vector3R<float> rotate_x(Vector3R<float> v, float angle) {
        float s = std::sin(angle);
        float c = std::cos(angle);

        v[1] = v[1] * c - v[2] * s;
        v[2] = v[1] * s + v[2] * c;

        return assume_normalized(v);
    }

    AVML_FINL Vector3R<float> rotate_y(Vector3R<float> v, float angle) {
        float s = std::sin(angle);
        float c = std::cos(angle);

        v[0] = v[0] * c + v[2] * s;
        v[2] = v[2] * c - v[0] * s;

        return assume_normalized(v);
    }

    AVML_FINL Vector3R<float> rotate_z(Vector3R<float> v, float angle) {
        float s = std::sin(angle);
        float c = std::cos(angle);

        v[0] = v[0] * c - v[1] * s;
        v[1] = v[0] * s + v[1] * c;

        return assume_normalized(v);
    }

    AVML_FINL Vector3R<float> reflect(Vector3R<float> v, Unit_vector3R<float> normal) {
        return 2 * dot(v, normal) * normal - v;
    }

    AVML_FINL Unit_vector3R<float> reflect(Unit_vector3R<float> v, Unit_vector3R<float> normal) {
        return Unit_vector3R<float>::read_aligned(reflect(static_cast<Vector3R<float>>(v), normal).data());
    }

    //=====================================================
    // Vectorized math
    //=====================================================

    AVML_FINL Vector3R<float> abs(Vector3R<float> v) {
        v[0] = std::abs(v[0]);
        v[1] = std::abs(v[1]);
        v[2] = std::abs(v[2]);
        return v;
    }

    AVML_FINL Vector3R<float> max(Vector3R<float> u, Vector3R<float> v) {
        u[0] = std::max(u[0], v[0]);
        u[1] = std::max(u[1], v[1]);
        u[2] = std::max(u[2], v[2]);
        return u;
    }

    AVML_FINL Vector3R<float> min(Vector3R<float> u, Vector3R<float> v) {
        u[0] = std::min(u[0], v[0]);
        u[1] = std::min(u[1], v[1]);
        u[2] = std::min(u[2], v[2]);
        return u;
    }

    //=====================================================
    // Swizzling
    //=====================================================

    // Single component

    AVML_FINL float x(Vector3R<float> v) {
        #if defined(AVML_SSE)
        return _mm_cvtss_f32(avml_impl::load3f(v.data()));
        #else
        return v[0];
        #endif
    }

    AVML_FINL float y(Vector3R<float> v) {
        return v[1];
    }

    AVML_FINL float z(Vector3R<float> v) {
        return v[2];
    }

    // Two components

    AVML_FINL Vector2R<float> xx(Vector3R<float> v) {
        return {v[0], v[0]};
    }

    AVML_FINL Vector2R<float> xy(Vector3R<float> v) {
        return {v[0], v[1]};
    }

    AVML_FINL Vector2R<float> xz(Vector3R<float> v) {
        return {v[0], v[2]};
    }

    AVML_FINL Vector2R<float> yx(Vector3R<float> v) {
        return {v[1], v[0]};
    }

    AVML_FINL Vector2R<float> yy(Vector3R<float> v) {
        return {v[1], v[1]};
    }

    AVML_FINL Vector2R<float> yz(Vector3R<float> v) {
        return {v[1], v[2]};
    }

    AVML_FINL Vector2R<float> zx(Vector3R<float> v) {
        return {v[2], v[0]};
    }

    AVML_FINL Vector2R<float> zy(Vector3R<float> v) {
        return {v[2], v[1]};
    }

    AVML_FINL Vector2R<float> zz(Vector3R<float> v) {
        return {v[2], v[2]};
    }

    // Three components

    AVML_FINL Vector3R<float> xxx(Vector3R<float> v) {
        return {v[0], v[0], v[0]};
    }

    AVML_FINL Vector3R<float> xxy(Vector3R<float> v) {
        #if defined(AVML_SSE)
        __m128 t = avml_impl::load2f(v.data());
        t = _mm_unpacklo_ps(t, t);
        avml_impl::store2f(v.data(), t);
        return v;
        #else
        return {v[0], v[0], v[1]};
        #endif
    }

    AVML_FINL Vector3R<float> xxz(Vector3R<float> v) {
        return {v[0], v[0], v[2]};
    }

    AVML_FINL Vector3R<float> xyx(Vector3R<float> v) {
        #if defined(AVML_SSE)
        __m128 t = avml_impl::load2f(v.data());
        t = _mm_movelh_ps(t, t);
        avml_impl::store2f(v.data(), t);
        return v;
        #else
        return {v[0], v[1], v[0]};
        #endif
    }

    AVML_FINL Vector3R<float> xyy(Vector3R<float> v) {
        return {v[0], v[1], v[1]};
    }

    AVML_FINL Vector3R<float> xyz(Vector3R<float> v) {
        return v;
    }

    AVML_FINL Vector3R<float> xzx(Vector3R<float> v) {
        return {v[0], v[2], v[0]};
    }

    AVML_FINL Vector3R<float> xzy(Vector3R<float> v) {
        return {v[0], v[2], v[1]};
    }

    AVML_FINL Vector3R<float> xzz(Vector3R<float> v) {
        return {v[0], v[2], v[2]};
    }

    AVML_FINL Vector3R<float> yxx(Vector3R<float> v) {
        return {v[1], v[0], v[0]};
    }

    AVML_FINL Vector3R<float> yxy(Vector3R<float> v) {
        return {v[1], v[0], v[1]};
    }

    AVML_FINL Vector3R<float> yxz(Vector3R<float> v) {
        return {v[1], v[0], v[2]};
    }

    AVML_FINL Vector3R<float> yyx(Vector3R<float> v) {
        return {v[1], v[1], v[0]};
    }

    AVML_FINL Vector3R<float> yyy(Vector3R<float> v) {
        return {v[1], v[1], v[1]};
    }

    AVML_FINL Vector3R<float> yyz(Vector3R<float> v) {
        return {v[1], v[1], v[2]};
    }

    AVML_FINL Vector3R<float> yzx(Vector3R<float> v) {
        return {v[1], v[2], v[0]};
    }

    AVML_FINL Vector3R<float> yzy(Vector3R<float> v) {
        return {v[1], v[2], v[1]};
    }

    AVML_FINL Vector3R<float> yzz(Vector3R<float> v) {
        return {v[1], v[2], v[2]};
    }

    AVML_FINL Vector3R<float> zxx(Vector3R<float> v) {
        return {v[2], v[0], v[0]};
    }

    AVML_FINL Vector3R<float> zxy(Vector3R<float> v) {
        return {v[2], v[0], v[1]};
    }

    AVML_FINL Vector3R<float> zxz(Vector3R<float> v) {
        return {v[2], v[0], v[2]};
    }

    AVML_FINL Vector3R<float> zyx(Vector3R<float> v) {
        return {v[2], v[1], v[0]};
    }

    AVML_FINL Vector3R<float> zyy(Vector3R<float> v) {
        return {v[2], v[1], v[1]};
    }

    AVML_FINL Vector3R<float> zyz(Vector3R<float> v) {
        return {v[2], v[1], v[2]};
    }

    AVML_FINL Vector3R<float> zzx(Vector3R<float> v) {
        return {v[2], v[2], v[0]};
    }

    AVML_FINL Vector3R<float> zzy(Vector3R<float> v) {
        return {v[2], v[2], v[1]};
    }

    AVML_FINL Vector3R<float> zzz(Vector3R<float> v) {
        return {v[2], v[2], v[2]};
    }

}
