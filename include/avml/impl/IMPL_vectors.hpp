#ifndef AVML_IMPL_VECTORS_HPP
#define AVML_IMPL_VECTORS_HPP

#include <cmath>

#include "IMPL_capabilities.hpp"

#if defined(AVML_SSE2)
    #include "x86/x86_uvec2f.ipp"
#else
    #include "default/DEF_uvec2f.ipp"
    #include "default/DEF_uvec3f.ipp"
    #include "default/DEF_uvec4f.ipp"

    #include "default/DEF_vec2f.ipp"
    #include "default/DEF_vec3f.ipp"
    #include "default/DEF_vec4f.ipp"
#endif

#endif //AVML_IMPL_VECTORS_HPP
