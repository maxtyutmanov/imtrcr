#include <vectorization/PotracePath.h>
#include <vectorization/StraightLineEquation.h>

#include <utils/Arithmetic.h>

#include <map>
#include <algorithm>
#include <stdexcept>

using namespace ImTrcr::Imaging;
using namespace ImTrcr::Utils;
using namespace std;

namespace ImTrcr {
namespace Vectorization {

    PotracePath::PotracePath()
        : closed(false) {}

    image_size_t PotracePath::StartX() const {
        return GetFirstPoint().x;
    }

    image_size_t PotracePath::StartY() const {
        return GetFirstPoint().y;
    }

    image_size_t PotracePath::CurX() const {
        return GetCurPoint().x;
    }

    image_size_t PotracePath::CurY() const {
        return GetCurPoint().y;
    }

    image_size_t PotracePath::PrevX() const {
        return GetPrevPoint().x;
    }

    image_size_t PotracePath::PrevY() const {
        return GetPrevPoint().y;
    }

    void PotracePath::AddPoint(image_size_t x, image_size_t y) {
        points.push_back(Point2(x, y));
    }

    const vector<Point2>& PotracePath::GetPoints() const {
        return points;
    }

    bool PotracePath::IsClosed() const {
        return closed;
    }

    vector<Point2> PotracePath::GetInteriorPoints() const {
        if (!this->IsClosed()) {
            throw logic_error("Cannot find interior of a non-closed path");
        }

        //the interior of a path is broken down into so-called layers - lines with height of 1 px.
        //This variable will contain a mapping from layers (y coordinates) to x coordinates of intersection points
        map< image_size_t, vector<image_size_t> > layers;

        //group all intersection points in a path by their y coordinate
        long numberOfPoints = points.size();
        for (long i = 0; i < points.size(); ++i) {
            Point2 prevPoint = points[ArithmeticUtils::CyclicDec(i, numberOfPoints)];
            Point2 curPoint = points[i];
            Point2 nextPoint = points[ArithmeticUtils::CyclicInc(i, numberOfPoints)];

            //there is an edge that intersects the layer between y and (y + 1) coordinate lines
            if (prevPoint.x == curPoint.x && prevPoint.y == curPoint.y + 1 ||
                nextPoint.x == curPoint.x && nextPoint.y == curPoint.y + 1) {

                layers[curPoint.y].push_back(curPoint.x);
            }
        }

        vector<Point2> interiorPixelsCoords;

        //find interior pixels

        map< image_size_t, vector<image_size_t> >::iterator layersIt;
        for (layersIt = layers.begin(); layersIt != layers.end(); ++layersIt) {
            //get y coordinate of the layer
            image_size_t yCoord = layersIt->first;

            //sort layer's intersection points
            vector<image_size_t>& layerPoints = layersIt->second;
            sort(layerPoints.begin(), layerPoints.end());

            //enumerate all black stripes in the layer and add them to output
            for (image_size_t i = 0; i < layerPoints.size() - 1; i += 2) {
                image_size_t curX = layerPoints[i];
                image_size_t nextX = layerPoints[i + 1];

                for (image_size_t x = curX; x < nextX; ++x) {
                    interiorPixelsCoords.push_back(Point2(x, yCoord));
                }
            }
        }

        return interiorPixelsCoords;
    }

    bool PotracePath::IsEdgeInPath(image_size_t x1, image_size_t y1, image_size_t x2, image_size_t y2) const {
        for (int i = points.size() - 1; i > 0; --i) {
            Point2 nextPoint = points[i];
            Point2 prevPoint = points[i - 1];

            if (prevPoint.x == x1 && prevPoint.y == y1 && nextPoint.x == x2 && nextPoint.y == y2 ||
                prevPoint.x == x2 && prevPoint.y == y2 && nextPoint.x == x1 && nextPoint.y == y1) {

                return true;
            }
        }

        return false;
    }

    void PotracePath::Augment(int moveX, int moveY) {
        if (this->IsClosed()) {
            throw logic_error("Cannot augment closed path");
        }

        Point2 curPoint = GetCurPoint();
        Point2 nextPoint(curPoint.x + moveX, curPoint.y + moveY);

        Point2 firstPoint = GetFirstPoint();

        if (firstPoint == nextPoint) {
            closed = true;
        }
        else {
            this->AddPoint(nextPoint.x, nextPoint.y);
        }
    }

