#ifndef AVML_TRANSFORMS_HPP
#define AVML_TRANSFORMS_HPP

#include "Matrices.hpp"

namespace avml {

    template<class R>
    class Translation2D;

    template<class R>
    class Translation3D;

    using Translation2Df = Translation2D<float>;
    using Translation2Dd = Translation2D<double>;

    using Translation3Df = Translation3D<float>;
    using Translation3Dd = Translation3D<double>;



    template<class R>
    class Rotation2D;

    template<class R>
    class Rotation3D;

    using Rotation2Df = Rotation2D<float>;
    using Rotation2Dd = Rotation2D<double>;

    using Rotation3Df = Rotation3D<float>;
    using Rotation3Dd = Rotation3D<double>;


    template<class R>
    class X_rotation;

    template<class R>
    class Y_rotation;

    template<class R>
    class Z_rotation;

    using X_rotationf = X_rotation<float>;
    using Y_rotationf = Y_rotation<float>;
    using Z_rotationf = Z_rotation<float>;

    using X_rotationd = X_rotation<double>;
    using Y_rotationd = Y_rotation<double>;
    using Z_rotationd = Z_rotation<double>;


    template<class R>
    class Axis_rotation;

    template<class R>
    class Euler_rotation;

    using Axis_rotationf = Axis_rotation<float>;
    using Axis_rotationd = Axis_rotation<double>;

    using Euler_rotationf = Euler_rotation<float>;
    using Euler_rotationd = Euler_rotation<double>;



    template<class R>
    class Scaling2D;

    template<class R>
    class Scaling3D;

    using Scaling2Df = Scaling2D<float>;
    using Scaling2Dd = Scaling2D<double>;

    using Scaling3Df = Scaling3D<float>;
    using Scaling3Dd = Scaling3D<double>;



    template<class R>
    class Affine2D;

    template<class R>
    class Affine3D;

    using Affine2Df = Affine2D<float>;
    using Affine2Dd = Affine2D<double>;

    using Affine3Df = Affine3D<float>;
    using Affine3Dd = Affine3D<double>;

}

#include "impl/IMPL_transforms.hpp"

#endif //AVML_TRANSFORMS_HPP
