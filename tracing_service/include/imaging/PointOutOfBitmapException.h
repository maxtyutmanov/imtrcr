#ifndef IMAGING_POINT_OUT_OF_BITMAP_EXCEPTION_H
#define IMAGING_POINT_OUT_OF_BITMAP_EXCEPTION_H

#include <stdexcept>
#include "imaging/Common.h"

namespace ImTrcr {
namespace Imaging {

    class PointOutOfBitmapException : public std::runtime_error {
    public:
        PointOutOfBitmapException(image_size_t x, image_size_t y) 
            : std::runtime_error("Invalid point's coordinates"), x(x), y(y) { }

        image_size_t GetX() const {
            return x;
        }
        image_size_t GetY() const {
            return y;
        }
        
        virtual ~PointOutOfBitmapException() throw() {}
    private:
        image_size_t x;
        image_size_t y;
    };

}
}

#endif
