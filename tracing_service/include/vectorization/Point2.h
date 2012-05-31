#ifndef VECTORIZATION_POINT2_H
#define VECTORIZATION_POINT2_H

#include <imaging/Common.h>
#include <imaging/Point2F.h>

namespace ImTrcr {
namespace Vectorization {

    struct Point2 {
        Point2() 
            : x(0), y(0) { }

        Point2(Imaging::image_size_t x, Imaging::image_size_t y)
            : x(x), y(y) { }

        bool operator == (const Point2& right) const {
            return this->x == right.x && this->y == right.y;
        }

        Imaging::Point2F ToPoint2F() const {
            return Imaging::Point2F(x, y);
        }

        Imaging::image_size_t x;
        Imaging::image_size_t y;
    };

}
}

#endif