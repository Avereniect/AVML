namespace avml {

    template<>
    class alignas(alignof(float) * 2) Vector2R<float> {
    public:

        using scalar = float;

        static constexpr unsigned width = 2;

        //=================================================
        // Creation functions
        //=================================================

        AVML_FINL static Vector2R read(const float* p) {
            Vector2R ret;
            #if defined(AVML_AVX512VL)
            _mm_mask_storeu_ps(
                (void*) p,
                0x07,
                _mm_maskz_loadu_ps(0x07, p)
            );

            #elif defined(AVML_AVX)
            _mm_maskstore_ps(
                ret.elements,
                avml_impl::fmask0111,
                _mm_maskload_ps(p, avml_impl::fmask0111)
            );

            #elif defined(AVML_SSE2)
            _mm_store_sd(
                reinterpret_cast<double*>(ret.elements),
                _mm_load_sd(reinterpret_cast<const double*>(p))
            );
            #else
            ret.elements[0] = p[0];
            ret.elements[1] = p[1];

            #endif
            return ret;
        }

        AVML_FINL static Vector2R read_aligned(const float* p) {
            Vector2R ret;
            #if defined(AVML_SSE2)
            avml_impl::store2f(ret.elements, avml_impl::load2f(p));

            #else
            ret.elements[0] = p[0];
            ret.elements[1] = p[1];

            #endif
            return ret;
        }

        //=================================================
        // -ctors
        //=================================================

        //TODO: Implement conversions from other vectors

        //explicit AVML_FINL Vector2R(Vector2R<double> v):
        //    elements{} {}

        explicit AVML_FINL Vector2R(float v):
            elements{} {

            #if defined(AVML_AVX)
            __m128 r = _mm_set_ss(v);
            r = _mm_permute_ps(r, 0x00);
            avml_impl::store2f(elements, r);

            #elif defined(AVML_SSE)
            __m128 r = _mm_set_ss(v);
            r = _mm_shuffle_ps(r, r, 0x00);
            avml_impl::store2f(elements, r);

            #else
            elements[0] = v;
            elements[1] = v;

            #endif
        }

        AVML_FINL Vector2R(float x, float y):
            elements{x, y} {}

        AVML_FINL Vector2R(Unit_vector2R<float> v):
            elements{} {

            #if defined(AVML_SSE)
            __m128 r = avml_impl::load2f(v.data());
            avml_impl::store2f(elements, r);

            #else
            elements[0] = v[0];
            elements[1] = v[1];

            #endif
        }

        template<class R>
        explicit AVML_FINL Vector2R(Vector2R<R> v):
            elements{
                static_cast<float>(v[0]),
                static_cast<float>(v[1])
            } {}

        explicit AVML_FINL Vector2R(Vector2R<double> v):
            elements{} {

            #if defined(AVML_SSE2)
            __m128d t0 = _mm_load_pd(v.data());
            __m128 t1 = _mm_cvtpd_ps(t0);
            avml_impl::store2f(elements, t1);

            #else
            elements[0] = static_cast<double>(v[0]);
            elements[1] = static_cast<double>(v[1]);

            #endif
        }

        Vector2R() = default;
        Vector2R(const Vector2R&) = default;
        Vector2R(Vector2R&&) = default;
        ~Vector2R() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Vector2R& operator=(const Vector2R&) = default;
        Vector2R& operator=(Vector2R&&) = default;

        //=================================================
        // Unary arithmetic operators
        //=================================================

        AVML_FINL Vector2R operator+() const {
            return *this;
        }

        AVML_FINL Vector2R operator-() const {
            Vector2R ret;

            #if defined(AVML_SSE)
            __m128 r = avml_impl::load2f(elements);
            r = _mm_sub_ps(_mm_setzero_ps(), r);
            avml_impl::store2f(ret.data(), r);

            #else
            ret[0] = -elements[0];
            ret[1] = -elements[1];

            #endif

            return ret;
        }

        //=================================================
        // Arithmetic assignment operators
        //=================================================

        AVML_FINL Vector2R& operator+=(const Vector2R& rhs) {
            #if defined(AVML_SSE)
            __m128 r0 = avml_impl::load2f(elements);
            __m128 r1 = avml_impl::load2f(rhs.elements);

            __m128 writeback = _mm_add_ps(r0, r1);
            avml_impl::store2f(elements, writeback);
            #else
            for (unsigned i = 0; i < width; ++i) {
                elements[i] += rhs[i];
            }
            #endif
            return *this;
        }

        AVML_FINL Vector2R& operator-=(const Vector2R& rhs) {
            #if defined(AVML_SSE)
            __m128 r0 = avml_impl::load2f(elements);
            __m128 r1 = avml_impl::load2f(rhs.elements);

            __m128 writeback = _mm_sub_ps(r0, r1);
            avml_impl::store2f(elements, writeback);
            #else
            for (unsigned i = 0; i < width; ++i) {
                elements[i] -= rhs[i];
            }
            #endif
            return *this;
        }

        AVML_FINL Vector2R& operator*=(const Vector2R rhs) {
            #if defined(AVML_SSE)
            __m128 r0 = avml_impl::load2f(elements);
            __m128 r1 = avml_impl::load2f(rhs.elements);

            __m128 writeback = _mm_mul_ps(r0, r1);
            avml_impl::store2f(elements, writeback);

            #else
            for (unsigned i = 0; i < width; ++i) {
                elements[i] *= rhs[i];
            }

            #endif
            return *this;
        }

        AVML_FINL Vector2R& operator*=(const scalar rhs) {
            this->operator*=(Vector2R(rhs));
            return *this;
        }

        AVML_FINL Vector2R& operator/=(const Vector2R rhs) {
            #if defined(AVML_SSE)
            __m128 a = avml_impl::load2f(elements);
            __m128 b = avml_impl::load2f(rhs.data());

            __m128 t = _mm_div_ps(a, b);
            avml_impl::store2f(elements, t);

            #else
            for (unsigned i = 0; i < width; ++i) {
                elements[i] /= rhs[i];
            }

            #endif
            return *this;
        }

        AVML_FINL Vector2R& operator/=(const scalar rhs) {
            this->operator/=(Vector2R(rhs));
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

        //=================================================
        // Conversion operators
        //=================================================

        template<class R>
        explicit operator Vector2R<R>() const {
            return Vector2R{
                static_cast<R>(elements[0]),
                static_cast<R>(elements[1])
            };
        }

        explicit operator Vector2R<double>() const {
            Vector2R<double> ret;

            #if defined(AVML_SSE)
            __m128d t = _mm_cvtps_pd(avml_impl::load2f(elements));
            avml_impl::store2d(ret.data(), t);

            #else
            ret[0] = static_cast<double>(elements[0]);
            ret[1] = static_cast<double>(elements[1]);

            #endif
            return ret;
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

    AVML_FINL bool operator==(Vector2R<float> lhs, Vector2R<float> rhs) {
        #if defined(AVML_SSE)
        __m128 a = avml_impl::load2f(lhs.data());
        __m128 b = avml_impl::load2f(rhs.data());

        __m128 t0 = _mm_cmpeq_ps(a, b);
        int t1 = _mm_movemask_ps(t0);
        return (t1 == 0x0F);

        #else
        return
            (lhs[0] == rhs[0]) &&
            (lhs[1] == rhs[1]);
        #endif
    }

    AVML_FINL bool operator!=(Vector2R<float> lhs, Vector2R<float> rhs) {
        #if defined(AVML_SSE)
        __m128 a = avml_impl::load2f(lhs.data());
        __m128 b = avml_impl::load2f(rhs.data());

        __m128 t0 = _mm_cmpeq_ps(a, b);
        int t1 = _mm_movemask_ps(t0);
        return (t1 == 0x0E);

        #else
        return
            (lhs[0] != rhs[0]) ||
            (lhs[1] != rhs[1]);
        #endif
    }

    //=====================================================
    // Arithmetic operators
    //=====================================================

    AVML_FINL Vector2R<float> operator+(Vector2R<float> lhs, Vector2R<float> rhs) {
        lhs += rhs;
        return lhs;
    }

    AVML_FINL Vector2R<float> operator-(Vector2R<float> lhs, Vector2R<float> rhs) {
        lhs -= rhs;
        return lhs;
    }

    AVML_FINL Vector2R<float> operator*(Vector2R<float> lhs, Vector2R<float> rhs) {
        lhs *= rhs;
        return lhs;
    }

    AVML_FINL Vector2R<float> operator*(Vector2R<float> lhs, float rhs) {
        lhs *= rhs;
        return lhs;
    }

    AVML_FINL Vector2R<float> operator*(float lhs, Vector2R<float> rhs) {
        rhs *= lhs;
        return rhs;
    }

    AVML_FINL Vector2R<float> operator/(Vector2R<float> lhs, float rhs) {
        lhs /= rhs;
        return lhs;
    }

    AVML_FINL Vector2R<float> operator/(Vector2R<float> lhs, Vector2R<float> rhs) {
        lhs /= rhs;
        return lhs;
    }

    //=====================================================
    // Vector math
    //=====================================================

    AVML_FINL float dot(Vector2R<float> lhs, Vector2R<float> rhs) {
        #if defined(AVML_SSE3)
        __m128 a = avml_impl::load2f(lhs.data());
        __m128 b = avml_impl::load2f(rhs.data());

        __m128 t0 = _mm_mul_ps(a, b);
        __m128 t1 = _mm_movehdup_ps(t0);
        __m128 t2 = _mm_add_ss(t0, t1);
        return _mm_cvtss_f32(t2);

        #elif defined(AVML_SSE)
        __m128 a = avml_impl::load2f(lhs.data());
        __m128 b = avml_impl::load2f(rhs.data());

        __m128 t0 = _mm_mul_ps(a, b);
        __m128 t1 = _mm_shuffle_ps(t0, t0, 0x55);
        __m128 t2 = _mm_add_ss(t0, t1);
        return _mm_cvtss_f32(t2);

        #else
        return
            lhs[0] * rhs[0] +
            lhs[1] * rhs[1];
        #endif
    }

    AVML_FINL float length2(Unit_vector2R<float>) = delete;

    AVML_FINL float length2(Vector2R<float> v) {
        return dot(v, v);
    }

    AVML_FINL float length(Unit_vector2R<float>) = delete;

    AVML_FINL float length(Vector2R<float> v) {
        __m128 t0 = _mm_set_ss(length2(v));
        __m128 t1 = _mm_sqrt_ss(t0);
        return _mm_cvtss_f32(t1);
    }

    AVML_FINL Unit_vector2R<float> normalize(Vector2R<float> v) {
        v /= length(v);
        return Unit_vector2R<float>::read_aligned(v.data());
    }

    AVML_FINL Unit_vector2R<float> assume_normalized(Vector2R<float> v) {
        return Unit_vector2R<float>::read_aligned(v.data());
    }

    AVML_FINL Vector2R<float> project(Vector2R<float> a, Vector2R<float> b) {
        return (dot(a, b) / dot(b, b)) * b;
    }

    AVML_FINL Vector2R<float> project(Vector2R<float> a, Unit_vector2R<float> b) {
        return dot(a, b) * b;
    }

    AVML_FINL Vector2R<float> rotate(Vector2R<float> v, float angle) {
        #if defined(AVML_AVX) && (defined(AVML_GCC) || defined(AVML_CLANG))
        float c, s;
        sincosf(angle, &c, &s);

        __m128 r_xy00 = avml_impl::load2f(v.data());
        __m128 r_c000 = _mm_set_ps1(c);
        __m128 r_s000 = _mm_set_ps1(s);

        __m128 r_xxyy = _mm_unpacklo_ps(r_xy00, r_xy00);

        __m128 r_cs00 = _mm_unpacklo_ps(r_c000, r_s000);
        __m128 r_cssc = _mm_permute_ps(r_cs00, 0x14);

        __m128 t0 = _mm_mul_ps(r_cssc, r_xxyy);
        __m128 t1 = _mm_movehl_ps(t0, t0);

        __m128 t4 = _mm_addsub_ps(t0, t1);

        Vector2R<float> ret;
        avml_impl::store2f(ret.data(), t4);
        return ret;


        #elif defined(AVML_SSE3) && (defined(AVML_GCC) || defined(AVML_CLANG))
        float c, s;
        sincosf(angle, &c, &s);

        __m128 r_xy00 = avml_impl::load2f(v.data());
        __m128 r_c000 = _mm_set_ps1(c);
        __m128 r_s000 = _mm_set_ps1(s);

        __m128 r_xxyy = _mm_unpacklo_ps(r_xy00, r_xy00);

        __m128 r_cs00 = _mm_unpacklo_ps(r_c000, r_s000);
        __m128 r_cssc = _mm_shuffle_ps(r_cs00, r_cs00, 0x14);

        __m128 t0 = _mm_mul_ps(r_cssc, r_xxyy);
        __m128 t1 = _mm_movehl_ps(t0, t0);

        __m128 t4 = _mm_addsub_ps(t0, t1);

        Vector2R<float> ret;
        avml_impl::store2f(ret.data(), t4);
        return ret;

        #elif defined(AVML_SSE) && (defined(AVML_GCC) || defined(AVML_CLANG))
        float c, s;
        sincosf(angle, &c, &s);

        __m128 r_xy00 = avml_impl::load2f(v.data());
        __m128 r_c000 = _mm_set_ps1(c);
        __m128 r_s000 = _mm_set_ps1(s);

        __m128 r_xxyy = _mm_unpacklo_ps(r_xy00, r_xy00);

        __m128 r_cs00 = _mm_unpacklo_ps(r_c000, r_s000);
        __m128 r_cssc = _mm_shuffle_ps(r_cs00, r_cs00, 0x14);

        __m128 t0 = _mm_mul_ps(r_cssc, r_xxyy);
        __m128 t1 = _mm_movehl_ps(t0, t0);

        //TODO: Test xoring with mask generated on the fly to negate first element instead?
        __m128 t2 = _mm_add_ss(t1, t1);
        __m128 t3 = _mm_sub_ss(t1, t2);

        __m128 t4 = _mm_add_ps(t0, t3);

        Vector2R<float> ret;
        avml_impl::store2f(ret.data(), t4);
        return ret;

        #else
        float cos = std::cos(angle);
        float sin = std::sin(angle);

        return Vector2R<float>{
            v[0] * cos - v[1] * sin,
            v[0] * sin + v[1] * cos
        };
        #endif
    }

    AVML_FINL Vector2R<float> reflect(Vector2R<float> v, Unit_vector2R<float> normal) {
        return 2.0f * dot(v, normal) * normal - v;
    }

    AVML_FINL Unit_vector2R<float> reflect(Unit_vector2R<float> v, Unit_vector2R<float> normal) {
        return Unit_vector2R<float>::read_aligned(reflect(static_cast<Vector2R<float>>(v), normal).data());
    }

    //=====================================================
    // Vectorized math
    //=====================================================

    AVML_FINL Vector2R<float> abs(Vector2R<float> v) {
        #if defined(AVML_SSE)
        __m128 a = avml_impl::load2f(v.data());
        __m128 d = _mm_and_ps(a, avml_impl::sign_bit_mask);
        avml_impl::store2f(v.data(), d);

        #else
        v[0] = -v[0];
        v[1] = -v[1];

        #endif
        return v;
    }

    AVML_FINL Vector2R<float> max(Vector2R<float> u, Vector2R<float> v) {
        #if defined(AVML_SSE)
        //TODO: Handle special NANs correctly
        __m128 a = avml_impl::load2f(u.data());
        __m128 b = avml_impl::load2f(v.data());

        __m128 t = _mm_max_ps(a, b);
        avml_impl::store2f(u.data(), t);

        #else

        u[0] = std::max(u[0], v[0]);
        u[1] = std::max(u[1], v[1]);
        #endif
        return u;
    }

    AVML_FINL Vector2R<float> min(Vector2R<float> u, Vector2R<float> v) {
        #if defined(AVML_SSE)
        //TODO: Handle special NANs correctly
        __m128 a = avml_impl::load2f(u.data());
        __m128 b = avml_impl::load2f(v.data());

        __m128 t = _mm_min_ps(a, b);
        avml_impl::store2f(u.data(), t);

        #else
        u[0] = std::min(u[0], v[0]);
        u[1] = std::min(u[1], v[1]);

        #endif
        return u;
    }

    //=====================================================
    // Swizzling
    //=====================================================

    // Single component

    AVML_FINL float x(Vector2R<float> v) {
        #if defined(AVML_SSE)
        return _mm_cvtss_f32(avml_impl::load2f(v.data()));
        #else
        return v[0];
        #endif
    }

    AVML_FINL float y(Vector2R<float> v) {
        #if defined(AVML_SSE3)
        __m128 t0 = avml_impl::load2f(v.data());
        __m128 t1 = _mm_movehdup_ps(t0);
        return _mm_cvtss_f32(t1);

        #elif defined(AVML_SSE)
        __m128 t0 = avml_impl::load2f(v.data());
        __m128 t1 = _mm_shuffle_ps(t0, t0, 0x55);
        return _mm_cvtss_f32(t1);

        #else
        return v[1];

        #endif
    }

    // Two component
    AVML_FINL Vector2R<float> xx(Vector2R<float> v) {
        #if defined(AVML_SSE)
        __m128 t = avml_impl::load2f(v.data());
        t = _mm_unpacklo_ps(t, t);
        avml_impl::store2f(v.data(), t);
        return v;

        #else
        return {v[0], v[0]};

        #endif
    }

    AVML_FINL Vector2R<float> xy(Vector2R<float> v) {
        return v;
    }

    AVML_FINL Vector2R<float> yx(Vector2R<float> v) {
        #if defined(AVML_AVX)
        __m128 t0 = avml_impl::load2f(v.data());
        __m128 t1 = _mm_permute_ps(t0, 0x01);
        avml_impl::store2f(v.data(), t1);
        return v;

        #elif defined(AVML_SSE)
        __m128 t0 = avml_impl::load2f(v.data());
        __m128 t1 = _mm_shuffle_ps(t0, t0, 0x01);
        avml_impl::store2f(v.data(), t1);
        return v;

        #else
        return {v[1], v[0]};

        #endif
    }

    AVML_FINL Vector2R<float> yy(Vector2R<float> v) {
        #if defined(AVML_SSE3)
        __m128 t0 = avml_impl::load2f(v.data());
        __m128 t1 = _mm_movehdup_ps(t0);
        avml_impl::store2f(v.data(), t1);
        return v;

        #elif defined(AVML_SSE)
        __m128 t0 = avml_impl::load2f(v.data());
        __m128 t1 = _mm_shuffle_ps(t0, t0, 0x55);
        avml_impl::store2f(v.data(), t1);
        return v;

        #else
        return {v[1], v[0]};

        #endif
    }

}
