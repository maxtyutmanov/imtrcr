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
            ClosePath
        };

        static PathCommand MoveToCommand(float x, float y);
        static PathCommand QuadraticBezierToCommand(float x1, float y1, float x2, float y2);
        static PathCommand ClosePathCommand();

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