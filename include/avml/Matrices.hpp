#ifndef AVML_MATRICES_HPP
#define AVML_MATRICES_HPP

#include "impl/Capabilities.hpp"
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

    using Mat2x2f = Matrix<float, 2, 2>;
    using Mat2x3f = Matrix<float, 2, 3>;
    using Mat2x4f = Matrix<float, 2, 4>;

    using Mat3x2f = Matrix<float, 3, 2>;
    using Mat3x3f = Matrix<float, 3, 3>;
    using Mat3x4f = Matrix<float, 3, 4>;

    using Mat4x2f = Matrix<float, 4, 2>;
    using Mat4x3f = Matrix<float, 4, 3>;
    using Mat4x4f = Matrix<float, 4, 4>;


    using Mat2x2d = Matrix<double, 2, 2>;
    using Mat2x3d = Matrix<double, 2, 3>;
    using Mat2x4d = Matrix<double, 2, 4>;

    using Mat3x2d = Matrix<double, 3, 2>;
    using Mat3x3d = Matrix<double, 3, 3>;
    using Mat3x4d = Matrix<double, 3, 4>;

    using Mat4x2d = Matrix<double, 4, 2>;
    using Mat4x3d = Matrix<double, 4, 3>;
    using Mat4x4d = Matrix<double, 4, 4>;

}

#include "impl/default/DEF_matrix2x2f.hpp"
#include "impl/default/DEF_matrix3x3f.hpp"
#include "impl/default/DEF_matrix4x4f.hpp"

#endif //AVML_MATRICES_HPP
