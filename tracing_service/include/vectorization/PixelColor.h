#ifndef VECTORIZATION_PIXEL_COLOR_H
#define VECTORIZATION_PIXEL_COLOR_H

namespace ImTrcr {
namespace Vectorization {

    //Color of pixel as Potrace algorithm sees it
    struct PixelColor {
        enum Enum {
            Black,
            White
        };
    };

}
}

#endif