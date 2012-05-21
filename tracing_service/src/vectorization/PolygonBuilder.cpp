#include <vectorization/PolygonBuilder.h>

#include <utils/Memory.h>
#include <utils/Arithmetic.h>
#include <utils/Graph.h>

#include <limits>
#include <queue>

using namespace std;
using namespace ImTrcr::Utils;

namespace ImTrcr {
namespace Vectorization {

    void PolygonBuilder::Polygonize(TracingContext& ctx) {
        ctx.polygons.clear();
        //number of polygons = number of paths, so let's optimize this a little bit
        ctx.polygons.reserve(ctx.paths.size());

        vector<PotracePath>::const_iterator it;

        for (it = ctx.paths.begin(); it != ctx.paths.end(); ++it) {
            BuildOptimalPolygon(*it, ctx);
        }
    }

    void PolygonBuilder::BuildOptimalPolygon(const PotracePath& path, TracingContext& ctx) {
        const int pathPointsCount = path.GetPoints().size();

        TwoDimArray<bool>* segmentsGraphAjMx = NULL;
        
        try {
            segmentsGraphAjMx = PrepareSegmentsGraph(path);

            vector<int> shortestCycle;
            GraphUtils::FindShortestCycle(*segmentsGraphAjMx, shortestCycle);

            Polygon p(shortestCycle);

            ctx.polygons.push_back(p);
            MemoryUtils::SafeFree(&segmentsGraphAjMx);
        }
        catch (...) {
            MemoryUtils::SafeFree(&segmentsGraphAjMx);
            throw;
        }
    }

    TwoDimArray<bool>* PolygonBuilder::PrepareSegmentsGraph(const PotracePath& path) {
        const int pathPointsCount = path.GetPoints().size();

        //adjancency matrix
        TwoDimArray<bool>* ajMx = new TwoDimArray<bool>(pathPointsCount, pathPointsCount, false);

        for (int i = 0; i < pathPointsCount; ++i) {

            //let's look for possible segments originating from i-th point of path
            int j = ArithmeticUtils::CyclicInc(i, pathPointsCount);

            while (j != i) {
                if (path.IsPossibleSegment(i, j)) {
                    ajMx->At(i, j) = true;
                }

                j = ArithmeticUtils::CyclicInc(j, pathPointsCount);
            }
        }

        return ajMx;
    }

}
}