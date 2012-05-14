#ifndef IMAGING_PRIMITIVE_H
#define IMAGING_PRIMITIVE_H

#include <imaging/ArgbQuad.h>
#include <iostream>

namespace ImTrcr {
namespace Imaging {

    struct PrimitiveType {
        enum Enum {
            Path = 1
        };
    };

    class Primitive {
    public:
        Primitive(ArgbQuad strokeColor, PrimitiveType::Enum type);

        ArgbQuad GetStrokeColor() const;
        PrimitiveType::Enum GetType() const;

        virtual ~Primitive() {}
    private:
        ArgbQuad strokeColor;
        PrimitiveType::Enum type;
    };

}
}

#endif
