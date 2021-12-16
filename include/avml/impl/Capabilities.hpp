#ifndef AVML_IMPL_CAPABILITIES_HPP
#define AVML_IMPL_CAPABILITIES_HPP

#include <climits>
#include <limits>
#include <cstdint>

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
    #define AVML_X86
#endif


#ifdef AVML_X86
#endif

//=========================================================
// ARM Instruction sets
//=========================================================

#ifdef AVML_SVE2
    #define AVML_SVE
#endif

#ifdef AVML_SVE
    #define AVML_ARM
#endif

#ifdef AVML_NEON
    #define AVML_ARM
#endif

#ifdef AVML_ARM
#endif

//=========================================================
// Error checking
//=========================================================

#if defined(AVML_ARM) && defined(AVML_X86)
    static_assert(false, "Extensions for multiple ISAs specified.");
#endif

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

    #ifdef AVML_FORCE_OPTIMIZATIONS
        //This level of optimization appears to be enough.
        #define AVML_FINL  __attribute__ ((__always_inline__, optimize("O1"))) inline
    #else
        #define AVML_FINL __attribute__((__always_inline__)) inline
    #endif

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



#endif //AVML_CAPABILITIES_HPP
