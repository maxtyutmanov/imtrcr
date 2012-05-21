#ifndef VECTORIZATION_STRAIGHT_LINE_EQUATION_H
#define VECTORIZATION_STRAIGHT_LINE_EQUATION_H

#include <vectorization/Point2.h>

namespace ImTrcr {
namespace Vectorization {

    class StraightLineEquation {
    public:
        StraightLineEquation(float x1, float y1, float x2, float y2);

        float operator()(float x, float y) const;

    private:
        float a;
        float b;
        float c;
    };

}
}

#endif