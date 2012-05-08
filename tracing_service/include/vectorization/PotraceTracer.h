#ifndef VECTORIZATION_POTRACE_TRACER_H
#define VECTORIZATION_POTRACE_TRACER_H

#include <vectorization/ITracer.h>
#include <vectorization/IBWRecognizer.h>
#include <vectorization/TracingContext.h>

namespace ImTrcr {
namespace Vectorization {

    //Implements vectorization using Potrace algorithm
    class PotraceTracer : public ITracer {
    public:
        PotraceTracer(IBWRecognizer* bwRecognizer);
        virtual ~PotraceTracer();

        virtual Imaging::VectorImage* Trace(const Imaging::RasterImage& rasterImage) const;
    private:
        //Path decomposition
        const PotraceTracer& DecomposeIntoPaths(TracingContext& ctx) const;

        //From paths to polygons
        const PotraceTracer& BuildPolygons(TracingContext& ctx) const;

        //from polygons to vector outlines
        void TrasformToVectorOutlines(TracingContext& ctx) const;

        IBWRecognizer* bwRecognizer;
    };

}
}

#endif
