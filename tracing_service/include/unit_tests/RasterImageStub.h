#ifndef UNIT_TESTS_RASTER_IMAGE_STUB_H
#define UNIT_TESTS_RASTER_IMAGE_STUB_H

#include <imaging/RasterImage.h>

namespace ImTrcr {
namespace UnitTests {

    //RasterImage's implementation for unit tests purposes
    class RasterImageStub : public Imaging::RasterImage {
    public:
        RasterImageStub(Imaging::image_size_t width, Imaging::image_size_t height);
        virtual Imaging::ArgbQuad GetColor(Imaging::image_size_t x, Imaging::image_size_t y) const;
        void SetColor(Imaging::image_size_t x, Imaging::image_size_t y, Imaging::ArgbQuad color);

        ~RasterImageStub();
    private:
        Imaging::ArgbQuad* colorMap;
    };

}
}

#endif