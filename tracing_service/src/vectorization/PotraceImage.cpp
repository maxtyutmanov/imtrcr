#include <vectorization/PotraceImage.h>
#include <utils/Memory.h>

#include <stdexcept>
#include <map>
#include <algorithm>

using namespace ImTrcr::Imaging;
using namespace ImTrcr::Utils;
using namespace std;

namespace ImTrcr {
namespace Vectorization {

    PotraceImage::PotraceImage(const IBWRecognizer& bwRecognizer, const RasterImage& rasterImg) {
        pixelMap = NULL;
        isInvertedMap = NULL;
        BuildMaps(bwRecognizer, rasterImg);

        this->width = rasterImg.GetWidth();
        this->height = rasterImg.GetHeight();
    }

    PotraceImage::~PotraceImage() {
        MemoryUtils::SafeFree(&pixelMap);
        MemoryUtils::SafeFree(&isInvertedMap);
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

    void PotraceImage::InvertPixels(const vector<PotracePath::Point2>& pixels) {
        vector<PotracePath::Point2>::const_iterator it;
        const vector<PotracePath::Point2>::const_iterator pixelsEnd = pixels.end();
        for (it = pixels.begin(); it != pixelsEnd; ++it) {
            if (it->x >= 0 && it->x < GetW() || it->y >= 0 || it->y < GetH()) {
                long mapIndex = it->y * GetW() + it->x;

                PixelColor::Enum currentColor = pixelMap[mapIndex];
                PixelColor::Enum invertedColor = (currentColor == PixelColor::Black ? PixelColor::White : PixelColor::Black);
                
                pixelMap[mapIndex] = invertedColor;
                isInvertedMap[mapIndex] = !isInvertedMap[mapIndex];
            }
        }
    }

    image_size_t PotraceImage::GetW() const {
        return this->width;
    }

    image_size_t PotraceImage::GetH() const {
        return this->height;
    }

    void PotraceImage::BuildMaps(const IBWRecognizer& bwRecognizer, const RasterImage& rasterImg) {
        long numberOfPixels = rasterImg.GetWidth() * rasterImg.GetHeight();
        pixelMap = new PixelColor::Enum[numberOfPixels];

        long currentPixelIndex = 0;

        for (image_size_t y = 0; y < rasterImg.GetHeight(); ++y) {
            for (image_size_t x = 0; x < rasterImg.GetWidth(); ++x) {
                pixelMap[currentPixelIndex] = bwRecognizer.GetPotraceColor(rasterImg.GetColor(x, y));
                ++currentPixelIndex;
            }
        }

        isInvertedMap = new bool[numberOfPixels];
        for (long i = 0; i < numberOfPixels; ++i) {
            isInvertedMap[i] = false;
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