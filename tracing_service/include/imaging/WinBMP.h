#pragma once

#include "imaging/RasterImage.h"
#include "imaging/ArgbQuad.h"
#include "imaging/WinBmpColorTable.h"
#include <string>
#include <vector>

namespace ImTrcr {
namespace Imaging {

    //Device independent bitmap (DIB) - Windows bitmap format
    class WinBMP : public RasterImage {
    public:
        //inherited
        virtual ArgbQuad GetColor(image_size_t x, image_size_t y) const;
        //loads bitmap from the specified stream
        static WinBMP* FromStream(std::istream& input);

        virtual ~WinBMP();
    private:
        WinBMP(image_size_t width, image_size_t height, Utils::byte* bmpData, WinBmpColorTable* colorTable, Utils::byte bitsPerPixel);

        Utils::byte bitsPerPixel;
        Utils::byte* bmpData;
        WinBmpColorTable* colorTable;
    };

}
}
