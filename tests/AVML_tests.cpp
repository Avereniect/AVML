#include <gtest/gtest.h>

#include "matrix/Mat2x2f_tests.hpp"
#include "matrix/Mat3x3f_tests.hpp"
#include "matrix/Mat4x4f_tests.hpp"

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
