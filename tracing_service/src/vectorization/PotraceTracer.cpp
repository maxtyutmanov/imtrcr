#pragma once

#include <assert.h>
#include <stdexcept>

#include <vectorization/PotraceTracer.h>
#include <vectorization/PotraceImage.h>
#include <vectorization/TracingContext.h>
#include <vectorization/PathDecomposer.h>
#include <vectorization/PolygonBuilder.h>

#include <imaging/Path.h>

#include <utils/Memory.h>

using namespace ImTrcr::Imaging;
using namespace ImTrcr::Imaging::Primitives;
using namespace ImTrcr::Utils;
using namespace std;

namespace ImTrcr {
namespace Vectorization {

    PotraceTracer::PotraceTracer(IBWRecognizer* bwRecognizer) {
        assert(bwRecognizer != NULL);
        
        this->bwRecognizer = bwRecognizer;
    }

    PotraceTracer::~PotraceTracer() {
        MemoryUtils::SafeFree(&bwRecognizer);
    }

    VectorImage* PotraceTracer::Trace(const RasterImage& rasterImage) const {

        PotraceImage potraceImg(*bwRecognizer, rasterImage);
        VectorImage* pVectorImg = new VectorImage();

        //prepare tracing context
        TracingContext ctx(*pVectorImg, potraceImg);

        try {
            //do tracing
            DecomposeIntoPaths(ctx).BuildPolygons(ctx).TrasformToVectorOutlines(ctx);
        }
        catch (const exception& ex) {
            MemoryUtils::SafeFree(&pVectorImg);
            throw;
        }
        
        return &ctx.vectorImg;
    }

    const PotraceTracer& PotraceTracer::DecomposeIntoPaths(TracingContext& ctx) const {
        PathDecomposer pathDecomposer;
        pathDecomposer.FindClosedPaths(ctx);

        return *this;
    }

    const PotraceTracer& PotraceTracer::BuildPolygons(TracingContext& ctx) const {
        PolygonBuilder b;
        b.Polygonize(ctx);

        return *this;
    }

    void PotraceTracer::TrasformToVectorOutlines(TracingContext& ctx) const {

    }
}
}
