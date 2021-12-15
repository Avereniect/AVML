//
// Created by avereniect on 12/15/21.
//

namespace avml {

    template<>
    class alignas(alignof(float) * 1) Vector2R<float> {
    public:

        using scalar = float;

        static constexpr unsigned width = 2;

        //=================================================
        // Creation functions
        //=================================================

        AVML_FINL static Vector2R read(const float* p) {

        }

    private:


    };

}
