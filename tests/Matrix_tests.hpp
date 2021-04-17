#ifndef AVML_MATRIX_TESTS_HPP
#define AVML_MATRIX_TESTS_HPP

#include <gtest/gtest.h>
#include <avml/Matrices.hpp>

namespace avml_tests {

    using namespace avml;

    TEST(Multiplication, Two_by_two) {
        Mat2x2 identity{1.0f};
        Mat2x2 rot_left{
            {0.0f, -1.0f},
            {1.0f, 0.0f}
        };

        Vec2 x{1.0f, 0.0f};
        Vec2 neg_x{-1.0f, 0.0f};

        Vec2 y{0.0f, 1.0f};
        Vec2 neg_y{0.0f, -1.0f};

        EXPECT_EQ(identity * x, x);
        EXPECT_EQ((identity * 2.0f) * x, x * 2);

        EXPECT_EQ(rot_left * x, y);
        EXPECT_EQ(rot_left * y, neg_x);
        EXPECT_EQ(rot_left * neg_x, neg_y);
        EXPECT_EQ(rot_left * neg_y, x);
    }

    TEST(Multiplication, Three_by_three) {
        Mat3x3 identity{1.0f};

        Vec3 x{1.0f, 0.0f, 0.0f};
        Vec3 y{0.0f, 1.0f, 0.0f};
        Vec3 z{0.0f, 0.0f, 1.0f};

        EXPECT_EQ(identity * x, x);
        EXPECT_EQ((identity * 2.0f) * x, x * 2);
    }

    TEST(Multiplication, Four_by_four) {
        Mat4x4 identity{1.0f};

        Vec4 w{1.0f, 0.0f, 0.0f, 0.0f};
        Vec4 x{0.0f, 1.0f, 0.0f, 0.0f};
        Vec4 y{0.0f, 0.0f, 1.0f, 0.0f};
        Vec4 z{0.0f, 0.0f, 0.0f, 1.0f};

        EXPECT_EQ(identity * w, w);
    }

}

#endif //AVML_MATRIX_TESTS_HPP
