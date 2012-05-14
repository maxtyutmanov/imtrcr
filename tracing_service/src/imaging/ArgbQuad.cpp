#include <imaging/ArgbQuad.h>

using namespace ImTrcr::Utils;

namespace ImTrcr {
namespace Imaging {

    ArgbQuad::ArgbQuad() {
        alpha = 255;
        red = 0;
        green = 0;
        blue = 0;
    }

    ArgbQuad::ArgbQuad(byte alpha, byte red, byte green, byte blue)
        : alpha(alpha), red(red), green(green), blue(blue) {}

    ArgbQuad::ArgbQuad(byte red, byte green, byte blue)
        : alpha(255), red(red), green(green), blue(blue) {}

    bool ArgbQuad::operator == (const ArgbQuad& right) {
        return this->alpha == right.alpha && this->red == right.red && this->green == right.green && this->blue == right.blue;
    }

    bool ArgbQuad::operator != (const ArgbQuad& right) {
        return !(*this == right);
    }

    ArgbQuad ArgbQuad::White() {
        return ArgbQuad(255, 255, 255, 255);
    }

    ArgbQuad ArgbQuad::Black() {
        return ArgbQuad(0, 0, 0, 0);
    }

}
}