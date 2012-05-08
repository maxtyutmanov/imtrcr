#ifndef VECTORIZATION_ITRACER_H
#define VECTORIZATION_ITRACER_H

#include <imaging/VectorImage.h>
#include <imaging/RasterImage.h>

namespace ImTrcr {
namespace Vectorization {

    //Encapsulates the vectorization logic
    class ITracer {
    public:
        virtual Imaging::VectorImage* Trace(const Imaging::RasterImage& rasterImage) const = 0;
        virtual ~ITracer() {}
    };

}
}

#endif
