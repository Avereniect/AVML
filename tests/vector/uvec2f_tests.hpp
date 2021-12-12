//
// Created by avereniect on 12/12/21.
//

#ifndef AVML_UNIT_VECTOR2_HPP
#define AVML_UNIT_VECTOR2_HPP

#include <gtest/gtest.h>

#include <avml/Vectors.hpp>

namespace avml_tests {

    using namespace avml;

    static_assert(std::is_same<uvec2f::scalar, float>::value, "");
    static_assert(uvec2f::width == 2, "");

    TEST(uvec2f, Default_constructor) {
        uvec2f v{};

        EXPECT_EQ(v[0], 1.0f);
        EXPECT_EQ(v[1], 0.0f);
    }

    TEST(uvec2f, Two_scalar_constructor) {
        uvec2f v{0.0f, 1.0f};

        EXPECT_EQ(v[0], 0.0f);
        EXPECT_EQ(v[1], 1.0f);
    }

}

#endif //AVML_UNIT_VECTOR2_HPP
