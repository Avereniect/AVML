#ifndef AVML_IMPL_CAPABILITIES_HPP
#define AVML_IMPL_CAPABILITIES_HPP

#include <climits>
#include <limits>

//=========================================================
// Primitive sizes
//=========================================================

static_assert(CHAR_BIT == 8, "Bytes required to be 8 bits.");
static_assert(std::numeric_limits<float>::is_iec559, "IEEE-754 floats required");
static_assert(sizeof(float) == 4, "Size of floats should be 32 bits");
static_assert(sizeof(double) == 8, "Size of doubles should be 64 bits");

//=========================================================
// x86 Instruction sets
//=========================================================

#ifdef AVML_AVX512BW
    #define AVML_AVX512F
#endif


#ifdef AVML_AVX512DQ
    #define AVML_AVX512F
#endif


#ifdef AVML_AVX512VL
    #define AVML_AVX512F
#endif


#ifdef AVML_AVX512_BITALG
    #define AVML_AVX512F
#endif


#ifdef AVML_AVX512VPOPCNTDQ
    #define AVML_AVX512F
#endif


#ifdef AVML_AVX512F
    #define AVML_AVX2
#endif


#ifdef AVML_AVX2
    #define AVML_AVX
#endif


#ifdef AVML_AVX
    #define AVML_SSE42
#endif


#ifdef AVML_SSE42
    #define AVML_SSE41
#endif


#ifdef AVML_SSE41
    #define AVML_SSSE3
#endif


#ifdef AVML_SSSE3
    #define AVML_SSE3
#endif


#ifdef AVML_SSE3
    #define AVML_SSE2
#endif


#ifdef AVML_SSE2
    #define AVML_SSE
#endif


#ifdef AVML_SSE
    #define AVML_x86
#endif


#ifdef AVML_x86
#endif

//=========================================================
// ARM Instruction sets
//=========================================================

//TODO: Define macros for ARM instruction sets

//=========================================================
// Compiler-specific
//=========================================================

#if defined(__clang__)
    #define AVML_CLANG
    #define AVML_FINL __attribute__((__always_inline__)) inline
    #define AVML_UNROLL(x) _Pragma("#pragma unroll x")

    #include <x86intrin.h>
    #include <immintrin.h>

#elif defined(__GNUC__)
    #define AVML_GCC
    #define AVML_FINL __attribute__((__always_inline__)) inline
    #define AVML_UNROLL(x) _Pragma("#pragma GCC unroll x")

    #include <x86intrin.h>
    #include <immintrin.h>
#elif defined(_MSC_VER)
    #define AVML_MSVC
    #define AVML_FINL __forceinline
    #define AVML_UNROLL(x) _Prgama("loopivdep)")

    #include "intrin.h"

#elif
    #define AVML_FINL inline
    static_assert(false, "Compiler not supported");
#endif



#endif //AVML_IMPL_CAPABILITIES_HPP