    #pragma region Straightness testing algorithm

    bool PotracePath::IsStraight(int i, int j) const {
        int subpathLength = ArithmeticUtils::CyclicDifference(j, i, (int)points.size());

        if (subpathLength <= 3) {
            return true;
        }
        else {
            return !UsesAllDirections(i, j) && CanBeApproximatedByLine(i, j);
        }
    }

    bool PotracePath::UsesAllDirections(int i, int j) const {
        //direction key = 2*dx + dy
        map<int, bool> directionsMap;
        directionsMap[-2] = false;
        directionsMap[2] = false;
        directionsMap[-1] = false;
        directionsMap[1] = false;

        int k = i;

        for (int k = i; k != j; k = ArithmeticUtils::CyclicInc(k, (int)points.size())) {
            Point2 cur = points[k];
            Point2 next = points[ArithmeticUtils::CyclicInc(k, (int)points.size())];

            int moveX = next.x - cur.x;
            int moveY = next.y - cur.y;

            //direction key = 2*dx + dy
            directionsMap[moveX * 2 + moveY] = true;
        }

        map<int, bool>::const_iterator it;
        for (it = directionsMap.begin(); it != directionsMap.end(); ++it) {
            if (!it->second) {
                return false;
            }
        }

        return true;
    }

    bool PotracePath::CanBeApproximatedByLine(int i, int j) const {
        Point2 firstP = points[i];
        Point2 lastP = points[j];

        StraightLineEquation f(firstP.x, firstP.y, lastP.x, lastP.y);

        //check internal points of path
        int pointIndex = ArithmeticUtils::CyclicInc(i, (int)points.size());
        while (pointIndex != j) {
            //max distance from approximating line segment to any of path's points is 1 px
            bool ok = LineIsNotFurtherThan(f, points[pointIndex], 1);

            if (!ok) {
                return false;
            }

            pointIndex = ArithmeticUtils::CyclicInc(pointIndex, (int)points.size());
        }

        return true;
    }

    bool PotracePath::LineIsNotFurtherThan(const StraightLineEquation& lineEq, const Point2& point, float maxDistance) {
        float fLeftTop = lineEq(point.x - maxDistance, point.y - maxDistance);
        float fLeftBottom = lineEq(point.x - maxDistance, point.y + maxDistance);
        float fRightTop = lineEq(point.x + maxDistance, point.y - maxDistance);
        float fRightBottom = lineEq(point.x + maxDistance, point.y + maxDistance);

        if (fLeftTop == 0 || fLeftBottom == 0 || fRightTop == 0 || fRightBottom == 0) {
            return true;
        }
        else if (
            fLeftTop > 0 && fLeftBottom > 0 && fRightTop > 0 && fRightBottom > 0 ||
            fLeftTop < 0 && fLeftBottom < 0 && fRightTop < 0 && fRightBottom < 0) {

            return false;
        }
        else {
            return true;
        }
    }

    #pragma endregion

    bool PotracePath::IsPossibleSegment(int i, int j) const {
        int cyclicDiff = ArithmeticUtils::CyclicDifference(j, i, (int)points.size());

        if (cyclicDiff <= points.size() - 3) {
            int prevPointIndex = ArithmeticUtils::CyclicDec(i, (int)points.size());
            int nextPointIndex = ArithmeticUtils::CyclicInc(j, (int)points.size());

            return IsStraight(prevPointIndex, nextPointIndex);
        }
        else {
            return false;
        }
    }

    Point2 PotracePath::GetFirstPoint() const {
        if (points.size() == 0) {
            throw logic_error("There's no first point to get - there are no points in path yet!");
        }

        return points[0];
    }

    Point2 PotracePath::GetCurPoint() const {
        if (points.size() == 0) {
            throw logic_error("There's no current point to get - there are no points in path yet!");
        }

        return points[points.size() - 1];
    }

    Point2 PotracePath::GetPrevPoint() const {
        if (points.size() < 2) {
            throw logic_error("There's no previous point in the path. There are less than two points in path.");
        }

        return points[points.size() - 2];
    }
}
}
