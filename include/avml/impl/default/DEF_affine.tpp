#ifndef AVML_DEF_AFFINE_TPP
#define AVML_DEF_AFFINE_TPP

namespace avml {

    template<class R>
    class alignas(alignof(R) * 16) Affine3D {
        static_assert(std::is_floating_point<R>::value);
    public:

        using scalar = R;
        using point = Point<R, 3>;
        using vector = Vector<R, 3>;
        using matrix = Matrix<R, 4, 4>;

        //=================================================
        // Creation methods
        //=================================================

        Affine3D read(const float* ptr) {
            return static_cast<Affine3D>(matrix::read(ptr));
        }

        Affine3D aligned_read(const float* ptr) {
            return static_cast<Affine3D>(matrix::aligned_read(ptr));
        }

        //=================================================
        // -ctors
        //=================================================

        explicit Affine3D(matrix mat) :
            mat(mat) {}

        Affine3D() = default;
        Affine3D(const Affine3D&) = default;
        Affine3D(Affine3D&&) = default;
        ~Affine3D() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Affine3D& operator=(const Affine3D&);
        Affine3D& operator=(Affine3D&&);

        //=================================================
        // Comparison operators
        //=================================================

        bool operator==(const Affine3D& rhs) {
            return (mat == rhs.mat);
        }

        bool operator!=(const Affine3D& rhs) {
            return (mat != rhs.mat);
        }

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
            Affine3D<R> ret = *this;
            ret.mat = inverse(ret.mat);
            return ret;
        }

        AVML_FINL point operator*(const point rhs) {
            Point<R, 4> t{rhs, R{}};
            auto v = mat * static_cast<typename matrix::vector>(t);
            return point{v[0], v[1], v[2]};
        }

        AVML_FINL point operator*(const vector rhs) {
            Vector<R, 4> t{rhs, R{}};
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

    };


    template<class R>
    class Affine2D {
        static_assert(std::is_floating_point<R>::value);
    public:

        using scalar = R;
        using point = Point<R, 2>;
        using matrix = Matrix<R, 3, 3>;

        //=================================================
        // -ctors
        //=================================================

        Affine2D() = default;
        Affine2D(const Affine2D&) = default;
        Affine2D(Affine2D&&) = default;
        ~Affine2D() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Affine2D& operator=(const Affine2D&) = default;
        Affine2D& operator=(Affine2D&&) = default;

        //=================================================
        // Comparison operators
        //=================================================

        AVML_FINL bool operator==(const Affine2D& rhs) {
            return mat == rhs.mat;
        }

        AVML_FINL bool operator!=(const Affine2D& rhs) {
            return mat != rhs.mat;
        }

        //=================================================
        // Instance members
        //=================================================

    private:

        matrix mat{1.0f};

    };

    //=====================================================
    // Affine transform functions
    //=====================================================

    template<class R>
    AVML_FINL Affine3D<R> inverse(Affine3D<R> affine) {
        return -affine;
    }

    template<class R>
    AVML_FINL Affine3D<R> transform(Affine3D<R> affine, Vector<R, 3> offset) {
        auto mat = static_cast<typename Affine3D<R>::matrix>(affine);
        mat[0][3] += offset[0];
        mat[1][3] += offset[1];
        mat[2][3] += offset[2];
        return static_cast<Affine3D<R>>(mat);
    }

    template<class R>
    AVML_FINL Affine3D<R> scale(Affine3D<R> affine, Vector<R, 3> scale) {
        auto mat = static_cast<typename Affine3D<R>::matrix>(affine);
        mat[0][0] *= scale[0];
        mat[1][1] *= scale[1];
        mat[2][2] *= scale[2];
        return static_cast<Affine3D<R>>(mat);
    }

    template<class R>
    AVML_FINL Affine3D<R> rotate(Affine3D<R> affine, R angle, Unit_vector<R, 3> axis) {
        float sine = std::sin(angle);
        float cosine = std::cos(angle);
        auto mat = static_cast<typename Affine3D<R>::matrix>(affine);

        //TODO: Implement

        return static_cast<Affine3D<R>>(mat);
    }

}

#endif //AVML_DEF_AFFINE_TPP
