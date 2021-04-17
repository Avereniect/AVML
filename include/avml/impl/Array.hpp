#ifndef AVML_ARRAY_HPP
#define AVML_ARRAY_HPP

#include "Util.hpp"

namespace avml {

    template<class T, unsigned N>
    class alignas(alignment(sizeof(T) * N)) Array {
    public:

        //=============================================
        // Assertions
        //=============================================

        static_assert((1 < N) && (N < 5));
        static_assert(std::is_floating_point_v<T> || std::is_integral_v<T>);

        //=============================================
        // -ctors
        //=============================================

        Array(T x, T y) {
            std::enable_if_t<N == 2, T> dummy{};

            elems[0] = x;
            elems[1] = y;
        }

        Array(T x, T y, T z) {
            std::enable_if_t<N == 3, T> dummy{};

            elems[0] = x;
            elems[1] = y;
            elems[2] = z;
        }

        Array(T w, T x, T y, T z) {
            std::enable_if_t<N == 4, T> dummy{};

            elems[0] = w;
            elems[1] = x;
            elems[2] = y;
            elems[3] = z;
        }

        Array() = default;
        Array(const Array&) = default;
        Array(Array&&) noexcept= default;
        ~Array() = default;

        //=============================================
        // Assignment Operators
        //=============================================

        Array& operator=(const Array&) = default;
        Array& operator=(Array&&) noexcept = default;

        //=================================================
        // Comparison operators
        //=================================================

        bool operator==(Array<T, N> rhs) const {
            for (int i = 0; i < N; ++i) {
                if (elems[i] != rhs[i]) {
                    return false;
                }
            }
            return true;
        }

        bool operator!=(Array<T, N> rhs) const {
            return !(*this == rhs);
        }

        //=================================================
        // Accessors
        //=================================================

        float& operator[](unsigned i) {
            return elems[i % N];
        }

        float operator[](unsigned i) const {
            return elems[i % N];
        }

        float* data() {
            return elems;
        }

        const float* data() const {
            return elems;
        }

        constexpr std::size_t size() const {
            return N;
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

    using Arr2 = Array<float, 2>;
    using Arr3 = Array<float, 3>;
    using Arr4 = Array<float, 4>;

    using Arr2d = Array<double, 2>;
    using Arr3d = Array<double, 3>;
    using Arr4d = Array<double, 4>;

    using Arr2i = Array<std::int32_t, 2>;
    using Arr3i = Array<std::int32_t, 3>;
    using Arr4i = Array<std::int32_t, 4>;

    using Arr2u = Array<std::uint32_t, 2>;
    using Arr3u = Array<std::uint32_t, 3>;
    using Arr4u = Array<std::uint32_t, 4>;

}

#endif //AVML_ARRAY_HPP
