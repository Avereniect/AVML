namespace avml {

    template<>
    class alignas(alignof(float) * 4) Unit_vector4R<float> {
    public:

        using scalar = float;

        static constexpr unsigned width = 4;

        //=================================================
        // Creation functions
        //=================================================

        AVML_FINL static Unit_vector4R read(const float* p) {
            Unit_vector4R ret;

            #if defined(AVML_SSE)
            __m128 t = _mm_loadu_ps(p);
            _mm_store_ps(ret.elements, t);

            #else
            ret.elements[0] = p[0];
            ret.elements[1] = p[1];
            ret.elements[2] = p[2];
            ret.elements[3] = p[3];

            #endif

            return ret;
        }

        AVML_FINL static Unit_vector4R read_aligned(const float* p) {
            Unit_vector4R ret;

            #if defined(AVML_SSE)
            avml_impl::store4f(ret.elements, avml_impl::load4f(p));

            #else
            ret.elements[0] = p[0];
            ret.elements[1] = p[1];
            ret.elements[2] = p[2];
            ret.elements[3] = p[3];

            #endif
            return ret;
        }

        //=================================================
        // -ctors
        //=================================================

        AVML_FINL Unit_vector4R(float x, float y, float z, float w) noexcept:
            elements() {

            #if defined(AVML_FMA)
            __m128 r_x000 = _mm_set_ss(x);
            __m128 r_y000 = _mm_set_ss(y);
            __m128 r_z000 = _mm_set_ss(z);
            __m128 r_w000 = _mm_set_ss(w);

            __m128 r_xy00 = _mm_unpacklo_ps(r_x000, r_y000);
            __m128 r_zw00 = _mm_unpacklo_ps(r_z000, r_w000);
            __m128 r_xyzw = _mm_movelh_ps(r_xy00, r_zw00);

            __m128 t0 = _mm_mul_ss(r_x000, r_x000);
            __m128 t1 = _mm_fmadd_ss(r_y000, r_y000, t0);
            __m128 t2 = _mm_fmadd_ss(r_z000, r_z000, t1);
            __m128 l = _mm_fmadd_ss(r_w000, r_w000, t2);

            l = _mm_sqrt_ss(l);
            __m128 r_llll = _mm_permute_ps(l, 0x00);

            __m128 d = _mm_div_ps(r_xyzw, r_llll);
            avml_impl::store4f(elements, d);

            #elif defined(AVML_AVX)
            __m128 r_x000 = _mm_set_ss(x);
            __m128 r_y000 = _mm_set_ss(y);
            __m128 r_z000 = _mm_set_ss(z);
            __m128 r_w000 = _mm_set_ss(w);

            __m128 r_xy00 = _mm_unpacklo_ps(r_x000, r_y000);
            __m128 r_zw00 = _mm_unpacklo_ps(r_z000, r_w000);
            __m128 r_xyzw = _mm_movelh_ps(r_xy00, r_zw00);

            __m128 t0 = _mm_mul_ps(r_xyzw, r_xyzw);
            __m128 t1 = _mm_movelh_ps(t0, t0);
            __m128 t2 = _mm_add_ps(t0, t1);
            __m128 t3 = _mm_permute_ps(t2, 0x55);
            __m128 r_l000 = _mm_permute_ps(t3, 0x00);
            r_l000 = _mm_sqrt_ss(r_l000);
            __m128 r_llll = _mm_permute_ps(r_l000, 0x00);

            __m128 d = _mm_div_ps(r_xyzw, r_llll);

            avml_impl::store4f(elements, d);

            #elif defined(AVML_SSE)
            __m128 r_x000 = _mm_set_ss(x);
            __m128 r_y000 = _mm_set_ss(y);
            __m128 r_z000 = _mm_set_ss(z);
            __m128 r_w000 = _mm_set_ss(w);

            __m128 r_xy00 = _mm_unpacklo_ps(r_x000, r_y000);
            __m128 r_zw00 = _mm_unpacklo_ps(r_z000, r_w000);
            __m128 r_xyzw = _mm_movelh_ps(r_xy00, r_zw00);

            __m128 t0 = _mm_mul_ps(r_xyzw, r_xyzw);
            __m128 t1 = _mm_movelh_ps(t0, t0);
            __m128 t2 = _mm_add_ps(t0, t1);
            __m128 t3 = _mm_shuffle_ps(t2, t2, 0x55);
            __m128 r_l000 = _mm_shuffle_ps(t3, t3, 0x00);
            r_l000 = _mm_sqrt_ss(r_l000);
            __m128 r_llll = _mm_shuffle_ps(r_l000, r_l000, 0x00);

            __m128 d = _mm_div_ps(r_xyzw, r_llll);

            avml_impl::store4f(elements, d);

            #else

            float length = std::sqrt(x * x + y * y + z * z + w * w);

            elements[0] = x / length;
            elements[1] = y / length;
            elements[2] = z / length;
            elements[3] = w / length;
            #endif
        }

        AVML_FINL Unit_vector4R(Unit_vector3R<float> v) :
            elements{v[0], v[1], v[2], 0.0f} {}

        template<class R>
        explicit AVML_FINL Unit_vector4R(Unit_vector4R<R> v):
            elements{
                static_cast<float>(v[0]),
                static_cast<float>(v[1]),
                static_cast<float>(v[2]),
                static_cast<float>(v[3])
            } {}

        explicit AVML_FINL Unit_vector4R(Unit_vector4R<double> v):
            elements{} {

            #if defined(AVML_AVX)
            __m256d c = avml_impl::load4d(v.data());

            __m128 d = _mm256_cvtpd_ps(c);
            avml_impl::store4f(elements, d);

            #elif defined(AVML_SSE2)
            auto c = avml_impl::load4d(v.data());

            __m128 lo = _mm_cvtpd_ps(c[0]);
            __m128 hi = _mm_cvtpd_ps(c[1]);

            __m128 d = _mm_movelh_ps(lo, hi);
            avml_impl::store4f(elements, d);

            #else
            elements[0] = static_cast<double>(v[0]);
            elements[1] = static_cast<double>(v[1]);
            elements[2] = static_cast<double>(v[2]);
            #endif
        }

        Unit_vector4R() = default;
        Unit_vector4R(const Unit_vector4R&) = default;
        Unit_vector4R(Unit_vector4R&&) = default;
        ~Unit_vector4R() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Unit_vector4R& operator=(const Unit_vector4R&) = default;
        Unit_vector4R& operator=(Unit_vector4R&&) = default;

        //=================================================
        // Unary arithmetic operators
        //=================================================

        AVML_FINL Unit_vector4R operator+() const {
            return *this;
        }

        AVML_FINL Unit_vector4R operator-() const {
            Unit_vector4R ret;

            #ifdef AVML_SSE
            __m128 r_xy00 = avml_impl::load4f(elements);
            __m128 diff = _mm_sub_ps(_mm_setzero_ps(), r_xy00);
            avml_impl::store2f(ret.elements, diff);

            #else
            ret.elements[0] = -elements[0];
            ret.elements[1] = -elements[1];

            #endif

            return ret;
        }

        //=================================================
        // Accessors
        //=================================================

        AVML_FINL const float& operator[](unsigned i) const {
            return elements[i];
        }

        AVML_FINL const float* data() const {
            return elements;
        }

        //=================================================
        // Conversion operators
        //=================================================

        template<class U>
        explicit operator Unit_vector2R<U>() const {
            Unit_vector2R<U> ret;
            ret.elements[0] = static_cast<U>(elements[0]);
            ret.elements[1] = static_cast<U>(elements[1]);
            return ret;
        }

        explicit operator Unit_vector4R<double>() const {
            Unit_vector4R<double> ret;
            double* p = const_cast<double*>(ret.data());

            #if defined(AVML_AVX)
            __m128 t = avml_impl::load4f(elements);
            __m256d d = _mm256_cvtps_pd(t);

            avml_impl::store4d(p, d);
            #elif defined(AVML_SSE2)
            __m128 d = avml_impl::load4f(elements);
            __m128d d0 = _mm_cvtps_pd(d);
            __m128d d1 = _mm_cvtps_pd(_mm_movehl_ps(d, d));
            avml_impl::store4d(p, d0, d1);
            #else
            p[0] = static_cast<double>(elements[0]);
            p[1] = static_cast<double>(elements[1]);
            p[2] = static_cast<double>(elements[2]);
            p[3] = static_cast<double>(elements[3]);
            #endif
            return ret;
        }

    private:

        //=================================================
        // Instance members
        //=================================================

        float elements[width] = {1.0f, 0.0f, 0.0f, 0.0f};

    };

    //=====================================================
    // Vectorized math
    //=====================================================

    AVML_FINL Unit_vector4R<float> abs(Unit_vector4R<float> v) {
        Unit_vector4R<float> ret;
        #if defined(AVML_SSE)
        __m128 vec_data = avml_impl::load4f(v.data());
        vec_data = _mm_and_ps(avml_impl::sign_bit_mask, vec_data);

        avml_impl::store4f(const_cast<float*>(ret.data()), vec_data);

        #else
        float* p = const_cast<float*>(ret.data());
        p[0] = -v[0];
        p[1] = -v[1];
        p[2] = -v[2];
        p[3] = -v[3];

        #endif
        return ret;
    }

}
