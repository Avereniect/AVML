#include <cmath>
#include "../IMPL_shared.hpp"

namespace avml {

    AVML_FINL float fmadd(float m, float x, float b) {
        return std::fma(m, x, b);
    }

    AVML_FINL float fmnadd(float m, float x, float b) {
        return std::fma(-m, x, b);
    }

    AVML_FINL float fmsub(float m, float x, float b) {
        return std::fma(m, x, -b);
    }

    AVML_FINL float fmnsub(float m, float x, float b) {
        return std::fma(-m, x, -b);
    }

    AVML_FINL float fract(float x) {
        return x - std::floor(x);
    }

    AVML_FINL float clamp(float x, float min, float max) {
        return std::min(std::max(x, min), max);
    }

    AVML_FINL float average(float x, float y) {
        return (x -  (x * 0.5f)) + (y * 0.5f);
    }

    /*
    //TODO: Complete implementation.
    bool compare_equal(float x, float y, std::uint32_t margin) {
        std::uint32_t a = avml_impl::reinterpret_bits<std::uint32_t>(x);
        std::uint32_t b = avml_impl::reinterpret_bits<std::uint32_t>(y);

        std::uint32_t sign0 = a & 0x80000000;
        std::uint32_t sign1 = b & 0x80000000;

        std::uint32_t mant0 = (a & 0x007FFFFF);
        std::uint32_t mant1 = (b & 0x007FFFFF);

        std::uint32_t exp0 = (a & 0x07800000);
        std::uint32_t exp1 = (b & 0x07800000);

        // Test if at least one float has an exponent of 255
        if ((exp0 == 0x07800000) || (exp1 == 0x07800000)) {
            //TODO: Handle Nans, infinities
        }

        if (sign0 == sign1) {
            return (a - b) <= margin;
        } else {
            std::uint32_t i;
            //TODO: Handle case where both numbers are sufficiently close to zero
            return false;
        }

    }
    */

}
