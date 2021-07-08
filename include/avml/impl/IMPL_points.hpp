#ifndef AVML_IMPL_POINTS_HPP
#define AVML_IMPL_POINTS_HPP

#include "IMPL_capabilities.hpp"

#ifdef AVML_SSE

#else
    #include "default/DEF_pt2f.hpp"
    #include "default/DEF_pt3f.hpp"
    #include "default/DEF_pt4f.hpp"
#endif

#endif //AVML_IMPL_POINTS_HPP
