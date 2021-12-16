#ifndef AVML_GEN_UVEC4R_HPP
#define AVML_GEN_UVEC4R_HPP

namespace avml {

    template<class R>
    class alignas(avml_impl::vector_alignment<R, 4>()) Unit_vector4R {
    public:

        using scalar = R;

        static constexpr unsigned width = 4;

        //=================================================
        // Creation functions
        //=================================================

        AVML_FINL static Unit_vector4R read(const R* p) {
            return Unit_vector4R{p[0], p[1], p[2], p[3]};
        }

        AVML_FINL static Unit_vector4R read_aligned(const R* p) {
            return Unit_vector4R{p[0], p[1], p[2], p[3]};
        }

        //=================================================
        // -ctors
        //=================================================

        AVML_FINL Unit_vector4R(R x, R y, R z, R w) noexcept:
            elements() {
            using std::sqrt;
            R length = sqrt(x * x + y * y + z * z + w * w);

            elements[0] = x / length;
            elements[1] = y / length;
            elements[2] = z / length;
            elements[3] = w / length;
        }

        AVML_FINL Unit_vector4R(Unit_vector3R<R> v) :
            elements{v[0], v[1], v[2], 0.0f} {}

        template<class T>
        explicit Unit_vector4R(Unit_vector4R<T> v):
            elements{
                static_cast<R>(v[0]),
                static_cast<R>(v[1]),
                static_cast<R>(v[2]),
                static_cast<R>(v[3])
            } {}

        Unit_vector4R() = default;
        Unit_vector4R(const Unit_vector4R&) = default;
        Unit_vector4R(Unit_vector4R&&) noexcept = default;
        ~Unit_vector4R() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Unit_vector4R& operator=(const Unit_vector4R&) = default;
        Unit_vector4R& operator=(Unit_vector4R&&) noexcept = default;

        //=================================================
        // Unary arithmetic operators
        //=================================================

        AVML_FINL Unit_vector4R operator+() const {
            return *this;
        }

        AVML_FINL Unit_vector4R operator-() const {
            Unit_vector4R ret;
            ret.elements[0] = -elements[0];
            ret.elements[1] = -elements[1];
            ret.elements[2] = -elements[2];
            ret.elements[3] = -elements[3];
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
        explicit operator Unit_vector4R<U>() const {
            Unit_vector4R<U> ret;
            ret.elements[0] = static_cast<U>(elements[0]);
            ret.elements[1] = static_cast<U>(elements[1]);
            ret.elements[2] = static_cast<U>(elements[2]);
            ret.elements[3] = static_cast<U>(elements[3]);
            return ret;
        }

    private:

        //=================================================
        // Instance members
        //=================================================

        R elements[width] = {1.0f, 0.0f, 0.0f, 0.0f};

    };

    //=====================================================
    // Vectorized math
    //=====================================================

    template<class R>
    AVML_FINL Unit_vector4R<R> abs(Unit_vector4R<R> v) {
        alignas(alignof(Unit_vector4R<R>)) R data[Unit_vector4R<R>::width];
        using std::abs;
        data[0] = abs(v[0]);
        data[1] = abs(v[1]);
        data[2] = abs(v[2]);
        data[3] = abs(v[3]);
        return Unit_vector4R<R>::read_aligned(data);
    }

}

#endif
