#ifndef IMAGING_SQUARE_H
#define IMAGING_SQUARE_H

#include <imaging/Point2F.h>
#include <vector>

namespace ImTrcr {
namespace Imaging {

    class Square {
    public:
        Square(const Point2F& center, float maxDistance);

        Point2F LT() const;
        Point2F LB() const;
        Point2F RT() const;
        Point2F RB() const;

        std::vector<Point2F> GetCorners() const;
    private:
        Point2F center;
        float maxDistance;
    };

}
}

#endif