#ifndef IMAGING_POINT2F_H
#define IMAGING_POINT2F_H

namespace ImTrcr {
namespace Imaging {

    //Represents a point in two-dimensional space that has real numbers as its coordinates
    class Point2F {
    public:
        Point2F();
        Point2F(float x, float y);

        float GetX() const;
        void SetX(float x);
        float GetY() const;
        void SetY(float y);

        static Point2F GetMidpoint(const Point2F& first, const Point2F& second);
    private:
        float x;
        float y;
    };

}
}

#endif
