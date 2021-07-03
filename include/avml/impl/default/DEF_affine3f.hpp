#include <cmath>

namespace avml {

    template<>
    class alignas(alignof(Matrix<float, 4, 4>)) Affine3D<float> {
    public:

        using scalar = float;
        using point = Point<float, 3>;
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

        AVML_FINL point operator()(const point rhs) {
            Point<float, 4> t{rhs, 1.0f};
            auto matrix = mat;
            matrix[3][3] = 1.0f;
            auto v = matrix * static_cast<typename matrix::vector>(t);
            return point{v[0], v[1], v[2]};
        }

        AVML_FINL vector operator()(const vector rhs) {
            Vector<float, 4> t{rhs, 0.0};
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

        //=================================================
        // Conversion operators
        //=================================================

        AVML_FINL explicit operator matrix() const {
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
            return a * b.as_matrix();
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
            std::array<matrix, sizeof...(args)> matrices{args.as_matrix()...};

            //TODO: Use combine methods in first pass of logarithmic reduction to improve performance
            //TODO: Use combine methods exclusively when sizeof...(args) is small?
            for (int i = matrices.size() - 1; i-- > 1;) {
                matrices.back() *= matrices[i];
            }

            return matrices.back();
        }

    };

    //=================================================
    // Comparison operators
    //=================================================

    bool operator==(const Affine3Df& lhs, const Affine3Df& rhs) {
        using matrix = Matrix<float, 4, 4>;
        return static_cast<matrix>(lhs) == static_cast<matrix>(rhs);
    }

    bool operator!=(const Affine3Df& lhs, const Affine3Df& rhs) {
        using matrix = Matrix<float, 4, 4>;
        return static_cast<matrix>(lhs) != static_cast<matrix>(rhs);
    }

    AVML_FINL Affine3Df inverse(Affine3Df affine) {
        return -affine;
    }

}
