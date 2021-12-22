namespace avml {

    template<>
    class alignas(alignof(float) * 2) Unit_vector2R<float> {
    public:

        using scalar = float;

        static constexpr unsigned width = 2;

        //=================================================
        // Creation functions
        //=================================================

        AVML_FINL static Unit_vector2R read(const float* p) {
            Unit_vector2R ret;
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

        AVML_FINL static Unit_vector2R read_aligned(const float* p) {
            Unit_vector2R ret;
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

        AVML_FINL Unit_vector2R(float x, float y) noexcept:
            elements() {

            #if defined(AVML_AVX)
            __m128 r_x000 = _mm_set_ss(x);
            __m128 r_y000 = _mm_set_ss(y);
            __m128 r_xy00 = _mm_unpacklo_ps(r_x000, r_y000);
            r_xy00 = _mm_mul_ps(r_xy00, r_xy00);

            __m128 r_yx00 = _mm_permute_ps(r_xy00, 0xF1);

            __m128 r_ll00 = _mm_add_ps(r_xy00, r_yx00);
            r_ll00 = _mm_sqrt_ps(r_ll00);

            r_xy00 = _mm_div_ps(r_xy00, r_ll00);
            avml_impl::store2f(elements, r_xy00);

            #elif defined(AVML_SSE)
            __m128 r_x000 = _mm_load1_ps(&x);
            __m128 r_y000 = _mm_load1_ps(&y);
            __m128 r_xy00 = _mm_unpacklo_ps(r_x000, r_y000);
            r_xy00 = _mm_mul_ps(r_xy00, r_xy00);

            __m128 r_yx00 = _mm_shuffle_ps(r_xy00, r_xy00, 0xF1);

            __m128 r_ll00 = _mm_add_ps(r_xy00, r_yx00);
            r_ll00 = _mm_sqrt_ps(r_ll00);

            r_xy00 = _mm_div_ps(r_xy00, r_ll00);
            avml_impl::store2f(elements, r_xy00);
            #else

            float length = std::sqrt(x * x + y * y);
            elements[0] = x / length;
            elements[1] = y / length;
            #endif
        }

        template<class R>
        explicit AVML_FINL Unit_vector2R(Unit_vector2R<R> v):
            elements{
                static_cast<float>(v[0]),
                static_cast<float>(v[1])
            } {}

        explicit AVML_FINL Unit_vector2R(Unit_vector2R<double> v):
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

        Unit_vector2R() = default;
        Unit_vector2R(const Unit_vector2R&) = default;
        Unit_vector2R(Unit_vector2R&&) noexcept = default;
        ~Unit_vector2R() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Unit_vector2R& operator=(const Unit_vector2R&) = default;
        Unit_vector2R& operator=(Unit_vector2R&&) noexcept = default;

        //=================================================
        // Unary arithmetic operators
        //=================================================

        AVML_FINL Unit_vector2R operator+() const {
            return *this;
        }

        AVML_FINL Unit_vector2R operator-() const {
            Unit_vector2R ret;

            #ifdef AVML_SSE
            __m128 r_xy00 = avml_impl::load2f(elements);
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

        explicit operator Unit_vector2R<double>() const {
            Unit_vector2R<double> ret;
            double* p = const_cast<double*>(ret.data());

            #if defined(AVML_SSE)
            __m128d t = _mm_cvtps_pd(avml_impl::load2f(elements));
            avml_impl::store2d(p, t);

            #else
            p[0] = static_cast<double>(elements[0]);
            p[1] = static_cast<double>(elements[1]);

            #endif
            return ret;
        }

    private:

        //=================================================
        // Instance members
        //=================================================

        float elements[width] = {1.0f, 0.0f};

    };

    //=====================================================
    // Vectorized math
    //=====================================================

    AVML_FINL Unit_vector2R<float> abs(Unit_vector2R<float> v) {
        Unit_vector2R<float> ret;
        #if defined(AVML_SSE)
        __m128 vec_data = avml_impl::load2f(v.data());
        vec_data = _mm_and_ps(avml_impl::sign_bit_mask, vec_data);

        avml_impl::store2f(const_cast<float*>(ret.data()), vec_data);
        return ret;

        #else
        float* data = const_cast<float*>(ret.data());
        data[0] = -v[0];
        data[1] = -v[1];
        return v;

        #endif
    }

}
