#ifndef AVML_UVEC3F_IPP
#define AVML_UVEC3F_IPP

namespace avml {

    template<>
    class alignas(alignof(float) * 1) Unit_vector3R<float> {
    public:

        using scalar = float;

        static constexpr unsigned width = 3;

        //=================================================
        // Creation functions
        //=================================================

        AVML_FINL static Unit_vector3R read(const float* p) {
            Unit_vector3R ret;
            #if defined(AVML_SSE)
            avml_impl::store3f(ret.elements, avml_impl::load3f(p));
            #else
            ret.elements[0] = p[0];
            ret.elements[1] = p[1];
            ret.elements[2] = p[2];
            #endif
            return ret;
        }

        AVML_FINL static Unit_vector3R read_aligned(const float* p) {
            return Unit_vector3R::read(p);
        }

        //=================================================
        // -ctors
        //=================================================

        AVML_FINL Unit_vector3R(float x, float y, float z) noexcept:
            elements() {

            #if defined(AVML_FMA)
            __m128 r_x000 = _mm_set_ss(x);
            __m128 r_y000 = _mm_set_ss(y);
            __m128 r_z000 = _mm_set_ss(z);

            __m128 r_xy00 = _mm_unpacklo_ps(r_x000, r_y000);
            __m128 r_xyz0 = _mm_movelh_ps(r_xy00, r_z000);

            __m128 t0 = _mm_mul_ss(r_x000, r_x000);
            __m128 t1 = _mm_fmadd_ss(r_y000, r_y000, t0);
            __m128 t2 = _mm_fmadd_ss(r_z000, r_z000, t1);

            __m128 r_l000 = _mm_sqrt_ss(t2);
            __m128 r_llll = _mm_permute_ps(r_l000, 0x00);

            __m128 d = _mm_div_ps(r_xyz0, r_llll);

            avml_impl::store3f(elements, d);

            #elif defined(AVML_AVX)
            __m128 r_x000 = _mm_set_ss(x);
            __m128 r_y000 = _mm_set_ss(y);
            __m128 r_z000 = _mm_set_ss(z);

            __m128 r_xy00 = _mm_unpacklo_ps(r_x000, r_y000);
            __m128 r_xyz0 = _mm_movelh_ps(r_xy00, r_z000);
            __m128 r_xyz02 = _mm_mul_ps(r_xyz0, r_xyz0);

            __m128 r_z0z0 = _mm_movehl_ps(r_xyz02, r_xyz02);
            __m128 t0 = _mm_add_ps(r_xyz02, r_z0z0);
            __m128 t1 = _mm_permute_ps(t0, 0x01);

            __m128 r_l000 = _mm_add_ss(t0, t1);
            r_l000 = _mm_sqrt_ss(r_l000);
            __m128 r_llll = _mm_permute_ps(r_l000, 0x00);

            __m128 d = _mm_div_ps(r_xyz0, r_llll);

            avml_impl::store3f(elements, d);

            #elif defined(AVML_SSE)
            __m128 r_x000 = _mm_set_ss(x);
            __m128 r_y000 = _mm_set_ss(y);
            __m128 r_z000 = _mm_set_ss(z);

            __m128 r_xy00 = _mm_unpacklo_ps(r_x000, r_y000);
            __m128 r_xyz0 = _mm_movelh_ps(r_xy00, r_z000);
            __m128 r_xyz02 = _mm_mul_ps(r_xyz0, r_xyz0);

            __m128 r_z0z0 = _mm_movehl_ps(r_xyz02, r_xyz02);
            __m128 t0 = _mm_add_ps(r_xyz02, r_z0z0);
            __m128 t1 = _mm_shuffle_ps(t0, t0, 0x01);

            __m128 r_l000 = _mm_add_ss(t0, t1);
            r_l000 = _mm_sqrt_ss(r_l000);
            __m128 r_llll = _mm_shuffle_ps(r_l000, r_l000, 0x00);

            __m128 d = _mm_div_ps(r_xyz0, r_llll);

            avml_impl::store3f(elements, d);

            #else
            float length = (x * x + y * y + z * z);
            elements[0] = x / length;
            elements[1] = y / length;
            elements[2] = z / length;

            #endif
        }

