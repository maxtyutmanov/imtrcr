#ifndef VECTORIZATION_POTRACE_PATH_H
#define VECTORIZATION_POTRACE_PATH_H

#include <imaging/Common.h>

#include <vector>
#include <assert.h>

namespace ImTrcr {
namespace Vectorization {

    class PotracePath {
    public:
        struct Point2 {
            Point2(Imaging::image_size_t x, Imaging::image_size_t y)
                : x(x), y(y) { }

            Imaging::image_size_t x;
            Imaging::image_size_t y;
        };

        Imaging::image_size_t StartX() const {
            return GetFirstPoint().x;
        }

        Imaging::image_size_t StartY() const {
            return GetFirstPoint().y;
        }

        Imaging::image_size_t CurX() const {
            return GetLastPoint().x;
        }

        Imaging::image_size_t CurY() const {
            return GetLastPoint().y;
        }

        void AddPoint(Imaging::image_size_t x, Imaging::image_size_t y) {
            points.push_back(Point2(x, y));
        }

        const std::vector<Point2>& GetPoints() const {
            return points;
        }

    private:
        std::vector<Point2> points;

        Point2 GetFirstPoint() const {
            assert(points.size() != 0);

            return points[0];
        }

        Point2 GetLastPoint() const {
            assert(points.size() != 0);

            return points[points.size() - 1];
        }
    };

}
}

#endif