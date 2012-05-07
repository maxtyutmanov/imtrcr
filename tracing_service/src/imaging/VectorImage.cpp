#include <imaging/VectorImage.h>
#include <utils/Memory.h>

using namespace std;
using namespace ImTrcr::Utils;

namespace ImTrcr {
namespace Imaging {

    void VectorImage::AddPrimitive(Primitive* p) {
        primitives.push_back(p);
    }

    const std::vector<Primitive*>& VectorImage::GetPrimitives() const {
        return primitives;
    }

    VectorImage::~VectorImage() {
        vector<Primitive*>::const_iterator it;

        for (it = primitives.begin(); it != primitives.end(); ++it) {
            Primitive* primitivePtr = *it;
            MemoryUtils::SafeFree(&primitivePtr);
        }
    }
}
}