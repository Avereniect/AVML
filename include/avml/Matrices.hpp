#ifndef AVML_MATRICES_HPP
#define AVML_MATRICES_HPP

#include "Vectors.hpp"

namespace avml {

    ///
    /// \tparam T A floating-point or integral type
    /// \tparam N Number of rows: [2, 4]
    /// \tparam M Number of columns: [2, 4]
    template<class T, unsigned N, unsigned M>
    class Matrix;

    //=================================
    // Type aliases
    //=================================

    using mat2x2f = Matrix<float, 2, 2>;
    using mat2x3f = Matrix<float, 2, 3>;
    using mat2x4f = Matrix<float, 2, 4>;

    using mat3x2f = Matrix<float, 3, 2>;
    using mat3x3f = Matrix<float, 3, 3>;
    using mat3x4f = Matrix<float, 3, 4>;

    using mat4x2f = Matrix<float, 4, 2>;
    using mat4x3f = Matrix<float, 4, 3>;
    using mat4x4f = Matrix<float, 4, 4>;


    using mat2x2d = Matrix<double, 2, 2>;
    using mat2x3d = Matrix<double, 2, 3>;
    using mat2x4d = Matrix<double, 2, 4>;

    using mat3x2d = Matrix<double, 3, 2>;
    using mat3x3d = Matrix<double, 3, 3>;
    using mat3x4d = Matrix<double, 3, 4>;

    using mat4x2d = Matrix<double, 4, 2>;
    using mat4x3d = Matrix<double, 4, 3>;
    using mat4x4d = Matrix<double, 4, 4>;

}

#include "impl/IMPL_matrices.hpp"

#endif //AVML_MATRICES_HPP
