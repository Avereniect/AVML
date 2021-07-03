#ifndef AVML_AFFINE3DF_TESTS_HPP
#define AVML_AFFINE3DF_TESTS_HPP

#include <avml/Transforms.hpp>

#include <gtest/gtest.h>

namespace avml_tests {

    using namespace avml;

    TEST(Affine3Df, Default_constructor) {
        Affine3Df affine{};
        Vec3f x{1.0f, 2.0f, 3.0f};
        EXPECT_EQ(affine(x), x);
    }

    TEST(Affine3Df, Variadic_transform_constructor) {
        Affine3Df affine{Translation3Df{1.0f, 1.0f, 1.0f}};
        Pt3f x{0.0f, 0.0f, 0.0f};
        Pt3f y{1.0f, 1.0f, 1.0f};

        Pt3f z = affine(x);
        EXPECT_EQ(z, y);
    }

}

#endif //AVML_AFFINE3DF_TESTS_HPP
