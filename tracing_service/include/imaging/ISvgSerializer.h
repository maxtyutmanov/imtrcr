#pragma once

#include "imaging/VectorImage.h"
#include "tinyxml/tinyxml.h"

namespace ImTrcr {
namespace Imaging {

    class ISvgSerializer {
    public:
        virtual TiXmlDocument* Serialize(const Imaging::VectorImage& vectorImage) const = 0;
    };

}
}
