#ifndef IMAGING_VECTOR_IMAGE_H
#define IMAGING_VECTOR_IMAGE_H

#include "imaging/Primitive.h"
#include <vector>

namespace ImTrcr {
namespace Imaging {

    //Represents an image as a set of geometric primitives
    class VectorImage {
    public:
        void AddPrimitive(Primitive* p);

        const std::vector<Primitive *>& GetPrimitives();
    private:
        std::vector<Primitive*> primitives;
    };

}
}

#endif
