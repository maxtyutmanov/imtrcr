#ifndef VECTORIZATION_POLYGON_SMOOTHER_H
#define VECTORIZATION_POLYGON_SMOOTHER_H

#include <imaging/Point2F.h>
#include <imaging/Path.h>

#include <vectorization/TracingContext.h>

namespace ImTrcr {
namespace Vectorization {

    class PolygonSmoother {
    public:
        void SmoothPolygons(TracingContext& ctx);
    private:
        struct CornerSmoothingResult {
            static CornerSmoothingResult Bezier(const Imaging::Point2F& z1, const Imaging::Point2F& z2) {
                return CornerSmoothingResult(true, z1, z2);
            }

            static CornerSmoothingResult StraightLines() {
                return CornerSmoothingResult(false, Imaging::Point2F(0.0f, 0.0f), Imaging::Point2F(0.0f, 0.0f));
            }

            bool isBezier;
            Imaging::Point2F z1;
            Imaging::Point2F z2;

        private:
            CornerSmoothingResult(bool isBezier, const Imaging::Point2F& z1, const Imaging::Point2F& z2) 
                : isBezier(isBezier), z1(z1), z2(z2) { }
        };

        Imaging::Primitives::Path* SmoothOnePolygon(const Polygon& polygon);
        CornerSmoothingResult TrySmoothCorner(const Imaging::Point2F& prev, const Imaging::Point2F& cur, const Imaging::Point2F& next);

        
    };

}
}

#endif