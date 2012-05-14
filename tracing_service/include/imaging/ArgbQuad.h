#ifndef IMAGING_ARGB_QUAD_H
#define IMAGING_ARGB_QUAD_H

#include "imaging/Common.h"

namespace ImTrcr {
namespace Imaging {
    //Represents one pixel value in ARGB color space
    struct ArgbQuad {
        ArgbQuad();
        ArgbQuad(Utils::byte alpha, Utils::byte red, Utils::byte green, Utils::byte blue);
        ArgbQuad(Utils::byte red, Utils::byte green, Utils::byte blue);

        bool operator == (const ArgbQuad& right);
        bool operator != (const ArgbQuad& right);
        
        static ArgbQuad White();
        static ArgbQuad Black();

        Utils::byte red;
        Utils::byte green;
        Utils::byte blue;
        Utils::byte alpha;
    };
}
}

#endif