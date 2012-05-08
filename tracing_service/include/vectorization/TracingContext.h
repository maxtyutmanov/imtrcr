#ifndef VECTORIZATION_TRACING_CONTEXT_H
#define VECTORIZATION_TRACING_CONTEXT_H

#include <imaging/VectorImage.h>

#include <vectorization/PotraceImage.h>
#include <vectorization/PotracePath.h>

#include <vector>

namespace ImTrcr {
namespace Vectorization {

    struct TracingContext {
        TracingContext(Imaging::VectorImage& vectorImg, PotraceImage& potraceImg)
            : vectorImg(vectorImg), potraceImg(potraceImg) {}

        Imaging::VectorImage& vectorImg;
        PotraceImage& potraceImg;
        std::vector<PotracePath> paths;
    };

}
}

#endif