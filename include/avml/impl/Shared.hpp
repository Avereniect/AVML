#ifndef AVML_SHARED_HPP
#define AVML_SHARED_HPP

#include "Capabilities.hpp"

#include <type_traits>

namespace avml_impl {

    template<class T, class U>
    AVML_FINL T reinterpret_bits(const U& u) {
        static_assert(sizeof(T) == sizeof(U), "Types should be of same size.");
        static_assert(std::is_trivial<T>::value, "T should be trivial");
        static_assert(std::is_trivial<U>::value, "U should be trivial");

        T ret;

        char* src = reinterpret_cast<char*>(&u);
        char* dest = reinterpret_cast<char*>(&ret);

        for (int i = 0; i < sizeof(U); ++i) {
            dest[i] = src[i];
        }

        return ret;
    }

    template<class T>
    [[nodiscard]]
    AVML_FINL constexpr bool is_pow2(const T v) {
        return v && !(v & (v - 1));
    }

    template<class T, unsigned N>
    [[nodiscard]]
    AVML_FINL constexpr std::size_t vector_alignment() {
        return is_pow2(N) ? alignof(T) * N : alignof(T);
    }

}

namespace avml_impl {

    static const __m128 sign_bit_mask = _mm_castsi128_ps(__m128i{
        0x7FFFFFFF7FFFFFFF,
        0x7FFFFFFF7FFFFFFF
    });

#if defined(AVML_AVX512VL)

    //=====================================================
    // Floats
    //=====================================================

    AVML_FINL __m128 load2f(const float* data) {
        return _mm_maskz_load_ps(0x03, data);
    }

    AVML_FINL __m128 load3f(const float* data) {
        return _mm_maskz_loadu_ps(0x07, data);
    }

    AVML_FINL __m128 load4f(const float* data) {
        return _mm_load_ps(data);
    }

    AVML_FINL void store2f(float* p, __m128 reg) {
        _mm_mask_storeu_ps(p, 0x03, reg);
    }

    AVML_FINL void store3f(float* p, __m128 reg) {
        _mm_mask_storeu_ps(p, 0x07, reg);
    }

    AVML_FINL void store4f(float* p, __m128 reg) {
        _mm_store_ps(p, reg);
    }

    //=====================================================
    // Double
    //=====================================================

    AVML_FINL __m128d load2d(const double* ptr) {
        return _mm_load_pd(ptr);
    }

    AVML_FINL __m256d load3d(const double* ptr) {
        return _mm256_maskz_load_pd(0x7, ptr);
    }

    AVML_FINL __m256d load4d(const double* ptr) {
        return _mm256_load_pd(ptr);
    }

    AVML_FINL void store2d(double* ptr, __m128d d) {
        _mm_store_pd(ptr, d);
    }

    AVML_FINL void store3d(double* ptr, __m256d d) {
        _mm256_mask_store_pd(ptr, 0x7, d);
    }

    AVML_FINL void store4d(double* ptr, __m256d d) {
        _mm256_store_pd(ptr, d);
    }

    //=====================================================
    // Integers
    //=====================================================

    AVML_FINL  __m128i load64b(const void* ptr) {
        return _mm_loadu_si64(ptr);
    }

    AVML_FINL __m128i load96b(const void* ptr) {
        return _mm_maskz_load_epi32(0x7, ptr);
    }

    AVML_FINL __m128i load128b(const void* ptr) {
        return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));
    }

    AVML_FINL void store64b(void* ptr, __m128i r) {
        _mm_storeu_si64(ptr, r);
    }

    AVML_FINL void store96b(void* ptr, __m128i r) {
        _mm_mask_store_epi32(ptr, 0x7, r);
    }

    AVML_FINL void store128b(void* ptr, __m128i r) {
        _mm_store_si128(reinterpret_cast<__m128i*>(ptr), r);
    }

