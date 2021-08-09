#ifndef AVML_IMPL_TRANSFORMS_HPP
#define AVML_IMPL_TRANSFORMS_HPP

#include "IMPL_capabilities.hpp"

namespace avml {

    template<class R>
    class Translation2D {
    public:

        friend class Affine3D<R>;

        //=================================================
        // Type aliases
        //=================================================

        using scalar = R;
        using unit_vector = Unit_vector<R, 3>;
        using vector = Vector<R, 2>;
        using affine = Affine2D<R>;

        //=================================================
        // -ctors
        //=================================================

        Translation2D(float x, float y, float z):
            offset(x, y, z) {}

        explicit Translation2D(vector v):
            offset(v) {}

        Translation2D() = default;
        Translation2D(const Translation2D&) = default;
        Translation2D(Translation2D&&) = default;
        ~Translation2D() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Translation2D& operator=(const Translation2D&) = default;
        Translation2D& operator=(Translation2D&&) = default;

        //=================================================
        // Application operators
        //=================================================

        vector operator()(vector p) const {
            return p + offset;
        }

        //=================================================
        // Accessors
        //=================================================

        vector get_translation() const {
            return offset;
        }

        //=================================================
        // Instance members
        //=================================================

    private:

        Vector<R, 2> offset{};

    };

    template<class R>
    class Translation3D {
    public:

        friend class Affine3D<R>;

        //=================================================
        // Type aliases
        //=================================================

        using scalar = R;
        using unit_vector = Unit_vector<R, 3>;
        using vector = Vector<R, 3>;
        using affine = Affine2D<R>;

        //=================================================
        // -ctors
        //=================================================

        Translation3D(R x, R y, R z):
            offset(x, y, z) {}

        explicit Translation3D(vector v):
            offset(v) {}

        Translation3D() = default;
        Translation3D(const Translation3D&) = default;
        Translation3D(Translation3D&&) = default;
        ~Translation3D() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Translation3D& operator=(const Translation3D&) = default;
        Translation3D& operator=(Translation3D&&) = default;

        //=================================================
        // Conversion methods
        //=================================================

        AVML_FINL explicit operator mat4x4f() const {
            return mat4x4f{
                1.0f, 0.0f, 0.0f, offset[0],
                0.0f, 1.0f, 0.0f, offset[1],
                0.0f, 0.0f, 1.0f, offset[2],
                0.0f, 0.0f, 0.0f, 1.0f,
            };
        }

        //=================================================
        // Instance members
        //=================================================

    private:

        vector offset{};

    };

    template<class R>
    class Scaling2D {
    public:

        //=================================================
        // Type aliases
        //=================================================

        using scalar = R;
        using vector = Vector<R, 2>;
        using affine = Affine3D<R>;

        //=================================================
        // -ctors
        //=================================================

        AVML_FINL Matrix<R, 3, 3> as_matrix() const{
            return Matrix<R, 3, 3>{
                f[0], 0, 0,
                0, f[1], 0,
                0, 0, 1
            };
        }

    private:

        vector f;

    };

    template<class R>
    class Scaling3D {
    public:

        friend class Affine3D<R>;

        //=================================================
        // Type aliases
        //=================================================

        using scalar = R;
        using unit_vector = Unit_vector<R, 3>;
        using vector = Vector<R, 3>;
        using affine = Affine3D<R>;

        //=================================================
        // -ctors
        //=================================================

        AVML_FINL explicit Scaling3D(float s):
            v(s) {}

        AVML_FINL explicit Scaling3D(vector v):
            v(v) {}

        AVML_FINL Scaling3D(float x, float y, float z):
            v(x, y, z) {}

        Scaling3D() = default;
        Scaling3D(const Scaling3D&) = default;
        Scaling3D(Scaling3D&&) = default;
        ~Scaling3D() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Scaling3D& operator=(const Scaling3D&) = default;
        Scaling3D& operator=(Scaling3D&&) = default;

        //=================================================
        // Application operators
        //=================================================

        AVML_FINL vector operator()(unit_vector uvec) const {
            return vector{
                uvec[0] * v[0],
                uvec[1] * v[1],
                uvec[2] * v[2]
            };
        }

        AVML_FINL vector operator()(vector vec) const {
            return vector {
                vec[0] * v[0],
                vec[1] * v[1],
                vec[2] * v[2]
            };
        }

        //=================================================
        // Conversion methods
        //=================================================

        AVML_FINL explicit operator mat4x4f() const {
            return mat4x4f{
                {v[0], 0.0f, 0.0f, 0.0f},
                {0.0f, v[1], 0.0f, 0.0f},
                {0.0f, 0.0f, v[2], 0.0f},
                {0.0f, 0.0f, 0.0f, 1.0f}
            };
        }

        //=================================================
        // Instance members
        //=================================================

    private:

        vector v;

    };





    template<class R>
    class Axis_rotation {
    public:

        //=================================================
        // Type aliases
        //=================================================

        using scalar = R;
        using unit_vector = Unit_vector<R, 3>;
        using vector = Vector<R, 3>;
        using affine = Affine3D<R>;

        //=================================================
        // -ctors
        //=================================================

        Axis_rotation() = default;
        Axis_rotation(const Axis_rotation&) = default;
        Axis_rotation(Axis_rotation&&) = default;
        ~Axis_rotation() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Axis_rotation& operator=(const Axis_rotation&) = default;
        Axis_rotation& operator=(Axis_rotation&&) = default;

        //=================================================
        // Application operators
        //=================================================

        AVML_FINL unit_vector operator()(unit_vector p) const;

        AVML_FINL vector operator()(vector v) const;

