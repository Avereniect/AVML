#ifndef AVML_TRANSFORMS_HPP
#define AVML_TRANSFORMS_HPP

#include "Matrices.hpp"

namespace avml {

    mat3x3f translation_matrix(float, float);
    mat3x3f translation_matrix(vec2f);

    mat3x3f scaling_matrix(float, float);
    mat3x3f scaling_matrix(vec2f);

    mat3x3f rotation_matrix(float angle);



    mat4x4f translation_matrix(float, float, float);
    mat4x4f translation_matrix(vec3f);

    mat4x4f scaling_matrix(float, float , float );
    mat4x4f scaling_matrix(vec3f);

    mat4x4f x_rotation_matrix(float angle);
    mat4x4f y_rotation_matrix(float angle);
    mat4x4f z_rotation_matrix(float angle);

    mat4x4f rotation_matrix(uvec3f axis, float angle);




    mat3x3d translation_matrixd(double, double);
    mat3x3d translation_matrixd(vec2d);

    mat3x3d scaling_matrix(double, double);
    mat3x3d scaling_matrixd(vec2d);

    mat3x3d rotation_matrixd(double angle);



    mat4x4d translation_matrixd(double, double, double);
    mat4x4d translation_matrixd(vec3d);

    mat4x4d scaling_matrixd(double, double , double );
    mat4x4d scaling_matrixd(vec3d);

    mat4x4d x_rotation_matrixd(double angle);
    mat4x4d y_rotation_matrixd(double angle);
    mat4x4d z_rotation_matrixd(double angle);

    mat4x4d rotation_matrix(uvec3d axis, double angle);

}

#include "impl/IMPL_transforms.hpp"

#endif //AVML_TRANSFORMS_HPP
