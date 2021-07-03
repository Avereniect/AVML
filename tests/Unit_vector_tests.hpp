#ifndef AVML_UNIT_VECTOR_TESTS_HPP
#define AVML_UNIT_VECTOR_TESTS_HPP

#include <gtest/gtest.h>

#include <avml/AVML.hpp>

namespace avml_tests {

    using namespace avml;

    TEST(Uvec2, Constructors) {
        Uvec2f vec0{};
        EXPECT_EQ(vec0[0], 1.0f);
        EXPECT_EQ(vec0[1], 0.0f);

        Uvec2f vec1{0.0f, 1.0f};
        EXPECT_EQ(vec1[0], 0.0f);
        EXPECT_EQ(vec1[1], 1.0f);
    }

    TEST(Uvec3, Constructors) {
        Uvec3f vec0;
        EXPECT_EQ(vec0[0], 1.0f);
        EXPECT_EQ(vec0[1], 0.0f);
        EXPECT_EQ(vec0[2], 0.0f);

        Uvec3f vec1{0.0f, 0.0f, 1.0f};
        EXPECT_EQ(vec1[0], 0.0f);
        EXPECT_EQ(vec1[1], 0.0f);
        EXPECT_EQ(vec1[2], 1.0f);
    }

    TEST(Uvec2, Negation) {
        Uvec2f vec0{1.0f, 0.0f};
        vec0 = -vec0;

        EXPECT_EQ(vec0[0], -1.0f);
        EXPECT_EQ(vec0[1], 0.0f);
    }

    TEST(Uvec3, Negation) {
        Uvec3f vec0{1.0f, 0.0f, 0.0f};
        vec0 = -vec0;

        EXPECT_EQ(vec0[0], -1.0f);
        EXPECT_EQ(vec0[1], 0.0f);
        EXPECT_EQ(vec0[2], 0.0f);
    }

}

#endif //AVML_UNIT_VECTOR_TESTS_HPP
