#include <imaging/PathSerializer.h>
#include <utils/String.h>
#include <iomanip>

using namespace std;
using namespace ImTrcr::Imaging::Primitives;
using namespace ImTrcr::Utils;

namespace ImTrcr {
namespace Imaging {

    PathSerializer::PathSerializer() {
        result << fixed << setprecision(2);
    }

    void PathSerializer::MoveTo(const PathCommand& cmd) {
        result << "M ";
        WritePointsSequence(cmd);
    }

    void PathSerializer::QuadraticBezier(const PathCommand& cmd) {
        result << "Q ";
        WritePointsSequence(cmd);
    }

    void PathSerializer::CubicBezier(const PathCommand& cmd) {
        result << "C ";

        WritePointsSequence(cmd);
    }

    void PathSerializer::ClosePath() {
        result << "Z ";
    }

    void PathSerializer::LineTo(const PathCommand& cmd) {
        result << "L ";
        WritePointsSequence(cmd);
    }

    string PathSerializer::GetResult() const {
        string trimmed = result.str();
        StringUtils::TrimEnd(trimmed);
        return trimmed;
    }

    void PathSerializer::WritePointsSequence(const PathCommand& cmd) {
        const vector<Point2F>& points = cmd.GetPoints();
        vector<Point2F>::const_iterator it;

        for (it = points.begin(); it != points.end(); ++it) {
            WritePoint(*it);
        }
    }

    void PathSerializer::WritePoint(const Point2F& point) {
        result << point.GetX() << ' ' << point.GetY() << ' ';
    }

}
}