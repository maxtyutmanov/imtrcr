#ifndef VECTORIZATION_IBW_RECOGNIZER_H
#define VECTORIZATION_IBW_RECOGNIZER_H

#include <vectorization/PixelColor.h>
#include <imaging/ArgbQuad.h>

namespace ImTrcr {
namespace Vectorization {

    //Break down all colors of an original raster image into black and white
    //according to some rule (black-white recognizer)
    class IBWRecognizer {
    public:
        virtual PixelColor::Enum GetPotraceColor(Imaging::ArgbQuad actualColor) const = 0;
    };

}
}

#endif