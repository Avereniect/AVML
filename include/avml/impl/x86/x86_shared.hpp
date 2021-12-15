//
// Created by avereniect on 12/13/21.
//

#ifndef AVML_X86_SHARED_HPP
#define AVML_X86_SHARED_HPP

namespace avml_impl {

    static const std::uint32_t sign_bit_mask_data[4] {
        0x7FFFFFFF,
        0x7FFFFFFF,
        0x7FFFFFFF,
        0x7FFFFFFF
    };

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

#elif defined(AVML_AVX2)
    __m128i mask0111{
        -1,
        4294967295
    };

    __m128 load2f(const float* data) {
        __m128 ret;
        ret = _mm_castpd_ps(_mm_load_sd(reinterpret_cast<const double*>(data)));
        return ret;
    }

    __m128 load3f(const float* data) {
        __m128i mask = _mm_load_si128(reinterpret_bits<const __m128i*>(mask0111));
        return _mm_maskload_ps(data, mask);
    }

    __m128 load4f(const float* data) {
        return _mm_load_ps(data);
    }

    void store2f(float* p, __m128 reg) {
        _mm_store_sd(reinterpret_cast<double*>(p), _mm_castps_pd(reg));
    }

    void store3f(float* p, __m128 reg) {
        _mm_maskstore_ps(p, mask0111, reg);
    }

    void store4f(float* p, __m128 reg) {
        _mm_store_ps(p, reg);
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

#endif

}

#endif //AVML_X86_SHARED_HPP
