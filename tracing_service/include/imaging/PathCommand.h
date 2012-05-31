#ifndef IMAGING_PRIMITIVES_PATH_COMMAND_H
#define IMAGING_PRIMITIVES_PATH_COMMAND_H

#include "imaging/Primitive.h"
#include "imaging/Point2F.h"
#include <vector>

namespace ImTrcr {
namespace Imaging {
namespace Primitives {

    class PathCommand {
    public:
        enum Type {
            MoveTo,
            QuadraticBezierTo,
            CubicBezier,
            ClosePath,
            LineTo
        };

        static PathCommand MoveToCommand(const Point2F& p);
        static PathCommand MoveToCommand(float x, float y);
        static PathCommand QuadraticBezierToCommand(const Point2F& p1, const Point2F& p2);
        static PathCommand QuadraticBezierToCommand(float x1, float y1, float x2, float y2);
        static PathCommand CubicBezierCommand(const Point2F& p1, const Point2F& p2, const Point2F& p3);
        static PathCommand CubicBezierCommand(float x1, float y1, float x2, float y2, float x3, float y3);
        static PathCommand ClosePathCommand();
        static PathCommand LineToCommand(const Point2F& p);
        static PathCommand LineToCommand(float x, float y);

        Type GetType() const;
        const std::vector<Point2F>& GetPoints() const;
    private:
        PathCommand(Type type, const std::vector<Point2F>& points);

        Type type;
        std::vector<Point2F> points;
    };

}
}
}

#endif