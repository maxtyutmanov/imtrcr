#include <imaging/Square.h>

using namespace std;

namespace ImTrcr {
namespace Imaging {

    Square::Square(const Point2F& center, float maxDistance)
        : center(center), maxDistance(maxDistance) {}

    Point2F Square::LT() const {
        return Point2F(center.GetX() - maxDistance, center.GetY() - maxDistance);
    }

    Point2F Square::LB() const {
        return Point2F(center.GetX() - maxDistance, center.GetY() + maxDistance);
    }

    Point2F Square::RT() const {
        return Point2F(center.GetX() + maxDistance, center.GetY() - maxDistance);
    }

    Point2F Square::RB() const {
        return Point2F(center.GetX() + maxDistance, center.GetY() + maxDistance);
    }

    vector<Point2F> Square::GetCorners() const {
        vector<Point2F> v;
        v.reserve(4);

        v.push_back(LT());
        v.push_back(LB());
        v.push_back(RT());
        v.push_back(RB());

        return v;
    }

}
}