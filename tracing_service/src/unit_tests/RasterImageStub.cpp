#include <unit_tests/RasterImageStub.h>
#include <utils/Memory.h>

using namespace ImTrcr::Imaging;
using namespace ImTrcr::Utils;

namespace ImTrcr {
namespace UnitTests {

    RasterImageStub::RasterImageStub(image_size_t width, image_size_t height) 
        : RasterImage(width, height) {
            
        long numberOfPixels = width * height;
        colorMap = new ArgbQuad[numberOfPixels];

        for (long i = 0; i < numberOfPixels; ++i) {
            colorMap[i] = ArgbQuad(255, 255, 255, 255);
        }
    }

    ArgbQuad RasterImageStub::GetColor(image_size_t x, image_size_t y) const {
        CheckCoordinates(x, y);

        return colorMap[y * GetWidth() + x];
    }

    void RasterImageStub::SetColor(image_size_t x, image_size_t y, ArgbQuad color) {
        CheckCoordinates(x, y);

        colorMap[y * GetWidth() + x] = color;
    }

    RasterImageStub::~RasterImageStub() {
        MemoryUtils::SafeFree(&colorMap);
    }
}
}