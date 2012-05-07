#include <imaging/Point2F.h>

namespace ImTrcr {
namespace Imaging {

    Point2F::Point2F(float x, float y) {
        this->x = x;
        this->y = y;
    }

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

}
}