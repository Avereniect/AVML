#ifndef AVML_VEC2I_TESTS_HPP
#define AVML_VEC2I_TESTS_HPP

#include <gtest/gtest.h>
#include <type_traits>
#include <cstdint>

#include <avml/Vectors.hpp>

namespace avml_tests {

    using namespace avml;

    static_assert(vec2i::width == 2, "");
    static_assert(std::is_same<vec2i::scalar, std::int32_t>::value);
    static_assert(alignof(vec2i) == sizeof(std::int32_t) * 2);

    TEST(vec2i, Read) {
        std::int32_t data[2]{34, 78};
        vec2i v = vec2i::read(data);

        EXPECT_EQ(v[0], 34);
        EXPECT_EQ(v[1], 78);
    }

    TEST(vec2i, Read_aligned) {
        alignas(alignof(vec2i)) std::int32_t data[2]{34, 78};
        vec2i v = vec2i::read_aligned(data);

        EXPECT_EQ(v[0], 34);
        EXPECT_EQ(v[1], 78);
    }

    TEST(vec2i, Default_constuctor) {
        vec2i v{};

        EXPECT_EQ(v[0], 0);
        EXPECT_EQ(v[1], 0);
    }

    TEST(vec2i, Scalar_constructor) {
        vec2i v{17};

        EXPECT_EQ(v[0], 17);
        EXPECT_EQ(v[1], 17);
    }

    TEST(vec2i, Two_scalar_constructor) {
        vec2i v{15, 17};

        EXPECT_EQ(v[0], 15);
        EXPECT_EQ(v[1], 17);
    }

    TEST(vec2i, Identity) {
        vec2i v{12, 78};
        v = +v;

        EXPECT_EQ(v[0], 12);
        EXPECT_EQ(v[1], 78);
    }

    TEST(vec2i, Negation) {
        vec2i v{56, 40};
        v = -v;

        EXPECT_EQ(v[0], -56);
        EXPECT_EQ(v[1], -40);
    }

    TEST(vec2i, Addiiton_assignment) {
        vec2i v{1, 4};
        v += {4, 7};

        EXPECT_EQ(v[0], 5);
        EXPECT_EQ(v[1], 11);
    }

    TEST(vec2i, Subtraction_assignment) {
        vec2i v{1, 4};
        v -= {4, 8};

        EXPECT_EQ(v[0], -3);
        EXPECT_EQ(v[1], -4);
    }

    TEST(vec2i, Multiplication_assignment_scalar) {
        vec2i v{4, 5};
        v *= 4;

        EXPECT_EQ(v[0], 16);
        EXPECT_EQ(v[1], 20);
    }

    TEST(vec2i, Multiplication_assignment_vector) {
        vec2i v{4, 5};
        v *= {5, 2};

        EXPECT_EQ(v[0], 20);
        EXPECT_EQ(v[1], 10);
    }

    TEST(vec2i, Division_assignment_scalar) {
        vec2i v{4, 16};
        v /= 4;

        EXPECT_EQ(v[0], 1);
        EXPECT_EQ(v[1], 4);
    }

    TEST(vec2i, Division_assignment_vector) {
        vec2i v{4, 16};
        v /= {4, 2};

        EXPECT_EQ(v[0], 1);
        EXPECT_EQ(v[1], 8);
    }

    TEST(vec2i, Equality_comparison) {
        vec2i v0{4, 5};
        vec2i v1{4, 5};
        vec2i v2{4, 6};

        EXPECT_TRUE(v0 == v1);
        EXPECT_FALSE(v0 == v2);
    }

    TEST(vec2i, Inequality_comparison) {
        vec2i v0{4, 5};
        vec2i v1{4, 5};
        vec2i v2{4, 6};

        EXPECT_FALSE(v0 != v1);
        EXPECT_TRUE(v0 != v2);
    }

}

#endif
