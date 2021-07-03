#ifndef AVML_MATH_HPP
#define AVML_MATH_HPP

namespace {

    float fmadd(float m, float x, float b);
    float fmnadd(float m, float x, float b);

    float fmsub(float m, float x, float b);
    float fmnsub(float m, float x, float b);

    float fract(float x);

    float clamp(float x, float min, float max);

    float average(float x, float y);


    double fmadd(double m, double x, double b);
    double fmnadd(double m, double x, double b);

    double fmsub(double m, double x, double b);
    double fmsub(double m, double x, double b);

    double fract(double x);

    double clamp(double x, double lo, double hi);

    double average(double x, double y);

}

#include "impl/IMPL_math.hpp"

#endif //AVML_MATH_HPP
