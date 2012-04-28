#pragma once

#include <imaging/VectorImage.h>
#include <imaging/RasterImage.h>

namespace ImTrcr {
namespace Vectorization {

    //Encapsulates the vectorization logic
    class ITracer {
    public:
        virtual Imaging::VectorImage* Trace(const Imaging::RasterImage& rasterImage) = 0;
        virtual ~ITracer() {}
    };

}
}
