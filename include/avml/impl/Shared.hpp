#ifndef AVML_IMPL_SHARED_HPP
#define AVML_IMPL_SHARED_HPP

#include "Capabilities.hpp"

#include <type_traits>

namespace avml_impl {

    template<class T, class U>
    T reinterpret_bits(const U& u) {
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
    constexpr inline bool is_pow2(const T v) {
        return v && !(v & (v - 1));
    }

    template<class T, unsigned N>
    [[nodiscard]]
    constexpr std::size_t vector_alignment() {
        return is_pow2(N) ? alignof(T) * N : alignof(T);
    }

}

namespace avml_impl {

    static const __m128i sign_bit_mask {
        0x7FFFFFFF7FFFFFFF,
        0x7FFFFFFF7FFFFFFF
    };


#if defined(AVML_AVX512VL)

    __m128 load2f(const float* data) {
        return _mm_maskz_load_ps(0x03, data);
    }

    __m128 load3f(const float* data) {
        return _mm_maskz_load_ps(0x07, data);
    }

    __m128 load4f(const float* data) {
        return _mm_load_ps(data);
    }

    void store2f(float* p, __m128 reg) {
        _mm_mask_store_ps(p, 0x03, reg);
    }

    void store3f(float* p, __m128 reg) {
        _mm_mask_store_ps(p, 0x07, reg);
    }

    void store4f(float* p, __m128 reg) {
        _mm_store_ps(p, reg);
    }


    __m128d load2d(const double* ptr) {
        return _mm_load_pd(ptr);
    }

    __m256 load3d(const double* ptr) {
        return _mm256_maskload_pd(ptr, dmask0111);
    }

    __m256 load4(const double* ptr) {
        return _mm256_load_pd(ptr);
    }

    void store2d(double* ptr, __m128d d) {
        _mm_store_pd(ptr, d);
    }

    void store3d(double* ptr, __m256d d) {
        _mm256_maskstore_pd(ptr, dmask0111, d);
    }

    void store4d(double* ptr, __m256d d) {
        _mm256_store_pd(ptr, d);
    }

#elif defined(AVML_AVX)

    __m128i fmask0111{
        -1,
        4294967295
    };

    __m256i dmask0111{
        -1,
        -1,
        -1,
        0
    };

    __m128 load2f(const float* data) {
        __m128 ret;
        ret = _mm_castpd_ps(_mm_load_sd(reinterpret_cast<const double*>(data)));
        return ret;
    }

    __m128 load3f(const float* data) {
        return _mm_maskload_ps(data, fmask0111);
    }

    __m128 load4f(const float* data) {
        return _mm_load_ps(data);
    }

    void store2f(float* p, __m128 reg) {
        _mm_store_sd(reinterpret_cast<double*>(p), _mm_castps_pd(reg));
    }

    void store3f(float* p, __m128 reg) {
        _mm_maskstore_ps(p, fmask0111, reg);
    }

    void store4f(float* p, __m128 reg) {
        _mm_store_ps(p, reg);
    }


    __m128d load2d(const double* ptr) {
        return _mm_load_pd(ptr);
    }

    __m256d load3d(const double* ptr) {
        return _mm256_maskload_pd(ptr, dmask0111);
    }

    __m256d load4d(const double* ptr) {
        return _mm256_load_pd(ptr);
    }

    void store2d(double* ptr, __m128d d) {
        _mm_store_pd(ptr, d);
    }

    void store3d(double* ptr, __m256d d) {
        _mm256_maskstore_pd(ptr, dmask0111, d);
    }

    void store4d(double* ptr, __m256d d) {
        _mm256_store_pd(ptr, d);
    }

#else

    __m128 load2f(const float* data) {
        __m128 ret;
        ret = _mm_castpd_ps(_mm_load_sd(reinterpret_cast<const double*>(data)));
        return ret;
    }

    __m128 load3f(const float* data) {
        __m128 lo = load2f(data);
        __m128 hi = _mm_load_ss(data + 0x2);
        __m128 ret = _mm_movelh_ps(lo, hi);
        return ret;
    }

    __m128 load4f(const float* data) {
        return _mm_load_ps(data);
    }

    void store2f(float* p, __m128 reg) {
        _mm_store_sd(reinterpret_cast<double*>(p), _mm_castps_pd(reg));
    }

    void store3f(float* p, __m128 reg) {
        __m128 lo = reg;
        __m128 hi = _mm_movehl_ps(reg, reg);

        _mm_store_sd(reinterpret_cast<double*>(p), _mm_castps_pd(lo));
        _mm_store_ss(p + 0x02, hi);
    }

    void store4f(float* p, __m128 reg) {
        _mm_store_ps(p, reg);
    }


    __m128d load2d(const double* ptr) {
        return _mm_load_pd(ptr);
    }

    std::array<__m128d, 2> load3d(const double* ptr) {
        return {_mm_load_pd(ptr), _mm_load_sd(ptr + 0x2)};
    }

    std::array<__m128d, 2> load4d(const double* ptr) {
        return {_mm_load_pd(ptr), _mm_load_pd(ptr + 0x2)};
    }

    void store2d(double* ptr, __m128d d) {
        _mm_store_pd(ptr, d);
    }

    void store3d(double* ptr, __m128d d0, __m128d d1) {
        _mm_store_pd(ptr + 0x0, d0);
        _mm_store_sd(ptr + 0x2, d1);
    }

    void store4d(double* ptr, __m128d d0, __m128 d1) {
        _mm_store_pd(ptr + 0x0, d0);
        _mm_store_pd(ptr + 0x2, d1);
    }

#endif

}

#endif
