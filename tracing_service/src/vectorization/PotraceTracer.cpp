#pragma once

#include "vectorization/PotraceTracer.h"

using namespace ImTrcr::Imaging;

namespace ImTrcr {
namespace Vectorization {

  Imaging::VectorImage* PotraceTracer::Trace(const Imaging::RasterImage& rasterImage) {
    return new VectorImage();
  }

}
}
