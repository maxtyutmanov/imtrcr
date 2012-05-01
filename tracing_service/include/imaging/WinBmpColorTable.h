#ifndef IMAGING_WIN_BMP_COLOR_TABLE_H
#define IMAGING_WIN_BMP_COLOR_TABLE_H

#include "imaging/Common.h"
#include "imaging/ArgbQuad.h"
#include <iostream>
#include <vector>

namespace ImTrcr {
namespace Imaging {

    //Represents a transformer from raw bitmap data to colors
    class WinBmpColorTable {
    public:
        //transforms raw bitmap data to color info
        ArgbQuad GetColor(Utils::byte* dataPtr) const;

        static WinBmpColorTable* FromStream(Utils::byte bitsPerPixel, unsigned long numberOfColors, std::istream& input);
    private:
        WinBmpColorTable(Utils::byte bitsPerPixel, const std::vector<ArgbQuad>& colorTable);

        std::vector<ArgbQuad> table;
        Utils::byte bitsPerPixel;
    };

}
}

#endif
