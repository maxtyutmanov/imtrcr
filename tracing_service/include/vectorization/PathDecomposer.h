#ifndef VECTORIZATION_PATH_DECOMPOSER_H
#define VECTORIZATION_PATH_DECOMPOSER_H

#include <vectorization/TracingContext.h>

namespace ImTrcr {
namespace Vectorization {

    //Breaks down monochrome image into set of closed paths (that separate black regions from white ones)
    class PathDecomposer {
    public:
        void FindClosedPaths(TracingContext& ctx);
    private:
        void AugmentPath(const PotraceImage& img, PotracePath& path);
        void DeleteBlackRegion(PotraceImage& img, const PotracePath& path);
    };

}
}

#endif