#ifndef IMAGING_VECTOR_IMAGE_H
#define IMAGING_VECTOR_IMAGE_H

#include <imaging/Primitive.h>
#include <boost/noncopyable.hpp>
#include <vector>

namespace ImTrcr {
namespace Imaging {

    //Represents an image as a set of geometric primitives
    class VectorImage : boost::noncopyable {
    public:
        void AddPrimitive(Primitive* p);

        const std::vector<Primitive *>& GetPrimitives() const;

        virtual ~VectorImage();
    private:
        std::vector<Primitive*> primitives;
    };

}
}

#endif
