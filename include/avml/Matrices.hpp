#ifndef AVML_MATRICES_HPP
#define AVML_MATRICES_HPP

#include "Vectors.hpp"

namespace avml {

    template<class T>
    class Matrix2x2R;

    template<class T>
    class Matrix3x3R;

    template<class T>
    class Matrix4x4R;


    template<class T>
    class Matrix2x2I;

    template<class T>
    class Matrix3x3I;

    template<class T>
    class Matrix4x4I;

    //=================================
    // Type aliases
    //=================================

    using mat2x2f = Matrix2x2R<float>;
    using mat3x3f = Matrix3x3R<float>;
    using mat4x4f = Matrix4x4R<float>;

    using mat2x2d = Matrix2x2R<double>;
    using mat3x3d = Matrix3x3R<double>;
    using mat4x4d = Matrix4x4R<double>;

    using mat2x2i = Matrix2x2I<std::int32_t>;
    using mat3x3i = Matrix3x3I<std::int32_t>;
    using mat4x4i = Matrix4x4I<std::int32_t>;

    using mat2x2u = Matrix2x2I<std::uint32_t>;
    using mat3x3u = Matrix3x3I<std::uint32_t>;
    using mat4x4u = Matrix4x4I<std::uint32_t>;

}

#include "impl/IMPL_matrices.hpp"

#endif //AVML_MATRICES_HPP