#elif defined(AVML_AVX2)

    static const __m128i fmask0111{
        -1,
        4294967295
    };

    static const __m256i dmask0111{
        -1,
        -1,
        -1,
        0
    };

    //=====================================================
    // Floats
    //=====================================================

    AVML_FINL __m128 load2f(const float* data) {
        __m128 ret;
        ret = _mm_castpd_ps(_mm_load_sd(reinterpret_cast<const double*>(data)));
        return ret;
    }

    AVML_FINL __m128 load3f(const float* data) {
        return _mm_maskload_ps(data, fmask0111);
    }

    AVML_FINL __m128 load4f(const float* data) {
        return _mm_load_ps(data);
    }

    AVML_FINL void store2f(float* p, __m128 reg) {
        _mm_store_sd(reinterpret_cast<double*>(p), _mm_castps_pd(reg));
    }

    AVML_FINL void store3f(float* p, __m128 reg) {
        _mm_maskstore_ps(p, fmask0111, reg);
    }

    AVML_FINL void store4f(float* p, __m128 reg) {
        _mm_store_ps(p, reg);
    }

    //=====================================================
    // Doubles
    //=====================================================

    AVML_FINL __m128d load2d(const double* ptr) {
        return _mm_load_pd(ptr);
    }

    AVML_FINL __m256d load3d(const double* ptr) {
        return _mm256_maskload_pd(ptr, dmask0111);
    }

    AVML_FINL __m256d load4d(const double* ptr) {
        return _mm256_load_pd(ptr);
    }

    AVML_FINL void store2d(double* ptr, __m128d d) {
        _mm_store_pd(ptr, d);
    }

    AVML_FINL void store3d(double* ptr, __m256d d) {
        _mm256_maskstore_pd(ptr, dmask0111, d);
    }

    AVML_FINL void store4d(double* ptr, __m256d d) {
        _mm256_store_pd(ptr, d);
    }

    //=====================================================
    // Integers
    //=====================================================

    AVML_FINL __m128i load64b(const void* ptr) {
        return _mm_loadu_si64(ptr);
    }

    AVML_FINL __m128i load96b(const void* ptr) {
        return _mm_maskload_epi32(reinterpret_cast<const int*>(ptr), fmask0111);
    }

    AVML_FINL __m128i load128b(const void* ptr) {
        return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));
    }

    AVML_FINL void store64b(void* ptr, __m128i r) {
        _mm_storeu_si64(ptr, r);
    }

    AVML_FINL void store96b(void* ptr, __m128i r) {
        _mm_maskstore_epi32(reinterpret_cast<int*>(ptr), fmask0111, r);
    }

    AVML_FINL void store128b(void* ptr, __m128i r) {
        _mm_store_si128(reinterpret_cast<__m128i*>(ptr), r);
    }

#elif defined(AVML_AVX)

    static const __m128i fmask0111{
        -1,
        4294967295
    };

    static const __m256i dmask0111{
        -1,
        -1,
        -1,
        0
    };

    //=====================================================
    // Floats
    //=====================================================

    AVML_FINL __m128 load2f(const float* data) {
        __m128 ret;
        ret = _mm_castpd_ps(_mm_load_sd(reinterpret_cast<const double*>(data)));
        return ret;
    }

    AVML_FINL __m128 load3f(const float* data) {
        return _mm_maskload_ps(data, fmask0111);
    }

    AVML_FINL __m128 load4f(const float* data) {
        return _mm_load_ps(data);
    }

    AVML_FINL void store2f(float* p, __m128 reg) {
        _mm_store_sd(reinterpret_cast<double*>(p), _mm_castps_pd(reg));
    }

    AVML_FINL void store3f(float* p, __m128 reg) {
        _mm_maskstore_ps(p, fmask0111, reg);
    }

    AVML_FINL void store4f(float* p, __m128 reg) {
        _mm_store_ps(p, reg);
    }

    //=====================================================
    // Doubles
    //=====================================================

    AVML_FINL __m128d load2d(const double* ptr) {
        return _mm_load_pd(ptr);
    }

    AVML_FINL __m256d load3d(const double* ptr) {
        return _mm256_maskload_pd(ptr, dmask0111);
    }

    AVML_FINL __m256d load4d(const double* ptr) {
        return _mm256_load_pd(ptr);
    }

    AVML_FINL void store2d(double* ptr, __m128d d) {
        _mm_store_pd(ptr, d);
    }

    AVML_FINL void store3d(double* ptr, __m256d d) {
        _mm256_maskstore_pd(ptr, dmask0111, d);
    }

    AVML_FINL void store4d(double* ptr, __m256d d) {
        _mm256_store_pd(ptr, d);
    }

    //=====================================================
    // Integers
    //=====================================================

    AVML_FINL __m128i load64b(const void* ptr) {
        return _mm_loadu_si64(ptr);
    }

    AVML_FINL __m128i load96b(const void* ptr) {
        __m128i ret;
        ret[0] = reinterpret_cast<const std::int64_t*>(ptr)[0];
        ret[1] = reinterpret_cast<const std::int32_t*>(ptr)[2];
        return ret;
    }

    AVML_FINL __m128i load128b(const void* ptr) {
        return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));
    }

    AVML_FINL void store64b(void* ptr, __m128i r) {
        _mm_storeu_si64(ptr, r);
    }

    AVML_FINL void store96b(void* ptr, __m128i r) {
        reinterpret_cast<std::uint64_t*>(ptr)[0] = r[0];
        reinterpret_cast<std::uint32_t*>(ptr)[2] = r[1];
    }

    AVML_FINL void store128b(void* ptr, __m128i r) {
        _mm_store_si128(reinterpret_cast<__m128i*>(ptr), r);
    }

