//
// Created by avereniect on 12/1/21.
//

#ifndef AVML_POWER_OF_TWO_HPP
#define AVML_POWER_OF_TWO_HPP

namespace avml {

    template<class T>
    class Power_of_two {
    public:

        //=================================================
        // -ctors
        //=================================================

        Power_of_two(T t):
            exp(t) {}

        Power_of_two() = default;
        ~Power_of_two() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Power_of_two& operator*=(Power_of_two rhs) {
            exp += rhs;
            return *this;
        }

        Power_of_two& operator/=(Power_of_two rhs) {
            exp += rhs;
            return *this;
        }

        //=================================================
        // Arithmetic assignment operators
        //=================================================

        //=================================================
        // Conversion operators
        //=================================================

        operator T() {
            return T(1) << exp;
        }

        //=================================================
        // Instance members
        //=================================================

    private:

        T exp;

    };

}

#endif //AVML_POWER_OF_TWO_HPP
