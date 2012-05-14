#include <imaging/PathCommand.h>

using namespace std;
using namespace ImTrcr::Utils;

namespace ImTrcr {
namespace Imaging {
namespace Primitives {

    PathCommand::PathCommand(Type type, const std::vector<Point2F>& points) {
        this->type = type;
        this->points = points;
    }

    PathCommand::Type PathCommand::GetType() const {
        return type;
    }

    const vector<Point2F>& PathCommand::GetPoints() const {
        return points;
    }

    PathCommand PathCommand::MoveToCommand(float x, float y) {
        vector<Point2F> points;
        points.push_back(Point2F(x, y));

        return PathCommand(PathCommand::MoveTo, points);
    }

    PathCommand PathCommand::QuadraticBezierToCommand(float x1, float y1, float x2, float y2) {
        vector<Point2F> points;

        points.push_back(Point2F(x1, y1));
        points.push_back(Point2F(x2, y2));

        return PathCommand(PathCommand::QuadraticBezierTo, points);
    }

    PathCommand PathCommand::ClosePathCommand() {
        return PathCommand(PathCommand::ClosePath, vector<Point2F>());
    }
}
}
}