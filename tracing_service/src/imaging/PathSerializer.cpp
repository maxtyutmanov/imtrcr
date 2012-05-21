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

    //TODO: DRY!

    void PathSerializer::MoveTo(const PathCommand& cmd) {
        result << "M ";

        const vector<Point2F>& points = cmd.GetPoints();
        vector<Point2F>::const_iterator it;

        for (it = points.begin(); it != points.end(); ++it) {
            WritePoint(*it);
        }
    }

    void PathSerializer::QuadraticBezier(const PathCommand& cmd) {
        result << "Q ";
        const vector<Point2F>& points = cmd.GetPoints();
        vector<Point2F>::const_iterator it;

        for (it = points.begin(); it != points.end(); ++it) {
            WritePoint(*it);
        }
    }

    void PathSerializer::ClosePath() {
        result << "Z ";
    }

    void PathSerializer::LineTo(const PathCommand& cmd) {
        result << "L ";

        const vector<Point2F>& points = cmd.GetPoints();
        vector<Point2F>::const_iterator it;

        for (it = points.begin(); it != points.end(); ++it) {
            WritePoint(*it);
        }
    }

    string PathSerializer::GetResult() const {
        string trimmed = result.str();
        Utils::StringUtils::TrimEnd(trimmed);
        return trimmed;
    }

    void PathSerializer::WritePoint(const Point2F& point) {
        result << point.GetX() << ' ' << point.GetY() << ' ';
    }

}
}