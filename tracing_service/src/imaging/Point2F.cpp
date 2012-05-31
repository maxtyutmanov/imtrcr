#include <imaging/Point2F.h>

#include <cmath>

namespace ImTrcr {
namespace Imaging {

    Point2F::Point2F()
        : x(0.0f), y(0.0f) {}

    Point2F::Point2F(float x, float y) 
        : x(x), y(y) { }

    float Point2F::GetX() const {
        return x;
    }

    float Point2F::GetY() const {
        return y;
    }

    void Point2F::SetX(float x) {
        this->x = x;
    }

    void Point2F::SetY(float y) {
        this->y = y;
    }

    Point2F Point2F::GetMidpoint(const Point2F& first, const Point2F& second) {
        return Point2F((first.GetX() + second.GetX()) / 2.0f, (first.GetY() + second.GetY()) / 2.0f);
    }

    float Point2F::GetDistance(const Point2F& p1, const Point2F& p2) {
        return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
    }
}
}