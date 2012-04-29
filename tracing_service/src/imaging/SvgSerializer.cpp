#include "imaging/SvgSerializer.h"

namespace ImTrcr {
namespace Imaging {

  TiXmlDocument* SvgSerializer::Serialize(const Imaging::VectorImage& vectorImage) const {
    return new TiXmlDocument();
  }
  
}
}
