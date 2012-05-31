#include <vectorization/StraightLineEquation.h>

#include <utils/Arithmetic.h>

using namespace ImTrcr::Imaging;
using namespace ImTrcr::Utils;

namespace ImTrcr {
namespace Vectorization {

    StraightLineEquation::StraightLineEquation(const Point2F& first, const Point2F& second) {
        Init(first.GetX(), first.GetY(), second.GetX(), second.GetY());
    }

    StraightLineEquation::StraightLineEquation(float x1, float y1, float x2, float y2) {
        Init(x1, y1, x2, y2);
    }

    StraightLineEquation::StraightLineEquation(float a, float b, float c)
        : a(a), b(b), c(c) {}

    float StraightLineEquation::operator()(float x, float y) const {
        return LeftPart(x, y);
    }

    void StraightLineEquation::Init(float x1, float y1, float x2, float y2) {
        a = y2 - y1;
        b = x1 - x2;
        c = x2 * y1 - x1 * y2;
    }

    StraightLineEquation StraightLineEquation::ParallelTo(const StraightLineEquation& line, const Point2F& p) {
        float a, b, c;

        if (!ArithmeticUtils::RoughlyEq(line.b, 0.0f)) {
            a = line.a / line.b;
            b = 1.0f;
            c = - (a * p.GetX() + p.GetY());
        }
        else {
            a = 1.0f;
            b = line.b / line.a;
            c = - (p.GetX() + b * p.GetY());
        }

        return StraightLineEquation(a, b, c);
    }

    float StraightLineEquation::GetDistanceBetweenLines(const StraightLineEquation& l1, const StraightLineEquation& l2) {
        //random point on the l2 line
        Point2F p = l2.GetRandomPoint();

        return std::abs(l1.a * p.GetX() + l1.b * p.GetY() + l1.c) / sqrt(l1.a * l1.a + l1.b * l1.b);
    }

    bool StraightLineEquation::IntersectsSquare(const Imaging::Square& square) const {
        float fLeftTop = LeftPart(square.LT());
        float fLeftBottom = LeftPart(square.LB());
        float fRightTop = LeftPart(square.RT());
        float fRightBottom = LeftPart(square.RB());

        //TODO: it's not a very good thing to compare floating point numbers with == operator

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

    float StraightLineEquation::LeftPart(const Point2F& point) const {
        return LeftPart(point.GetX(), point.GetY());
    }

    float StraightLineEquation::LeftPart(float x, float y) const {
        return a * x + b * y + c;
    }

    Point2F StraightLineEquation::GetIntersectionPoint(const StraightLineEquation& l1, const StraightLineEquation& l2) {
        //solve the system of linear equations using Cramer's rule

        float det = l1.a * l2.b - l2.a * l1.b;
        float detX = l1.b * l2.c - l2.b * l1.c;
        float detY = l2.a * l1.c - l1.a * l2.c;

        return Point2F(detX / det, detY / det);
    }

    float StraightLineEquation::GetA() const {
        return a;
    }

    float StraightLineEquation::GetB() const {
        return b;
    }

    float StraightLineEquation::GetC() const {
        return c;
    }

    Point2F StraightLineEquation::GetRandomPoint() const {
        if (!ArithmeticUtils::RoughlyEq(a, 0.0f)) {
            //a != 0

            return Point2F(-c / a, 0.0f);
        }
        else {
            //b != 0

            return Point2F(0.0, -c / b);
        }
    }
    
}
}
