#ifndef AVML_DEF_AFFINE3F_IPP
#define AVML_DEF_AFFINE3F_IPP

#include <cmath>
#include <array>

namespace avml {

    template<>
    class alignas(alignof(Matrix<float, 4, 4>)) Affine3D<float> {
    public:

        using scalar = float;
        using unit_vector = Unit_vector<float, 3>;
        using vector = Vector<float, 3>;
        using matrix = Matrix<float, 4, 4>;

        //=================================================
        // Creation methods
        //=================================================

        AVML_FINL static Affine3D read(const float* ptr) {
            Affine3Df ret;
            ret.mat = matrix::read(ptr);
            return ret;
        }

        AVML_FINL static Affine3D read_aligned(const float* ptr) {
            Affine3Df ret;
            ret.mat = matrix::read_aligned(ptr);
            return ret;
        }

        //=================================================
        // -ctors
        //=================================================

        template<class T, class...Args>
        explicit Affine3D(T t, Args&&...args):
            mat(create_matrix(t, args...)) {}

        explicit Affine3D(Scaling3Df s, Rotation3Df r, Translation3Df t):
            mat(create_matrix(s, r, t)) {}

        Affine3D() = default;
        Affine3D(const Affine3D&) = default;
        Affine3D(Affine3D&&) = default;
        ~Affine3D() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Affine3D& operator=(const Affine3D&) = default;
        Affine3D& operator=(Affine3D&&) = default;

        //=================================================
        // Arithmetic assignment operators
        //=================================================

        AVML_FINL Affine3D& operator*=(const Affine3D& rhs) {
            mat *= rhs.mat;
            return *this;
        }

        //=================================================
        // Arithmetic operators
        //=================================================

        AVML_FINL Affine3D operator-() const {
            Affine3D ret = *this;
            //TODO: Implement more efficient solution
            ret.mat = inverse(ret.mat);
            return ret;
        }

        //=================================================
        // Application methods
        //=================================================

        AVML_FINL vector operator()(const vector rhs) {
            Vector<float, 4> t{rhs, 1.0};
            auto v = mat * t;
            return vector{v[0], v[1], v[2]};
        }

        //=================================================
        // Accessors operators
        //=================================================

        AVML_FINL float* data() {
            return mat.data();
        }

        AVML_FINL const float* data() const {
            return mat.data();
        }

        AVML_FINL operator matrix() const {
            return mat;
        }

        //=================================================
        // Instance members
        //=================================================

    private:

        matrix mat{1.0f};

        //=================================================
        // Helper methods
        //=================================================

        //TODO: Move elsewhere

        static AVML_FINL matrix combine(matrix a, Translation3Df b) {
            a[0][3] += (a[0][0] * b.offset[0]) + (a[0][1] * b.offset[1]) + (a[0][2] * b.offset[2]);
            a[1][3] += (a[1][0] * b.offset[0]) + (a[1][1] * b.offset[1]) + (a[1][2] * b.offset[2]);
            a[2][3] += (a[2][0] * b.offset[0]) + (a[2][1] * b.offset[1]) + (a[2][2] * b.offset[2]);
            return a;
        }

        static AVML_FINL matrix combine(matrix a, Rotation3Df b) {
            return a * mat4x4f{b};
        }

        static AVML_FINL matrix combine(matrix a, Scaling3Df b) {
            a[0][0] *= b.v[0];
            a[0][1] *= b.v[0];
            a[0][2] *= b.v[0];

            a[1][0] *= b.v[1];
            a[1][1] *= b.v[1];
            a[1][2] *= b.v[1];

            a[2][0] *= b.v[2];
            a[2][1] *= b.v[2];
            a[2][2] *= b.v[2];

            return a;
        }

        template<class...Args>
        static AVML_FINL matrix create_matrix(Args&&...args) {
            static_assert(sizeof...(args) > 0, "More than one transform required.");
            std::array<matrix, sizeof...(args)> matrices{mat4x4f{args}...};

            //TODO: Use combine methods in first pass of logarithmic reduction to improve performance
            //TODO: Use combine methods exclusively when sizeof...(args) is small?
            for (int i = matrices.size() - 1; i-- > 0;) {
                matrices.back() *= matrices[i];
            }

            return matrices.back();
        }

        /*
        template<>
        static AVML_FINL matrix create_matrix<Translation3Df, Rotation3Df, Scaling3Df>(Translation3Df&& t, Rotation3Df&& r, Scaling3Df&& s) {
            auto rmat = r.mat;
            return matrix {
                s.v[0] * rmat[0][0], s.v[1] * rmat[0][1], s.v[2] * rmat[0][2], t.offset[0],
                s.v[0] * rmat[1][0], s.v[1] * rmat[1][1], s.v[2] * rmat[1][2], t.offset[1],
                s.v[0] * rmat[2][0], s.v[1] * rmat[2][1], s.v[2] * rmat[2][2], t.offset[2],
                0.0f, 0.0f, 0.0f, 1.0f
            };
        }
        */

    };

    //=================================================
    // Comparison operators
    //=================================================

    AVML_FINL bool operator==(const Affine3Df& lhs, const Affine3Df& rhs) {
        return mat4x4f{lhs} == mat4x4f{rhs};
    }

    AVML_FINL bool operator!=(const Affine3Df& lhs, const Affine3Df& rhs) {
        using matrix = Matrix<float, 4, 4>;
        return mat4x4f{lhs} != mat4x4f{rhs};
    }

    AVML_FINL Affine3Df inverse(Affine3Df affine) {
        return -affine;
    }

    //=================================================
    // Free functions
    //=================================================

    AVML_FINL Affine3Df clear_translation(Affine3Df affine) {
        mat4x4f m = affine;
        m[0][3] = 0.0f;
        m[1][3] = 0.0f;
        m[2][3] = 0.0f;
        return Affine3Df::read_aligned(m.data());
    }

    AVML_FINL Affine3Df clear_scale(Affine3Df affine) {
        auto m = transpose(affine);
        m[0] = normalize(m[0]);
        m[1] = normalize(m[1]);
        m[2] = normalize(m[2]);
        m = transpose(m);
        return Affine3Df::read_aligned(m.data());
    }

    AVML_FINL Affine3Df clear_rotation(Affine3Df affine) {
        auto m = transpose(affine);
        float lx = length(m[0]);
        float ly = length(m[1]);
        float lz = length(m[2]);

        mat4x4f ret = affine;
        ret[0][0] = lx;
        ret[0][1] = 0.0f;
        ret[0][2] = 0.0f;

        ret[1][0] = 0.0f;
        ret[1][1] = ly;
        ret[1][2] = 0.0f;

        ret[2][0] = 0.0f;
        ret[2][1] = 0.0f;
        ret[2][2] = lz;

        return Affine3Df::read_aligned(ret.data());
    }

}

#endif
