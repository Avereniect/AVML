#ifndef AVML_MAT2X2F_TESTS_HPP
#define AVML_MAT2X2F_TESTS_HPP

#include <gtest/gtest.h>

namespace avml_tests {

    using namespace avml;

    TEST(Matrix2x2f, Constructors) {
        Mat2x2f m0{};
        EXPECT_EQ(m0[0][0], 0.0f);
        EXPECT_EQ(m0[0][1], 0.0f);
        EXPECT_EQ(m0[1][0], 0.0f);
        EXPECT_EQ(m0[1][1], 0.0f);

        Mat2x2f m1{1.0f};
        EXPECT_EQ(m1[0][0], 1.0f);
        EXPECT_EQ(m1[0][1], 0.0f);
        EXPECT_EQ(m1[1][0], 0.0f);
        EXPECT_EQ(m1[1][1], 1.0f);

        Mat2x2f m2{
            2.0f, 4.0f,
            6.0f, 8.0f
        };
        EXPECT_EQ(m2[0][0], 2.0f);
        EXPECT_EQ(m2[0][1], 4.0f);
        EXPECT_EQ(m2[1][0], 6.0f);
        EXPECT_EQ(m2[1][1], 8.0f);

        Vec2f r0{1.0f, 3.0f};
        Vec2f r1{5.0f, 7.0f};
        Mat2x2f m3{r0, r1};
        EXPECT_EQ(m3[0][0], 1.0f);
        EXPECT_EQ(m3[0][1], 3.0f);
        EXPECT_EQ(m3[1][0], 5.0f);
        EXPECT_EQ(m3[1][1], 7.0f);
    }

}

#endif //AVML_MAT2X2F_TESTS_HPP
