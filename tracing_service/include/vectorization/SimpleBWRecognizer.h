#ifndef VECTORIZATION_SIMPLE_BW_RECOGNIZER_H
#define VECTORIZATION_SIMPLE_BW_RECOGNIZER_H

#include <vectorization/IBWRecognizer.h>

namespace ImTrcr {
namespace Vectorization {

    class SimpleBWRecognizer : public IBWRecognizer {
    public:
        virtual PixelColor::Enum GetPotraceColor(Imaging::ArgbQuad actualColor) const;
    };

}
}

#endif