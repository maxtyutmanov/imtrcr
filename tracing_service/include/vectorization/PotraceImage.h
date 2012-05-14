#ifndef VECTORIZATION_POTRACE_IMAGE_H
#define VECTORIZATION_POTRACE_IMAGE_H

#include <imaging/RasterImage.h>

#include <vectorization/PixelColor.h>
#include <vectorization/IBWRecognizer.h>
#include <vectorization/PotracePath.h>

#include <vector>

namespace ImTrcr {
namespace Vectorization {
    
    //Special representation of raster image that Potrace algorithm works with.
    //Note 1: potrace can only work with monochrome images, so all color information
    //in original colored image will be lost.
    //Note 2: coordinate grid has nodes not at the centers of pixels, but on their corners
    class PotraceImage {
    public:
        PotraceImage(const IBWRecognizer& bwRecognizer, const Imaging::RasterImage& rasterImg);
        ~PotraceImage();

        //LT - left top. Gets the color of pixel located on the left above the point (x, y)
        PixelColor::Enum LT(Imaging::image_size_t x, Imaging::image_size_t y) const;
        //LB - left bottom. Gets the color of pixel located on the left below the point (x, y)
        PixelColor::Enum LB(Imaging::image_size_t x, Imaging::image_size_t y) const;
        //RT - right top. Gets the color of pixel located on the right above the point (x, y)
        PixelColor::Enum RT(Imaging::image_size_t x, Imaging::image_size_t y) const;
        //RB - right bottom. Gets the color of pixel located on the right below the point (x, y)
        PixelColor::Enum RB(Imaging::image_size_t x, Imaging::image_size_t y) const;

        void InvertPixels(const std::vector<PotracePath::Point2>& pixels);

        //Gets the width of original image
        Imaging::image_size_t GetW() const;
        //Gets the height of original image
        Imaging::image_size_t GetH() const;
    private:
        void BuildMaps(const IBWRecognizer& bwRecognizer, const Imaging::RasterImage& rasterImg);
        PixelColor::Enum GetPixelAt(Imaging::image_size_t x, Imaging::image_size_t y, int shiftX, int shiftY) const;

        Imaging::image_size_t width;
        Imaging::image_size_t height;
        PixelColor::Enum* pixelMap;
        bool* isInvertedMap;
    };

}
}

#endif