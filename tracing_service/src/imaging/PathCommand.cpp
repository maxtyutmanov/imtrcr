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
        return MoveToCommand(Point2F(x, y));
    }

    PathCommand PathCommand::MoveToCommand(const Point2F& p) {
        vector<Point2F> points;
        points.push_back(p);

        return PathCommand(PathCommand::MoveTo, points);
    }

    PathCommand PathCommand::QuadraticBezierToCommand(float x1, float y1, float x2, float y2) {
        return QuadraticBezierToCommand(Point2F(x1, y1), Point2F(x2, y2));
    }

    PathCommand PathCommand::QuadraticBezierToCommand(const Point2F& p1, const Point2F& p2) {
        vector<Point2F> points;

        points.push_back(p1);
        points.push_back(p2);

        return PathCommand(PathCommand::QuadraticBezierTo, points);
    }

    PathCommand PathCommand::CubicBezierCommand(float x1, float y1, float x2, float y2, float x3, float y3) {
       return CubicBezierCommand(Point2F(x1, y1), Point2F(x2, y2), Point2F(x3, y3));
    }

    PathCommand PathCommand::CubicBezierCommand(const Point2F& p1, const Point2F& p2, const Point2F& p3) {
        vector<Point2F> points;

        points.push_back(p1);
        points.push_back(p2);
        points.push_back(p3);

        return PathCommand(PathCommand::CubicBezier, points);
    }

    PathCommand PathCommand::ClosePathCommand() {
        return PathCommand(PathCommand::ClosePath, vector<Point2F>());
    }

    PathCommand PathCommand::LineToCommand(float x, float y) {
        return LineToCommand(Point2F(x, y));
    }

    PathCommand PathCommand::LineToCommand(const Point2F& p) {
        vector<Point2F> points;
        points.push_back(p);

        return PathCommand(PathCommand::LineTo, points);
    }
}
}
}