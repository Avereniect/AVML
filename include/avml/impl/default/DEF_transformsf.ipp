#ifndef AVML_DEF_TRANSFORMSF_IPP
#define AVML_DEF_TRANSFORMSF_IPP

namespace avml {

    AVML_FINL mat3x3f translation_matrix(float x, float y) {
        return mat3x3f {
            {1.0f, 0.0f, x},
            {0.0f, 1.0f, y},
            {0.0f, 0.0f, 1.0f}
        };
    }

    AVML_FINL mat3x3f translation_matrix(vec2f d) {
        return translation_matrix(d[0], d[1]);
    }

    AVML_FINL mat3x3f scaling_matrix(float x, float y) {
        return mat3x3f{
            {x, 0.0f, 0.0f},
            {0.0f, y, 0.0f},
            {0.0f, 0.0f, 1.0f},
        };
    }

    AVML_FINL mat3x3f scaling_matrix(vec2f s) {
        return scaling_matrix(s[0], s[1]);
    }

    AVML_FINL mat3x3f rotation_matrix(float angle) {
        float s = std::sin(angle);
        float c = std::cos(angle);

        return mat3x3f{
            {c, -s, 0.0f},
            {s, c, 0.0f},
            {0.0f, 0.0f, 1.0f},
        };
    }



    AVML_FINL mat4x4f translation_matrix(float x, float y, float z) {
        return mat4x4f{
            {1.0f, 0.0f, 0.0f, x},
            {0.0f, 1.0f, 0.0f, y},
            {0.0f, 0.0f, 1.0f, z},
            {0.0f, 0.0f, 0.0f, 1.0f}
        };
    }

    AVML_FINL mat4x4f translation_matrix(vec3f t) {
        return translation_matrix(t[0], t[1], t[2]);
    }

    AVML_FINL mat4x4f scaling_matrix(float x, float y, float z) {
        return mat4x4f{
            {x, 0.0f, 0.0f, 0.0f},
            {0.0f, y, 0.0f, 0.0f},
            {0.0f, 0.0f, z, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        };
    }

    AVML_FINL mat4x4f scaling_matrix(vec3f s) {
        return scaling_matrix(s[0], s[1], s[2]);
    }

    AVML_FINL mat4x4f x_rotation_matrix(float angle) {
        float s = std::sin(angle);
        float c = std::cos(angle);

        return mat4x4f{
            {1.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, c, -s, 0.0f},
            {0.0f, s, c, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        };
    }

    AVML_FINL mat4x4f y_rotation_matrix(float angle) {
        float s = std::sin(angle);
        float c = std::cos(angle);

        return mat4x4f{
            {c, 0.0f, s, 0.0f},
            {0.0f, 1.0f, 0.0f, 0.0f},
            {-s, 0.0f, c, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        };
    }

    AVML_FINL mat4x4f z_rotation_matrix(float angle) {
        float s = std::sin(angle);
        float c = std::cos(angle);

        return mat4x4f{
            {c, -s, 0.0f, 0.0f},
            {s, c, 0.0f, 0.0f},
            {0.0f, 0.0f, 1.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        };
    }

    AVML_FINL mat4x4f rotation_matrix(uvec3f axis, float angle) {
        float s = std::sin(angle);
        float c = std::cos(angle);

        float ic = 1.0f - c;

        float x = axis[0];
        float y = axis[1];
        float z = axis[2];

        return mat4x4f{
            {c + x * x * ic, x * y * ic - z * s, x * z + y * s, 0.0f},
            {y * x * ic + z * s, c + y * y * ic, y * z * ic - x * s , 0.0f},
            {z * x * ic - y * s, z * y * ic + x * s, c + z * z * ic, 0.0f},
            {0.0f, 0.0f, 0.0f , 1.0f}
        };
    }

}

#endif //AVML_DEF_TRANSFORMSF_IPP
