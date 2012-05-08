#include <vectorization/PotraceImage.h>
#include <utils/Memory.h>

using namespace ImTrcr::Imaging;
using namespace ImTrcr::Utils;

namespace ImTrcr {
namespace Vectorization {

    PotraceImage::PotraceImage(const IBWRecognizer& bwRecognizer, const RasterImage& rasterImg) {
        pixelMap = NULL;
        BuildPixelMap(bwRecognizer, rasterImg);

        this->width = rasterImg.GetWidth();
        this->height = rasterImg.GetHeight();
    }

    PotraceImage::~PotraceImage() {
        MemoryUtils::SafeFree(&pixelMap);
    }

    PixelColor::Enum PotraceImage::LT(Imaging::image_size_t x, Imaging::image_size_t y) const {
        return GetPixelAt(x, y, -1, -1);
    }

    PixelColor::Enum PotraceImage::LB(Imaging::image_size_t x, Imaging::image_size_t y) const {
        return GetPixelAt(x, y, -1, 1);
    }

    PixelColor::Enum PotraceImage::RT(Imaging::image_size_t x, Imaging::image_size_t y) const {
        return GetPixelAt(x, y, 1, -1);
    }

    PixelColor::Enum PotraceImage::RB(Imaging::image_size_t x, Imaging::image_size_t y) const {
        return GetPixelAt(x, y, 1, 1);
    }

    image_size_t PotraceImage::GetW() const {
        return this->width;
    }

    image_size_t PotraceImage::GetH() const {
        return this->height;
    }

    void PotraceImage::BuildPixelMap(const IBWRecognizer& bwRecognizer, const RasterImage& rasterImg) {
        long numberOfPixels = rasterImg.GetWidth() * rasterImg.GetHeight();
        pixelMap = new PixelColor::Enum[numberOfPixels];

        long currentPixelIndex = 0;

        for (image_size_t x = 0; x < rasterImg.GetWidth(); ++x) {
            for (image_size_t y = 0; y < rasterImg.GetHeight(); ++y) {
                pixelMap[currentPixelIndex] = bwRecognizer.GetPotraceColor(rasterImg.GetColor(x, y));
                ++currentPixelIndex;
            }
        }
    }

    PixelColor::Enum PotraceImage::GetPixelAt(image_size_t x, image_size_t y, int shiftX, int shiftY) const {
        shiftX = (shiftX > 0 ? 0 : -1);
        shiftY = (shiftY > 0 ? 0 : -1);

        x += shiftX;
        y += shiftY;

        if (x < 0 || x >= GetW() || y < 0 || y >= GetH()) {
            return PixelColor::White;
        }
        else {
            return pixelMap[y * GetW() + x];
        }
    }
}
}