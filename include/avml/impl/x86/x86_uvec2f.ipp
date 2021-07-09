#ifndef AVML_X86_UVEC2F_IPP
#define AVML_X86_UVEC2F_IPP

namespace avml {

    template<>
    class alignas(sizeof(float) * 2) Vector<float, 2> {
    public:

        using scalar = float;

        static constexpr unsigned width = 2;

        //=================================================
        // Creation functions
        //=================================================

        AVML_FINL static Vector read(const float* p) {
            return Vector{p[0], p[1]};
        }

        AVML_FINL static Vector read_aligned(const float* p) {
            return Vector{p[0], p[1]};
        }

        //=================================================
        // -ctors
        //=================================================

        AVML_FINL Vector(float v):
            elements{v, v} {}

        AVML_FINL Vector(float x, float y):
            elements{x, y} {}

        AVML_FINL Vector(uvec2f v):
            elements{v[0], v[1]} {}

        Vector() = default;
        Vector(const Vector&) = default;
        Vector(Vector&&) = default;
        ~Vector() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Vector& operator=(const Vector&) = default;
        Vector& operator=(Vector&&) = default;

        //=================================================
        // Arithmetic assignment operators
        //=================================================

        AVML_FINL Vector& operator+=(const Vector& rhs) {
            __m128 a = aligned_load(elements);
            __m128 b = aligned_load(rhs.elements);

            aligned_store(elements, _mm_add_ps(a, b));
            return *this;
        }

        AVML_FINL Vector& operator-=(const Vector& rhs) {
            __m128 a = aligned_load(elements);
            __m128 b = aligned_load(rhs.elements);

            aligned_store(elements, _mm_sub_ps(a, b));
            return *this;
        }

        AVML_FINL Vector& operator*=(const scalar rhs) {
            __m128 a = aligned_load(elements);
            __m128 b = _mm_set1_ps(rhs);

            aligned_store(elements, _mm_mul_ps(a, b));
            return *this;
        }

        AVML_FINL Vector& operator/=(const scalar rhs) {
            __m128 a = aligned_load(elements);
            __m128 b = _mm_set1_ps(rhs);

            aligned_store(elements, _mm_div_ps(a, b));
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

        float elements[width] = {0.0f, 0.0f};

        //=================================================
        // Helper functions
        //=================================================

        AVML_FINL __m128 aligned_load(const float* p) {
            #if defined(AVML_AVX512F)
            return _mm_maskz_load_ps(0x3, p);
            #elif defined(AVML_AVX)
            alignas(16) static constexpr std::int32_t mask_data[4]{0, 0, -1, -1};
            __m128i mask = _mm_load_si128((__m128i*)mask_data);
            return _mm_maskload_ps(p, mask);
            #elif defined(AVML_SSE2)
            return _mm_castpd_ps(_mm_load_sd((double*)p));
            #endif
        }

        AVML_FINL void aligned_store(float* p, __m128 data) {
            #if defined(AVML_AVX512F)
            _mm_mask_store_ps(p, 0x3, data);
            #elif defined(AVML_AVX)
            alignas(16) static constexpr std::int32_t mask_data[4]{0, 0, -1, -1};
            __m128i mask = _mm_load_si128((__m128i*)mask_data);
            _mm_maskstore_ps(p, mask, data);
            #elif defined(AVML_SSE2)
            _mm_store_sd((double*)p, _mm_castps_pd(data));
            #endif
        }

    };

    //=====================================================
    // Vectorized math
    //=====================================================

    AVML_FINL uvec2f abs(uvec2f v) {
        alignas(alignof(uvec2f)) float data[uvec2f::width];
        data[0] = std::abs(v[0]);
        data[1] = std::abs(v[1]);
        return uvec2f::read_aligned(data);
    }

}

#endif //AVML_X86_UVEC2F_IPP
