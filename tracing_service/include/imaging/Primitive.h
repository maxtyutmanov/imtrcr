#ifndef IMAGING_PRIMITIVE_H
#define IMAGING_PRIMITIVE_H

#include "imaging/ArgbQuad.h"

namespace ImTrcr {
namespace Imaging {

    struct PrimitiveType {
        enum Enum {
            Path
        };
    };

    class Primitive {
    public:
        Primitive(ArgbQuad color, PrimitiveType type);

        ArgbQuad GetColor() const;
        PrimitiveType GetType() const;
    private:
        ArgbQuad color;
        PrimitiveType type;
    };

}
}

#endif