        AVML_FINL Unit_vector3R(Unit_vector2R<float> v):
            elements{v[0], v[1], 0.0f} {}

        template<class R>
        explicit AVML_FINL Unit_vector3R(Unit_vector3R<R> v):
            elements{
                static_cast<float>(v[0]),
                static_cast<float>(v[1]),
                static_cast<float>(v[2])
            } {}

        explicit AVML_FINL Unit_vector3R(Unit_vector3R<double> v):
            elements{} {

            #if defined(AVML_AVX)
            __m256d c = avml_impl::load3d(v.data());

            __m128 d = _mm256_cvtpd_ps(c);
            avml_impl::store3f(elements, d);

            #elif defined(AVML_SSE2)
            auto c = avml_impl::load3d(v.data());

            __m128 lo = _mm_cvtpd_ps(c[0]);
            __m128 hi = _mm_cvtpd_ps(c[1]);

            __m128 d = _mm_movelh_ps(lo, hi);
            avml_impl::store3f(elements, d);

            #else
            elements[0] = static_cast<double>(v[0]);
            elements[1] = static_cast<double>(v[1]);
            elements[2] = static_cast<double>(v[2]);
            #endif
        }

        Unit_vector3R() = default;
        Unit_vector3R(const Unit_vector3R&) = default;
        Unit_vector3R(Unit_vector3R&&) = default;
        ~Unit_vector3R() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Unit_vector3R& operator=(const Unit_vector3R&) = default;
        Unit_vector3R& operator=(Unit_vector3R&&) = default;

        //=================================================
        // Unary arithmetic operators
        //=================================================

        AVML_FINL Unit_vector3R operator+() const {
            return *this;
        }

        AVML_FINL Unit_vector3R operator-() const {
            Unit_vector3R ret;

            #ifdef AVML_SSE
            __m128 r_xy00 = avml_impl::load3f(elements);
            __m128 diff = _mm_sub_ps(_mm_setzero_ps(), r_xy00);
            avml_impl::store3f(ret.elements, diff);
            #else
            ret.elements[0] = -elements[0];
            ret.elements[1] = -elements[1];
            ret.elements[2] = -elements[2];
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
        explicit operator Unit_vector3R<U>() const {
            Unit_vector3R<U> ret;
            ret.elements[0] = static_cast<U>(elements[0]);
            ret.elements[1] = static_cast<U>(elements[1]);
            ret.elements[2] = static_cast<U>(elements[2]);
            return ret;
        }

        explicit operator Unit_vector3R<double>() const {
            Unit_vector3R<double> ret;
            double* p = const_cast<double*>(ret.data());

            #if defined(AVML_AVX)
            __m128 t = avml_impl::load3f(elements);
            __m256d d = _mm256_cvtps_pd(t);

            avml_impl::store3d(p, d);
            #elif defined(AVML_SSE2)
            __m128 d = avml_impl::load3f(elements);
            __m128d d0 = _mm_cvtps_pd(d);
            __m128 d1 = _mm_movehl_ps(d, d);
            __m128d d2 = _mm_cvtss_sd(_mm_setzero_pd(), d1);
            avml_impl::store3d(p, d0, d2);
            #else
            p[0] = static_cast<double>(elements[0]);
            p[1] = static_cast<double>(elements[1]);
            p[2] = static_cast<double>(elements[2]);
            #endif

            return ret;
        }

    private:

        //=================================================
        // Instance members
        //=================================================

        float elements[width] = {1.0f, 0.0f, 0.0f};

    };

    //=====================================================
    // Vectorized math
    //=====================================================

    AVML_FINL Unit_vector3R<float> abs(Unit_vector3R<float> v) {
        Unit_vector3R<float> ret;
        #if defined(AVML_SSE)
        __m128 vec_data = avml_impl::load3f(v.data());
        vec_data = _mm_and_ps(avml_impl::sign_bit_mask, vec_data);

        avml_impl::store3f(const_cast<float*>(ret.data()), vec_data);
        return ret;

        #else
        float* data = const_cast<float*>(ret.data());
        data[0] = -v[0];
        data[1] = -v[1];
        data[2] = -v[2];
        return v;

        #endif
    }

}

#endif
