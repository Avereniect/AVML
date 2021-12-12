#ifndef AVML_MATH_HPP
#define AVML_MATH_HPP

#include <cstdint>
#include <limits>

#include "impl/Capabilities.hpp"

namespace avml {

    float fmadd(float m, float x, float b);
    float fmnadd(float m, float x, float b);

    float fmsub(float m, float x, float b);
    float fmnsub(float m, float x, float b);

    float fract(float x);

    float clamp(float x, float min, float max);

    float average(float x, float y);

    ///
    /// \param x First float to compare
    /// \param y Second float to compare
    /// \param margin Tolerance in number of representable values between x and y
    /// \return True if number of representable values between x and y is less than margin
    bool compare_equal(float x, float y, std::uint32_t margin);


    double fmadd(double m, double x, double b);
    double fmnadd(double m, double x, double b);

    double fmsub(double m, double x, double b);
    double fmsub(double m, double x, double b);

    double fract(double x);

    double clamp(double x, double lo, double hi);

    double average(double x, double y);

    bool compare_equal(double x, double y, std::uint64_t margin);

}

#include "impl/Math.hpp"

#endif //AVML_MATH_HPP
