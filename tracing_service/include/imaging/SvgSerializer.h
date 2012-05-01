#ifndef IMAGING_SVG_SERIALIZER_H
#define IMAGING_SVG_SERIALIZER_H

#include "imaging/ISvgSerializer.h"
#include "tinyxml/tinyxml.h"

namespace ImTrcr {
namespace Imaging {

    class SvgSerializer : public ISvgSerializer {
    public:
        virtual TiXmlDocument* Serialize(const Imaging::VectorImage& vectorImage) const;
    };

}
}

#endif