#elif defined(AVML_SSE2)

    //=====================================================
    // Floats
    //=====================================================

    AVML_FINL __m128 load2f(const float* data) {
        __m128 ret;
        ret = _mm_castpd_ps(_mm_load_sd(reinterpret_cast<const double*>(data)));
        return ret;
    }

    AVML_FINL __m128 load3f(const float* data) {
        __m128 lo = load2f(data);
        __m128 hi = _mm_load_ss(data + 0x2);
        __m128 ret = _mm_movelh_ps(lo, hi);
        return ret;
    }

    AVML_FINL __m128 load4f(const float* data) {
        return _mm_load_ps(data);
    }

    AVML_FINL void store2f(float* p, __m128 reg) {
        _mm_store_sd(reinterpret_cast<double*>(p), _mm_castps_pd(reg));
    }

    AVML_FINL void store3f(float* p, __m128 reg) {
        __m128 lo = reg;
        __m128 hi = _mm_movehl_ps(reg, reg);

        _mm_store_sd(reinterpret_cast<double*>(p), _mm_castps_pd(lo));
        _mm_store_ss(p + 0x02, hi);
    }

    AVML_FINL void store4f(float* p, __m128 reg) {
        _mm_store_ps(p, reg);
    }

    //=====================================================
    // Doubles
    //=====================================================

    AVML_FINL __m128d load2d(const double* ptr) {
        return _mm_load_pd(ptr);
    }

    AVML_FINL std::array<__m128d, 2> load3d(const double* ptr) {
        return {_mm_load_pd(ptr), _mm_load_sd(ptr + 0x2)};
    }

    AVML_FINL std::array<__m128d, 2> load4d(const double* ptr) {
        return {_mm_load_pd(ptr), _mm_load_pd(ptr + 0x2)};
    }

    AVML_FINL void store2d(double* ptr, __m128d d) {
        _mm_store_pd(ptr, d);
    }

    AVML_FINL void store3d(double* ptr, __m128d d0, __m128d d1) {
        _mm_store_pd(ptr + 0x0, d0);
        _mm_store_sd(ptr + 0x2, d1);
    }

    AVML_FINL void store4d(double* ptr, __m128d d0, __m128d d1) {
        _mm_store_pd(ptr + 0x0, d0);
        _mm_store_pd(ptr + 0x2, d1);
    }

    //=====================================================
    // Integers
    //=====================================================

    AVML_FINL __m128i load64b(const void* ptr) {
        return _mm_loadu_si64(ptr);
    }

    AVML_FINL __m128i load96b(const void* ptr) {
        __m128i ret;
        ret[0] = reinterpret_cast<const std::int64_t*>(ptr)[0];
        ret[1] = reinterpret_cast<const std::int32_t*>(ptr)[2];
        return ret;
    }

    AVML_FINL __m128i load128b(const void* ptr) {
        return _mm_load_si128(reinterpret_cast<const __m128i*>(ptr));
    }

    AVML_FINL void store64b(void* ptr, __m128i r) {
        _mm_storeu_si64(ptr, r);
    }

    AVML_FINL void store96b(void* ptr, __m128i r) {
        reinterpret_cast<std::uint64_t*>(ptr)[0] = r[0];
        reinterpret_cast<std::uint32_t*>(ptr)[2] = r[1];
    }

    AVML_FINL void store128b(void* ptr, __m128i r) {
        _mm_store_si128(reinterpret_cast<__m128i*>(ptr), r);
    }

#endif

}

#endif
