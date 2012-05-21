#ifndef VECTORIZATION_POLYGON_BUILDER_H
#define VECTORIZATION_POLYGON_BUILDER_H

#include <vectorization/TracingContext.h>

#include <utils/TwoDimArray.h>

namespace ImTrcr {
namespace Vectorization {

    //Builds polygons for every path
    class PolygonBuilder {
    public:
        void Polygonize(TracingContext& ctx);

    private:
        //Adds optimal polygon for the given path to the tracing context
        void BuildOptimalPolygon(const PotracePath& path, TracingContext& ctx);

        //returns adjacency matrix for a graph composed of all possible segments in a path
        Utils::TwoDimArray<bool>* PrepareSegmentsGraph(const PotracePath& path);
    };

}
}

#endif