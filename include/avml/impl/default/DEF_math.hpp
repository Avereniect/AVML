#ifndef AVML_IMPL_MATH_HPP
#define AVML_IMPL_MATH_HPP

#include <cmath>

namespace avml {

    float fmadd(float m, float x, float b) {
        return std::fma(m, x, b);
    }

    float fmnadd(float m, float x, float b) {
        return std::fma(-m, x, b);
    }

    float fmsub(float m, float x, float b) {
        return std::fma(m, x, -b);
    }

    float fmnsub(float m, float x, float b) {
        return std::fma(-m, x, b);
    }

    float fract(float x) {
        return x - std::floor(x);
    }

    float clamp(float x, float min, float max) {
        return std::min(std::max(x, min), max);
    }

    float average(float x, float y) {
        return (x -  (x * 0.5f)) + (y * 0.5f);
    }

}

#endif //AVML_IMPL_MATH_HPP
