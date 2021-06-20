#ifndef AVML_SSE_UNIT_VECTOR_HPP
#define AVML_SSE_UNIT_VECTOR_HPP

#include "../../Vectors.hpp"

namespace avml {

    template<>
    class Unit_vector<float, 4> {
    public:

        //=================================================
        // Type aliases
        //=================================================

        using scalar = float;

        //=================================================
        // -ctors
        //=================================================

        Unit_vector(float x, float y, float z, float w):
            elements({x, y, z, w}) {}

        Unit_vector() = default;
        Unit_vector(const Unit_vector&) = default;
        Unit_vector(Unit_vector&&) = default;
        ~Unit_vector() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Unit_vector& operator=(const Unit_vector&) = default;
        Unit_vector& operator=(Unit_vector&&) = default;

        //=================================================
        // Accessors
        //=================================================

        scalar& operator[](unsigned i) {
            return elements[i];
        }

        const scalar& operator[](unsigned i) {
            return elements[i];
        }

        scalar* data() {
            return elements;
        }

        const scalar* data() const {
            return elements;
        }

    private:

        //=================================================
        // Instance members
        //=================================================

        float elements[2];

    };

}

#endif //AVML_SSE_UNIT_VECTOR_HPP
