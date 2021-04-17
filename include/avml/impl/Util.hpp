#ifndef AVML_UTIL_HPP
#define AVML_UTIL_HPP

namespace avml {

    constexpr unsigned alignment(unsigned n) {
        switch (n) {
            case 4: return 4;
            case 8: return 8;
            case 12: return 4;
            case 16: return 16;
            case 24: return 8;
            case 32: return 32;
            default: return 0;
        }
    }

}

#endif //AVML_UTIL_HPP
