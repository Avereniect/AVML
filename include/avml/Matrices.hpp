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

    using Mat2x2 = Matrix<float, 2, 2>;
    using Mat2x3 = Matrix<float, 2, 3>;
    using Mat2x4 = Matrix<float, 2, 4>;

    using Mat3x2 = Matrix<float, 3, 2>;
    using Mat3x3 = Matrix<float, 3, 3>;
    using Mat3x4 = Matrix<float, 3, 4>;

    using Mat4x2 = Matrix<float, 4, 2>;
    using Mat4x3 = Matrix<float, 4, 3>;
    using Mat4x4 = Matrix<float, 4, 4>;

}

#include "impl/default/DEF_matrix.tpp"

#endif //AVML_MATRICES_HPP
