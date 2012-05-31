#ifndef IMAGING_PATH_SERIALIZER_H
#define IMAGING_PATH_SERIALIZER_H

#include <sstream>
#include <vector>
#include <imaging/Point2F.h>
#include <imaging/PathCommand.h>

namespace ImTrcr {
namespace Imaging {

    class PathSerializer {
    public:
        PathSerializer();
        void MoveTo(const Imaging::Primitives::PathCommand& cmd);
        void QuadraticBezier(const Imaging::Primitives::PathCommand& cmd);
        void CubicBezier(const Imaging::Primitives::PathCommand& cmd);
        void ClosePath();
        void LineTo(const Imaging::Primitives::PathCommand& cmd);
        std::string GetResult() const;

    private:
        void WritePointsSequence(const Imaging::Primitives::PathCommand& cmd);
        void WritePoint(const ImTrcr::Imaging::Point2F& point);
        std::ostringstream result;
    };

}
}

#endif