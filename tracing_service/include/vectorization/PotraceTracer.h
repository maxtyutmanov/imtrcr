#ifndef VECTORIZATION_POTRACE_TRACER_H
#define VECTORIZATION_POTRACE_TRACER_H

#include "vectorization/ITracer.h"

namespace ImTrcr {
namespace Vectorization {

    //Implements vectorization using Potrace algorithm
    class PotraceTracer : public ITracer {
    public:
        virtual Imaging::VectorImage* Trace(const Imaging::RasterImage& rasterImage);
    };

}
}

#endif
