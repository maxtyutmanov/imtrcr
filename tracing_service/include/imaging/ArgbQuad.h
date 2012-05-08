#ifndef IMAGING_ARGB_QUAD_H
#define IMAGING_ARGB_QUAD_H

#include "imaging/Common.h"

namespace ImTrcr {
namespace Imaging {
    //Represents one pixel value in ARGB color space
    struct ArgbQuad {
        ArgbQuad() {
            alpha = 255;
            red = 0;
            green = 0;
            blue = 0;
        }

        ArgbQuad(Utils::byte alpha, Utils::byte red, Utils::byte green, Utils::byte blue)
            : alpha(alpha), red(red), green(green), blue(blue) {}

        ArgbQuad(Utils::byte red, Utils::byte green, Utils::byte blue)
            : alpha(255), red(red), green(green), blue(blue) {}

        bool operator == (const ArgbQuad& right) {
            return this->alpha == right.alpha && this->red == right.red && this->green == right.green && this->blue == right.blue;
        }

        bool operator != (const ArgbQuad& right) {
            return !(*this == right);
        }
        
        Utils::byte red;
        Utils::byte green;
        Utils::byte blue;
        Utils::byte alpha;

        static ArgbQuad White() {
            return ArgbQuad(255, 255, 255, 255);
        }

        static ArgbQuad Black() {
            return ArgbQuad(0, 0, 0, 0);
        }
    };
}
}

#endif