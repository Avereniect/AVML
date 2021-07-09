#ifndef AVML_DEF_AFFINE2F_IPP
#define AVML_DEF_AFFINE2F_IPP

namespace avml {

    template<class R>
    class Affine2D {
        static_assert(std::is_floating_point<R>::value);
    public:

        using scalar = R;
        using vector = Vector<R, 2>;
        using matrix = Matrix<R, 3, 3>;

        //=================================================
        // -ctors
        //=================================================

        template<class T, class...Args>
        Affine2D(Args&&...args);

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
        // Arithmetic assignment operators
        //=================================================

        AVML_FINL Affine2D& operator*=(const Affine2D& rhs) {
            mat *= rhs.mat;
            return *this;
        }

        //=================================================
        // Arithmetic operators
        //=================================================

        AVML_FINL Affine2D operator-() const {
            Affine2D<R> ret = *this;
            //TODO: Implement more efficient solution
            ret.mat = inverse(ret.mat);
            return ret;
        }

        AVML_FINL vector operator()(const vector rhs) const {
            Vector<R, 4> t{rhs, 0};
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

        friend AVML_FINL matrix as_matrix(Affine2Df affine) {
            return affine.mat;
        }

        //=================================================
        // Instance members
        //=================================================

    private:

        matrix mat{1.0f};

    };

    AVML_FINL Affine2Df inverse(Affine2Df affine) {
        return -affine;
    }

}

#endif
