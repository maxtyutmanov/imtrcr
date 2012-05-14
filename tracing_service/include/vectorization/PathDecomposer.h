#ifndef VECTORIZATION_PATH_DECOMPOSER_H
#define VECTORIZATION_PATH_DECOMPOSER_H

#include <vectorization/TracingContext.h>

namespace ImTrcr {
namespace Vectorization {

    //Breaks down monochrome image into set of closed paths (that separate black regions from white ones)
    class PathDecomposer {
    public:
        struct Directions {
            enum Enum {
                RIGHT = 0,
                LEFT = 1,
                DOWNWARDS = 2,
                UPWARDS = 3
            };
        };

        PathDecomposer();

        void FindClosedPaths(TracingContext& ctx);
    private:
        void BuildPath(const PotraceImage& img, PotracePath& path);
        void DeleteBlackRegion(PotraceImage& img, const PotracePath& path);
        bool IsDirectionAllowed(const PotraceImage& img, const PotracePath& path, const Directions::Enum direction);

        static const int DIRECTIONS_COUNT = 4;
        PotracePath::Point2 walkDirections[DIRECTIONS_COUNT];
    };

}
}

#endif