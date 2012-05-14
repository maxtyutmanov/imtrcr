#ifndef VECTORIZATION_POTRACE_PATH_H
#define VECTORIZATION_POTRACE_PATH_H

#include <imaging/Common.h>

#include <vector>

namespace ImTrcr {
namespace Vectorization {

    class PotracePath {
    public:
        struct Point2 {
            Point2() 
                : x(0), y(0) { }

            Point2(Imaging::image_size_t x, Imaging::image_size_t y)
                : x(x), y(y) { }

            bool operator == (const Point2& right) const {
                return this->x == right.x && this->y == right.y;
            }

            Imaging::image_size_t x;
            Imaging::image_size_t y;
        };

        PotracePath();

        Imaging::image_size_t StartX() const;
        Imaging::image_size_t StartY() const;
        Imaging::image_size_t CurX() const;
        Imaging::image_size_t CurY() const;
        Imaging::image_size_t PrevX() const;
        Imaging::image_size_t PrevY() const;
        void AddPoint(Imaging::image_size_t x, Imaging::image_size_t y);
        const std::vector<Point2>& GetPoints() const;
        bool IsClosed() const;

        //Finds the set of pixels that are located inside the path (when it's closed).
        //Each point in result refers to pixel located to the left below it.
        std::vector<Point2> GetInteriorPoints() const;

        //finds out whether specified edge is in the path. Doesn't consider direction of edge.
        bool IsEdgeInPath(Imaging::image_size_t x1, Imaging::image_size_t y1, Imaging::image_size_t x2, Imaging::image_size_t y2) const;

        void Augment(int moveX, int moveY);
    private:
        std::vector<Point2> points;
        bool closed;

        Point2 GetFirstPoint() const;
        Point2 GetCurPoint() const;
        Point2 GetPrevPoint() const;
    };

}
}

#endif