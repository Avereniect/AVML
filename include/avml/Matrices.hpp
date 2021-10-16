#ifndef AVML_MATRICES_HPP
#define AVML_MATRICES_HPP

#include "Vectors.hpp"

namespace avml {

    template<class T>
    class Matrix2x2;

    template<class T>
    class Matrix3x3;

    template<class T>
    class Matrix4x4;

    //=================================
    // Type aliases
    //=================================

    using mat2x2f = Matrix2x2<float>;
    using mat3x3f = Matrix3x3<float>;
    using mat4x4f = Matrix4x4<float>;


    using mat2x2d = Matrix2x2<double>;
    using mat3x3d = Matrix3x3<double>;
    using mat4x4d = Matrix4x4<double>;

}

#include "impl/IMPL_matrices.hpp"

#endif //AVML_MATRICES_HPP
