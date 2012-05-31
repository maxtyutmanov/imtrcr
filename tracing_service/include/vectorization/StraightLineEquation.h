#ifndef VECTORIZATION_STRAIGHT_LINE_EQUATION_H
#define VECTORIZATION_STRAIGHT_LINE_EQUATION_H

#include <imaging/Point2F.h>
#include <imaging/Square.h>

namespace ImTrcr {
namespace Vectorization {

    class StraightLineEquation {
    public:
        StraightLineEquation(float x1, float y1, float x2, float y2);
        StraightLineEquation(const Imaging::Point2F& first, const Imaging::Point2F& second);

        //Creates the equation of line that is parallel to specified line and passes through the point p
        static StraightLineEquation ParallelTo(const StraightLineEquation& line, const Imaging::Point2F& p);

        //Calculates the distance between two parallel lines
        static float GetDistanceBetweenLines(const StraightLineEquation& first, const StraightLineEquation& second);

        //Gets value of the formula (Ax + By + C)
        float operator()(float x, float y) const;

        bool IntersectsSquare(const Imaging::Square& square) const;

        static Imaging::Point2F GetIntersectionPoint(const StraightLineEquation& l1, const StraightLineEquation& l2);

        float GetA() const;
        float GetB() const;
        float GetC() const;
    private:
        void Init(float x1, float y1, float x2, float y2);

        StraightLineEquation(float a, float b, float c);

        //Gets value of the formula (Ax + By + C)
        float LeftPart(float x, float y) const;
        float LeftPart(const Imaging::Point2F& point) const;

        Imaging::Point2F GetRandomPoint() const;

        float a;
        float b;
        float c;
    };

}
}

#endif