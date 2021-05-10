#ifndef AVML_UNIT_VECTOT_HPP
#define AVML_UNIT_VECTOT_HPP

#include "Shared.hpp"

#include <cmath>
#include <cstdint>
#include <type_traits>

namespace avml {
    
    template<class T, unsigned N>
    class alignas(alignment(sizeof(T) * N)) Unit_vector {
    public:

        //=============================================
        // Assertions
        //=============================================

        static_assert((1 < N) && (N < 5));
        static_assert(std::is_floating_point_v<T>);

        //=============================================
        // -ctors
        //=============================================

        Unit_vector(T x, T y) {
            std::enable_if_t<N == 2, T> dummy{};

            elems[0] = x;
            elems[1] = y;

            T length = std::sqrt(
                elems[0] * elems[0] +
                elems[1] * elems[1]
            );

            elems[0] /= length;
            elems[1] /= length;
        }

        Unit_vector(T x, T y, T z) {
            std::enable_if_t<N == 3, T> dummy{};

            elems[0] = x;
            elems[1] = y;
            elems[2] = z;

            T length = std::sqrt(
                elems[0] * elems[0] +
                elems[1] * elems[1] +
                elems[2] * elems[2]
            );

            elems[0] /= length;
            elems[1] /= length;
            elems[2] /= length;
        }

        Unit_vector(T w, T x, T y, T z) {
            std::enable_if_t<N == 4, T> dummy{};

            elems[0] = w;
            elems[1] = x;
            elems[2] = y;
            elems[3] = z;

            T length = std::sqrt(
                elems[0] * elems[0] +
                elems[1] * elems[1] +
                elems[2] * elems[2] +
                elems[3] * elems[3]
            );

            elems[0] /= length;
            elems[1] /= length;
            elems[2] /= length;
            elems[3] /= length;
        }

        Unit_vector() = default;
        Unit_vector(const Unit_vector&) = default;
        Unit_vector(Unit_vector&&) noexcept= default;
        ~Unit_vector() = default;

        //=============================================
        // Assignment Operators
        //=============================================

        Unit_vector& operator=(const Unit_vector&) = default;
        Unit_vector& operator=(Unit_vector&&) noexcept = default;

        //=================================================
        // Comparison operators
        //=================================================

        bool operator==(Unit_vector<T, N> rhs) const {
            for (int i = 0; i < N; ++i) {
                if (elems[i] != rhs[i]) {
                    return false;
                }
            }
            return true;
        }

        bool operator!=(Unit_vector<T, N> rhs) const {
            return !(*this == rhs);
        }

        //=================================================
        // Accessors
        //=================================================

        float operator[](unsigned i) const {
            return elems[i % N];
        }

        const float* data() const {
            return elems;
        }

        constexpr std::size_t size() const {
            return N;
        }

        //=============================================
        // Conversion operators
        //=============================================

        operator Array<T, N>() const{
            Array<T, N> ret;

            for (int i = 0; i < N; ++i) {
                ret[i] = elems[i];
            }

            return ret;
        }

        //=============================================
        // Instance members
        //=============================================

    protected:

        T elems[N];

    };

    //=====================================================
    // Aliases
    //=====================================================

    using Uvec2 = Unit_vector<float, 2>;
    using Uvec3 = Unit_vector<float, 3>;
    using Uvec4 = Unit_vector<float, 4>;

    using Uvec2d = Unit_vector<double, 2>;
    using Uvec3d = Unit_vector<double, 3>;
    using Uvec4d = Unit_vector<double, 4>;
    
}

#endif //AVML_UNIT_VECTOT_HPP
