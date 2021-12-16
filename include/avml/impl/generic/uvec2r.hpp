#ifndef AVML_GEN_UVEC2R_HPP
#define AVML_GEN_UVEC2R_HPP

namespace avml {

    template<class R>
    class alignas(avml_impl::vector_alignment<R, 2>()) Unit_vector2R {
    public:

        using scalar = R;

        static constexpr unsigned width = 2;

        //=================================================
        // Creation functions
        //=================================================

        AVML_FINL static Unit_vector2R read(const R* p) {
            return Unit_vector2R{p[0], p[1]};
        }

        AVML_FINL static Unit_vector2R read_aligned(const R* p) {
            return Unit_vector2R{p[0], p[1]};
        }

        //=================================================
        // -ctors
        //=================================================

        AVML_FINL Unit_vector2R(R x, R y) noexcept:
            elements() {
            using std::sqrt;
            R length = sqrt(x * x + y * y);

            elements[0] = x / length;
            elements[1] = y / length;
        }

        template<class T>
        explicit Unit_vector2R(Unit_vector2R<T> v):
            elements{
                static_cast<R>(v[0]),
                static_cast<R>(v[1])
            } {}

        Unit_vector2R() = default;
        Unit_vector2R(const Unit_vector2R&) = default;
        Unit_vector2R(Unit_vector2R&&) noexcept = default;
        ~Unit_vector2R() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Unit_vector2R& operator=(const Unit_vector2R&) = default;
        Unit_vector2R& operator=(Unit_vector2R&&) noexcept = default;

        //=================================================
        // Unary arithmetic operators
        //=================================================

        AVML_FINL Unit_vector2R operator+() const {
            return *this;
        }

        AVML_FINL Unit_vector2R operator-() const {
            Unit_vector2R ret;
            ret.elements[0] = -elements[0];
            ret.elements[1] = -elements[1];
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
        explicit operator Unit_vector2R<U>() const {
            Unit_vector2R<U> ret;
            ret.elements[0] = static_cast<U>(elements[0]);
            ret.elements[1] = static_cast<U>(elements[1]);
            return ret;
        }

    private:

        //=================================================
        // Instance members
        //=================================================

        R elements[width] = {1.0f, 0.0f};

    };

    //=====================================================
    // Vectorized math
    //=====================================================

    template<class R>
    AVML_FINL Unit_vector2R<R> abs(Unit_vector2R<R> v) {
        alignas(alignof(Unit_vector2R<R>)) R data[Unit_vector2R<R>::width];
        using std::abs;
        data[0] = abs(v[0]);
        data[1] = abs(v[1]);
        return Unit_vector2R<R>::read_aligned(data);
    }

}

#endif