        //=================================================
        // Conversion methods
        //=================================================

        AVML_FINL explicit operator mat4x4f() const {
            return mat4x4f{
                {cosine + axis[0] * axis[0] * cosine_inverse, axis[0] * axis[1] * cosine_inverse - axis[2] * sine, axis[0] * axis[2] * cosine_inverse + axis[1] * sine, 0},
                {axis[0] * axis[1] * cosine_inverse + axis[2] * sine, cosine + axis[0] * axis[0] * cosine_inverse, axis[1] * axis[2] * cosine_inverse - axis[0] * sine, 0},
                {axis[0] * axis[2] * cosine_inverse - axis[1] * sine, axis[1] * axis[2] * cosine_inverse + axis[0] * sine, cosine + axis[2] * axis[2] * cosine_inverse, 0},
                {0, 0, 0, 1}
            };
        }

    private:

        float sine = 0.0f;
        float cosine = 1.0f;
        float cosine_inverse = 0.0f;

        float axis[3]{1.0f, 0.0f, 0.0f};

    };

    template<class R>
    class X_rotation {
    public:

        using scalar = R;
        using vector = Vector<R, 3>;
        using unit_vector = Unit_vector<R, 3>;

        //=================================================
        // -ctors
        //=================================================

        explicit X_rotation(R angle):
            sine(std::sin(angle)),
            cosine(std::cos(angle)) {}

        //=================================================
        // Conversions
        //=================================================

        AVML_FINL explicit operator mat4x4f() const {
            return Matrix<R, 4, 4> {
                {1, 0, 0, 0},
                {0, cosine, -sine, 0},
                {0, sine, cosine, 0},
                {0, 0, 0, 1}
            };
        }

    private:

        R sine = 0;
        R cosine = 1;

    };

    template<class R>
    class Y_rotation {
    public:

        using scalar = R;
        using vector = Vector<R, 3>;
        using unit_vector = Unit_vector<R, 3>;

        //=================================================
        // -ctors
        //=================================================

        explicit Y_rotation(R angle):
            sine(std::sin(angle)),
            cosine(std::cos(angle)) {}

        //=================================================
        // Conversions
        //=================================================

        AVML_FINL explicit operator mat4x4f() const {
            return Matrix<R, 4, 4> {
                {cosine, 0, sine, 0},
                {0, 1, 0, 0},
                {-sine, 0, cosine, 0},
                {0, 0, 0, 1}
            };
        }

    private:

        R sine = 0;
        R cosine = 1;

    };

    template<class R>
    class Z_rotation {
    public:

        using scalar = R;
        using vector = Vector<R, 3>;
        using unit_vector = Unit_vector<R, 3>;

        //=================================================
        // -ctors
        //=================================================

        explicit Z_rotation(R angle):
            sine(std::sin(angle)),
            cosine(std::cos(angle)) {}

        //=================================================
        // Conversions
        //=================================================

        AVML_FINL explicit operator mat4x4f() const {
            return Matrix<R, 4, 4> {
                {cosine, -sine, 0, 0},
                {sine, cosine, 0, 0},
                {0, 0, 1, 0},
                {0, 0, 0, 1},
            };
        }

    private:

        R sine = 0;
        R cosine = 1;

    };

    template<class R>
    class Rotation3D {
    public:

        friend class Affine3D<R>;

        //=================================================
        // Type aliases
        //=================================================

        using scalar = R;
        using unit_vector = Unit_vector<R, 3>;
        using vector = Vector<R, 3>;
        using affine = Affine3D<R>;

        //=================================================
        // -ctors
        //=================================================

        ///
        /// Constructs a rotation object representing a rotation around an
        /// arbitrary axis.
        ///
        /// \param angle Rotation angle
        /// \param axis Axis to rotate around
        AVML_FINL Rotation3D(R angle, unit_vector axis):
            Rotation3D(Axis_rotation<R>(angle, axis)) {}

        AVML_FINL explicit Rotation3D(Axis_rotation<R> rotation):
            mat(rotation.as_matrix()) {}

        AVML_FINL explicit Rotation3D(X_rotation<R> rotation):
            mat(rotation.as_matrix()) {}

        AVML_FINL explicit Rotation3D(Y_rotation<R> rotation):
            mat(rotation.as_matrix()) {}

        AVML_FINL explicit Rotation3D(Z_rotation<R> rotation):
            mat(rotation.as_matrix()) {}

        Rotation3D() = default;
        Rotation3D(const Rotation3D&) = default;
        Rotation3D(Rotation3D&&) noexcept = default;
        ~Rotation3D() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Rotation3D& operator=(const Rotation3D&) = default;
        Rotation3D& operator=(Rotation3D&&) noexcept = default;

        //=================================================
        // Operators
        //=================================================

        AVML_FINL unit_vector operator()(unit_vector v) const {
            return unit_vector::read_aligned((mat * v).data());
        }

        AVML_FINL vector operator()(vector v) const {
            return mat * v;
        }

        AVML_FINL explicit operator mat4x4f() const {
            return Matrix<R, 4, 4> {
                {mat[0], 0.0f},
                {mat[1], 0.0f},
                {mat[2], 0.0f},
                {0.0f, 0.0f, 0.0f, 1.0f}
            };
        }

    private:

        Matrix<R, 3, 3> mat{1.0f};

    };

}

#include "default/DEF_axis_rotationf.ipp"
#include "default/DEF_xyz_rotationf.ipp"

#include "default/DEF_affine2f.ipp"
#include "default/DEF_affine3f.ipp"

#endif //AVML_IMPL_TRANSFORMS_HPP
