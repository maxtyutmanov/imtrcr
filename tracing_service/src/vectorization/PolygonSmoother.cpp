#include <vectorization/PolygonSmoother.h>
#include <vectorization/StraightLineEquation.h>

#include <utils/Arithmetic.h>

#include <imaging/Square.h>

#include <stdexcept>

using namespace ImTrcr::Imaging::Primitives;
using namespace ImTrcr::Imaging;
using namespace ImTrcr::Utils;
using namespace std;

namespace ImTrcr {
namespace Vectorization {

    void PolygonSmoother::SmoothPolygons(TracingContext& ctx) {

        if (ctx.paths.size() != ctx.polygons.size()) {
            throw logic_error("Number of paths must be equal to number of polygons");
        }

        for (size_t i = 0; i < ctx.paths.size(); ++i) {
            Path* smoothed = SmoothOnePolygon(ctx, ctx.polygons[i]);
            ctx.vectorImg.AddPrimitive(smoothed);
        }
    }

    Path* PolygonSmoother::SmoothOnePolygon(TracingContext& ctx, const Polygon& polygon) {
        const int vertexCount = polygon.GetVertexCount();

        ArgbQuad fillColor = polygon.IsInverted() ? ArgbQuad::White() : ArgbQuad::Black();
        Path* p = new Path(fillColor);

        //move to the start of the resulting path
        Point2F firstCurPoint = polygon[0].ToPoint2F();
        Point2F firstPrevPoint = polygon[ArithmeticUtils::CyclicDec(0, vertexCount)].ToPoint2F();
        Point2F firstPrevMidpoint = Point2F::GetMidpoint(firstPrevPoint, firstCurPoint);
        p->AddCommand(PathCommand::MoveToCommand(firstPrevMidpoint));

        //enumerate all vertices in polygon and approximate each of them

        for (int vertexIndex = 0; vertexIndex < vertexCount; ++vertexIndex) {
            
            Point2F prevPoint = polygon[ArithmeticUtils::CyclicDec(vertexIndex, vertexCount)].ToPoint2F();
            Point2F curPoint = polygon[vertexIndex].ToPoint2F();
            Point2F nextPoint = polygon[ArithmeticUtils::CyclicInc(vertexIndex, vertexCount)].ToPoint2F();

            Point2F prevMidpoint = Point2F::GetMidpoint(prevPoint, curPoint);
            Point2F nextMidpoint = Point2F::GetMidpoint(curPoint, nextPoint);

            CornerSmoothingResult smoothResult = TrySmoothCorner(ctx, prevMidpoint, curPoint, nextMidpoint);

            if (smoothResult.isBezier) {
                //approximate the vertex by cubic bezier curve
                p->AddCommand(PathCommand::CubicBezierCommand(smoothResult.z1, smoothResult.z2, nextMidpoint));
            }
            else {
                //approximate this vertex by two straight line segments

                p->AddCommand(PathCommand::LineToCommand(curPoint));
                p->AddCommand(PathCommand::LineToCommand(nextMidpoint));
            }

        }

        p->AddCommand(PathCommand::ClosePathCommand());

        return p;
    }

    PolygonSmoother::CornerSmoothingResult PolygonSmoother::TrySmoothCorner(TracingContext& ctx, const Point2F& prev, const Point2F& cur, const Point2F& next) {
        bool useBezier = false;
        Point2F z1;
        Point2F z2;

        //draw unit square around cur point
        Square unitSquare(cur, 1.0f);

        StraightLineEquation prev_next(prev, next);

        if (prev_next.IntersectsSquare(unitSquare)) {
            if (ctx.opts.angularity != 0) {
                useBezier = true;
                z1 = Point2F::GetMidpoint(prev, cur);
                z2 = Point2F::GetMidpoint(cur, next);
            }
            else {
                useBezier = false;
            }
        }
        else {
            //draw four lines that are parallel to prev-next line and passes through one of the square's points
            //find the line that is nearest to the prev-next line. Let's call this line L
        
            vector<Point2F> squareCorners = unitSquare.GetCorners();
            StraightLineEquation L = StraightLineEquation::ParallelTo(prev_next, squareCorners[0]);
            float shortestDistance = StraightLineEquation::GetDistanceBetweenLines(prev_next, L);

            for (size_t i = 1; i < squareCorners.size(); ++i) {
                StraightLineEquation line = StraightLineEquation::ParallelTo(prev_next, squareCorners[i]);

                float distance = StraightLineEquation::GetDistanceBetweenLines(prev_next, line);

                if (distance < shortestDistance) {
                    L = line;
                    shortestDistance = distance;
                }
            }

            //find the points in which L intersects prev-cur and cur-next lines. Name this points z1 and z2

            StraightLineEquation prev_cur(prev, cur);
            StraightLineEquation cur_next(cur, next);

            z1 = StraightLineEquation::GetIntersectionPoint(L, prev_cur);

            float gamma = Point2F::GetDistance(prev, z1) / Point2F::GetDistance(prev, cur);
            float alpha = gamma * 1.333f;

            float smoothCoeff = (100.0f - ctx.opts.angularity) / 100.0f;
            float alphaMax = 1.3334f * smoothCoeff;

            if (alpha < alphaMax) {
                z2 = StraightLineEquation::GetIntersectionPoint(L, cur_next);
                useBezier = true;
            }
            else {
                useBezier = false;
            }
        }

        //return CornerSmoothingResult::();

        if (useBezier) {
            return CornerSmoothingResult::Bezier(z1, z2);
            //return CornerSmoothingResult::StraightLines();
        }
        else {
            return CornerSmoothingResult::StraightLines();
        }

        //find the gamma and alpha values

        //decide how to approximate the given corner - by two straight lines or by cubic bezier curve
    }

}
}
