#ifndef VECTORIZATION_POTRACE_PATH_H
#define VECTORIZATION_POTRACE_PATH_H

#include <imaging/Common.h>

#include <vectorization/Point2.h>
#include <vectorization/StraightLineEquation.h>

#include <vector>

namespace ImTrcr {
namespace Vectorization {

    class PotracePath {
    public:
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

        //finds out whether the subpath specified by start index and end index is straight
        bool IsStraight(int i, int j) const;
        //finds out if there is a possible segment from i-th to j-th vertex of path
        bool IsPossibleSegment(int i, int j) const;
    private:
        std::vector<Point2> points;
        bool closed;

        Point2 GetFirstPoint() const;
        Point2 GetCurPoint() const;
        Point2 GetPrevPoint() const;
        bool UsesAllDirections(int i, int j) const;
        bool CanBeApproximatedByLine(int i, int j) const;

        static bool LineIsNotFurtherThan(const StraightLineEquation& lineEq, const Point2& point, float maxDistance);
    };

}
}

#endif