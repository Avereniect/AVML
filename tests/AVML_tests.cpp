#include <gtest/gtest.h>

#include <avml/AVML.hpp>

//#include "vector/uvec2f_tests.hpp"
//#include "vector/uvec3f_tests.hpp"
//#include "vector/uvec4f_tests.hpp"

//#include "vector/vec2i_tests.hpp"
//#include "vector/vec3i_tests.hpp"
//#include "vector/vec4i_tests.hpp"

//#include "matrix/Mat2x2f_tests.hpp"
//#include "matrix/Mat3x3f_tests.hpp"
//#include "matrix/Mat4x4f_tests.hpp"

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
