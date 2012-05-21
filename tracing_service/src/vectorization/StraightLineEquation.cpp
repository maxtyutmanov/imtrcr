#include <vectorization/StraightLineEquation.h>

namespace ImTrcr {
namespace Vectorization {

    StraightLineEquation::StraightLineEquation(float x1, float y1, float x2, float y2) 
        : a(y2 - y1), b(x1 - x2), c(x2 * y1 - x1 * y2) {}

    float StraightLineEquation::operator()(float x, float y) const {
        return a * x + b * y + c;
    }
    
}
}