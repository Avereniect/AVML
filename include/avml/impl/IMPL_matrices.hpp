#ifndef AVML_IMPL_MATRICES_HPP
#define AVML_IMPL_MATRICES_HPP

namespace avml {

    template<class T, unsigned N>
    Matrix<T, N, N> pow(Matrix<T, N, N> mat, std::uint32_t power) {
        static const Matrix<T, N, N> identity{static_cast<T>(1)};
        Matrix<T, N, N> matrices[32] = {identity, mat};

        if (power == 0) {
            return identity;
        }

        std::uint32_t p = 1;
        while (p < power) {
            matrices[p] = matrices[p - 1] * matrices[p - 1];
            p = p << 1;
        }

        auto ret = mat;
        std::uint32_t mask = 0x2;
        unsigned i = 2;
        while (power) {
            if (power & mask) {
                ret *= matrices[i];
            }

            power &= ~mask;
            mask <<= 1;
            i += 1;
        }

        return mat;
    }

}

#ifdef SSE

#else
    #include "default/DEF_matrix2x2f.hpp"
    #include "default/DEF_matrix3x3f.hpp"
    #include "default/DEF_matrix4x4f.hpp"
#endif

#endif //AVML_IMPL_MATRICES_HPP
