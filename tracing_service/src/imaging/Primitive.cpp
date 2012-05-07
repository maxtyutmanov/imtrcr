#include <imaging/Primitive.h>

namespace ImTrcr {
namespace Imaging {

    Primitive::Primitive(ArgbQuad strokeColor, PrimitiveType::Enum type) {
        this->strokeColor = strokeColor;
        this->type = type;
    }

    ArgbQuad Primitive::GetStrokeColor() const {
        return this->strokeColor;
    }

    PrimitiveType::Enum Primitive::GetType() const {
        return this->type;
    }

}
}