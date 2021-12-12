#ifndef AVML_GEN_UVEC3F_IPP
#define AVML_GEN_UVEC3F_IPP

namespace avml {

    template<class R>
    class alignas(avml_impl::vector_alignment<R, 3>) Unit_vector3 {
    public:

        using scalar = R;

        static constexpr unsigned width = 3;

        //=================================================
        // Creation functions
        //=================================================

        AVML_FINL static Unit_vector3 read(const R* p) {
            return Unit_vector3{p[0], p[1], p[2]};
        }

        AVML_FINL static Unit_vector3 read_aligned(const R* p) {
            return Unit_vector3{p[0], p[1], p[2]};
        }

        //=================================================
        // -ctors
        //=================================================

        AVML_FINL Unit_vector3(R x, R y, R z):
            elements() {
            using std::sqrt;
            R length = sqrt(x * x + y * y + z * z);

            elements[0] = x / length;
            elements[1] = y / length;
            elements[2] = z / length;
        }

        AVML_FINL Unit_vector3(Unit_vector2<R> v):
            elements{v[0], v[1], 0.0f} {}

        Unit_vector3() = default;
        Unit_vector3(const Unit_vector3&) = default;
        Unit_vector3(Unit_vector3&&) noexcept = default;
        ~Unit_vector3() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Unit_vector3& operator=(const Unit_vector3&) = default;
        Unit_vector3& operator=(Unit_vector3&&) noexcept = default;

        //=================================================
        // Unary arithmetic operators
        //=================================================

        AVML_FINL Unit_vector3 operator+() const {
            return *this;
        }

        AVML_FINL Unit_vector3 operator-() const {
            Unit_vector3 ret;
            ret.elements[0] = -elements[0];
            ret.elements[1] = -elements[1];
            ret.elements[2] = -elements[2];
            return ret;
        }

        //=================================================
        // Accessors
        //=================================================

        AVML_FINL const R& operator[](unsigned i) const {
            return elements[i];
        }

        AVML_FINL const R* data() const {
            return elements;
        }

        //=================================================
        // Conversion operators
        //=================================================

        template<class U>
        explicit operator Unit_vector3R<U>() const {
            Unit_vector3R<U> ret;
            ret.elements[0] = static_cast<U>(elements[0]);
            ret.elements[1] = static_cast<U>(elements[1]);
            ret.elements[2] = static_cast<U>(elements[2]);
            return ret;
        }

    private:

        //=================================================
        // Instance members
        //=================================================

        R elements[width] = {1.0f, 0.0f, 0.0f};

    };

    template<class R>
    AVML_FINL Unit_vector3<R> cross(Unit_vector3<R> lhs, Unit_vector3<R> rhs) {
        R data[3] = {
            lhs[1] * rhs[2] - lhs[2] * rhs[1],
            lhs[2] * rhs[0] - lhs[0] * rhs[2],
            lhs[0] * rhs[1] - lhs[1] * rhs[0]
        };

        return Unit_vector3<R> ::read(data);
    }

    //=====================================================
    // Vectorized math
    //=====================================================

    template<class R>
    AVML_FINL Unit_vector3<R> abs(Unit_vector3<R> v) {
        alignas(alignof(Unit_vector3<R>)) R data[Unit_vector3<R>::width];
        using std::abs;
        data[0] = std::abs(v[0]);
        data[1] = std::abs(v[1]);
        data[2] = std::abs(v[2]);
        return Unit_vector3<R>::read_aligned(data);
    }

}

#endif
