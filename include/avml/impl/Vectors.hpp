#ifndef AVML_IMPL_VECTORS_HPP
#define AVML_IMPL_VECTORS_HPP

#include <cmath>

#include "Capabilities.hpp"
#include "Shared.hpp"

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

#include "generic/uvec2r.hpp"
#include "generic/uvec3r.hpp"
#include "generic/uvec4r.hpp"

#include "generic/vec2r.hpp"
#include "generic/vec3r.hpp"
#include "generic/vec4r.hpp"

#include "generic/vec2i.hpp"
#include "generic/vec3i.hpp"
#include "generic/vec4i.hpp"

#endif